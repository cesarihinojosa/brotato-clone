#include "raylib.h"
#include "scene.hpp"

// TODO: Add documentaion
// Program main entry point
int main(void) {
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  // TODO: learn more about FPS
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Scene scene;
  GameObject &player = scene.spawn();
  // player.addComponent<ShapeComponent>(rectangle, size);

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
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
