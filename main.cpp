#include "components.hpp"
#include "core.hpp"
#include "raylib.h"
#include "systems.hpp"

int main(void) {

  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Scene scene;
  scene.addSystem<CollisionSystem>();
  TextureCache textureCache;

  GameObject &player = scene.spawn();
  player.addComponent<HealthComponent>(10, 10);
  player.addComponent<TransformComponent>(screenWidth / 2, screenHeight / 2);
  player.addComponent<VelocityComponent>(5);
  player.addComponent<PlayerInputComponent>();
  player.addComponent<AnimationSpriteComponent>(
      textureCache.get("assets/characters/bull.png"), 0.15, 0.9, 8);
  player.addComponent<HitboxComponent>(25.0);
  player.getComponent<HitboxComponent>()->debug = true;
  player.addComponent<DamageComponent>(3, 8);

  GameObject &enemy = scene.spawn();
  enemy.addComponent<HealthComponent>(15, 15);
  enemy.addComponent<TransformComponent>(screenWidth / 4, screenHeight / 4);
  enemy.addComponent<AnimationSpriteComponent>(
      textureCache.get("assets/enemies/baby_alien.png"), 0.07, 0.9, 7);
  enemy.addComponent<HitboxComponent>(25.0);
  enemy.getComponent<HitboxComponent>()->debug = true;
  enemy.addComponent<DamageComponent>(3, 8);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    float dt = GetFrameTime();
    scene.update(dt);

    // Draw
    BeginDrawing();
    ClearBackground(GRAY);
    DrawFPS(screenWidth - 30, screenHeight - 30);
    scene.draw();
    EndDrawing();
  }

  // De-Initialization
  textureCache.unloadAll();
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
