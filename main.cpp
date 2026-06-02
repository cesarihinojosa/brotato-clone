/*******************************************************************************************
 *
 *   raylib [core] example - basic window
 *
 *   Example complexity rating: [★☆☆☆] 1/4
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute 'raylib_compile_execute' script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   To test the examples on Web, press F6 and execute
 * 'raylib_compile_execute_web' script Web version of the program is generated
 * in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   Example originally created with raylib 1.0, last time updated with
 * raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an
 * OSI-certified, BSD-like license that allows static linking with closed source
 * software
 *
 *   Copyright (c) 2013-2026 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/
#include "enemy.hpp"
#include "player.hpp"
#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  // TODO: learn more about FPS
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  Player player(screenWidth / 2.0f, screenHeight / 2.0f, 5, 64.0, 64.0);
  Enemy enemy(15, 15, 5);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    player.update();
    enemy.update();
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(GRAY);

    player.draw();
    enemy.draw();
    DrawFPS(screenWidth - 30, screenHeight - 30);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  player.unload();
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
