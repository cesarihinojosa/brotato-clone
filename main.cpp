#include "animation_sprite_component.hpp"
#include "game_object.hpp"
#include "health_component.hpp"
#include "hitbox_component.hpp"
#include "player_input_component.hpp"
#include "raylib.h"
#include "rectangle_component.hpp"
#include "scene.hpp"
#include "sprite_component.hpp"
#include "texture_cache.hpp"
#include "transform_component.hpp"
#include "velocity_component.hpp"

int main(void) {

  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Scene scene;
  TextureCache textureCache;

  GameObject &player = scene.spawn();
  player.addComponent<TransformComponent>(screenWidth / 2, screenHeight / 2);
  player.addComponent<VelocityComponent>(5);
  player.addComponent<PlayerInputComponent>();
  player.addComponent<AnimationSpriteComponent>(
      textureCache.get("assets/characters/bull.png"), 0.15, 0.9, 8);
  player.addComponent<HealthComponent>(8, 10);
  player.addComponent<HitboxComponent>(25.0);
  player.getComponent<HitboxComponent>()->debug = true;

  GameObject &enemy = scene.spawn();
  enemy.addComponent<TransformComponent>(screenWidth / 4, screenHeight / 4);
  enemy.addComponent<AnimationSpriteComponent>(
      textureCache.get("assets/enemies/baby_alien.png"), 0.07, 0.9, 7);
  enemy.addComponent<HealthComponent>(2, 20);

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
