#include "alloc_counter.hpp"
#include <cstdlib>
#include <new>

std::atomic<std::size_t> g_alloc_count{0};
std::atomic<std::size_t> g_alloc_bytes{0};

// Replace the global allocator so every `new` in the process bumps the
// counters. This includes raylib's internal allocations, which is fine —
// we measure per-frame deltas, and steady-state frames should be alloc-free.

void *operator new(std::size_t n) {
  g_alloc_count.fetch_add(1, std::memory_order_relaxed);
  g_alloc_bytes.fetch_add(n, std::memory_order_relaxed);
  if (void *p = std::malloc(n))
    return p;
  throw std::bad_alloc();
}

void *operator new[](std::size_t n) { return ::operator new(n); }

void operator delete(void *p) noexcept { std::free(p); }
void operator delete[](void *p) noexcept { std::free(p); }
void operator delete(void *p, std::size_t) noexcept { std::free(p); }
void operator delete[](void *p, std::size_t) noexcept { std::free(p); }
