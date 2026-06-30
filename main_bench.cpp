#include "alloc_counter.hpp"
#include "animation_sprite_component.hpp"
#include "game_object.hpp"
#include "health_component.hpp"
#include "raylib.h"
#include "scene.hpp"
#include "transform_component.hpp"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <sys/resource.h>
#include <vector>

#ifndef GIT_COMMIT
#define GIT_COMMIT "unknown"
#endif
#ifndef BUILD_MODE
#define BUILD_MODE "unknown"
#endif

using clk = std::chrono::steady_clock;

static double ms_since(clk::time_point t0) {
  using namespace std::chrono;
  return duration<double, std::milli>(clk::now() - t0).count();
}

static double percentile(std::vector<double> v, double p) {
  if (v.empty())
    return 0.0;
  std::sort(v.begin(), v.end());
  auto idx = static_cast<std::size_t>((p / 100.0) * (v.size() - 1));
  return v[idx];
}

static double mean(const std::vector<double> &v) {
  double s = 0.0;
  for (double x : v)
    s += x;
  return v.empty() ? 0.0 : s / v.size();
}

static long peak_rss_bytes() {
  rusage r{};
  getrusage(RUSAGE_SELF, &r);
#ifdef __APPLE__
  return r.ru_maxrss; // bytes on macOS
#else
  return r.ru_maxrss * 1024; // kilobytes on Linux
#endif
}

static std::string iso_now() {
  std::time_t t = std::time(nullptr);
  char buf[32];
  std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", std::localtime(&t));
  return buf;
}

int main(int argc, char **argv) {
  int N = 1000;
  int frames = 600;
  int warmup = 60;
  const char *notes = "";

  for (int i = 1; i < argc; ++i) {
    if (!std::strncmp(argv[i], "--entities=", 11))
      N = std::atoi(argv[i] + 11);
    else if (!std::strncmp(argv[i], "--frames=", 9))
      frames = std::atoi(argv[i] + 9);
    else if (!std::strncmp(argv[i], "--notes=", 8))
      notes = argv[i] + 8;
  }

  InitWindow(800, 450, "brotato-bench");
  // NOTE: no SetTargetFPS, no vsync — let frames run uncapped so timings
  // reflect actual CPU+GPU work rather than raylib's sleep padding.

  std::srand(42); // deterministic entity positions across runs
  long rss_before = peak_rss_bytes();

  Scene scene;
  for (int i = 0; i < N; ++i) {
    GameObject &e = scene.spawn();
    e.addComponent<TransformComponent>(std::rand() % 800, std::rand() % 450);
    e.addComponent<AnimationSpriteComponent>("assets/enemies/baby_alien.png",
                                             0.07f, 0.9f, 7);
    e.addComponent<HealthComponent>(2, 20);
  }
  long rss_after = peak_rss_bytes();
  long bytes_per_entity = (rss_after - rss_before) / std::max(1, N);

  std::vector<double> frame_ms, update_ms, draw_ms, allocs;
  frame_ms.reserve(frames);
  update_ms.reserve(frames);
  draw_ms.reserve(frames);
  allocs.reserve(frames);

  int total = warmup + frames;
  for (int f = 0; f < total && !WindowShouldClose(); ++f) {
    std::size_t allocs_start =
        g_alloc_count.load(std::memory_order_relaxed);

    auto t_frame = clk::now();
    float dt = GetFrameTime();

    auto t_upd = clk::now();
    scene.update(dt);
    double upd = ms_since(t_upd);

    auto t_drw = clk::now();
    BeginDrawing();
    ClearBackground(GRAY);
    scene.draw();
    DrawFPS(10, 10);
    EndDrawing();
    double drw = ms_since(t_drw);

    double total_ms = ms_since(t_frame);
    std::size_t a =
        g_alloc_count.load(std::memory_order_relaxed) - allocs_start;

    if (f >= warmup) {
      update_ms.push_back(upd);
      draw_ms.push_back(drw);
      frame_ms.push_back(total_ms);
      allocs.push_back(static_cast<double>(a));
    }
  }

  long rss_peak = peak_rss_bytes();
  CloseWindow();

  const char *path = "benchmarks/results.csv";
  bool exists = std::ifstream(path).good();
  std::ofstream out(path, std::ios::app);
  if (!exists) {
    out << "timestamp,commit,build,n_entities,frames,"
           "avg_frame_ms,p50_frame_ms,p99_frame_ms,"
           "avg_update_ms,p99_update_ms,"
           "avg_draw_ms,p99_draw_ms,"
           "peak_rss_mb,bytes_per_entity,"
           "avg_allocs_per_frame,p99_allocs_per_frame,notes\n";
  }
  out << iso_now() << "," << GIT_COMMIT << "," << BUILD_MODE << "," << N << ","
      << frames << "," << mean(frame_ms) << "," << percentile(frame_ms, 50)
      << "," << percentile(frame_ms, 99) << "," << mean(update_ms) << ","
      << percentile(update_ms, 99) << "," << mean(draw_ms) << ","
      << percentile(draw_ms, 99) << "," << (rss_peak / (1024.0 * 1024.0))
      << "," << bytes_per_entity << "," << mean(allocs) << ","
      << percentile(allocs, 99) << "," << notes << "\n";

  std::printf("Wrote 1 row to %s\n", path);
  return 0;
}
