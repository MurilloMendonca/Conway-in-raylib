//Run with " g++ main.cpp  -lraylib -O2 && ./a.out "
extern "C" {
#include "raylib.h"
}
#include <vector>
#include <bitset>
#define SQR_SIZE 20
#define screenWidth  1000 
#define screenHeight  1000 
#define numberOfCols screenWidth/SQR_SIZE
#define numberOfRows screenHeight/SQR_SIZE
#define numberOfSquares numberOfCols*numberOfRows
std::bitset<numberOfSquares> generateNewGeneration(std::bitset<numberOfSquares> bits, int NCols, int NRows);
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(screenWidth, screenHeight, "raylib Conway's Game of Life");
  std::bitset<numberOfSquares> values {};
  
  std::vector<Rectangle> squares;
  for (int i = 0; i < numberOfRows; i++) {
    for (int j = 0; j < numberOfCols; j++) {
      Rectangle rect;
      // item.color = (i + j) % 2 == 0 ? WHITE : GRAY;
      rect = {(float)j * SQR_SIZE, (float)i * SQR_SIZE, SQR_SIZE,
                   SQR_SIZE};

      squares.push_back(rect);
      values[i * numberOfCols + j] = false;
    }
  }

  Camera2D camera = {0};
  camera.target = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  int cameraOption = 0;

  Vector2 mousePosition = {-100.0f, -100.0f};
  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  bool running = false;
  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    //----------------------------------------------------------------------------------
    float deltaTime = GetFrameTime();
    mousePosition = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      int id = 0;
      for (auto square : squares) {
        if (CheckCollisionPointRec(mousePosition, square)) {
          values[id] = true;
        }
        id++;
      }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      int id = 0;
      for (auto square : squares) {
        if (CheckCollisionPointRec(mousePosition, square)) {
          values[id] = false;
        }
        id++;
      }
    }
    if (IsKeyPressed(KEY_SPACE)) {
      running = !running;
    }
    if (IsKeyPressed(KEY_R)) {
        values.reset();
    }
    if (IsKeyPressed(KEY_N)) {
      values = generateNewGeneration(values, numberOfCols, numberOfRows);
    }
    // Simulate the Conway's Game of Life
    //----------------------------------------------------------------------------------
    if (running) {
        values = generateNewGeneration(values, numberOfCols, numberOfRows);
    }
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(LIGHTGRAY);

    BeginMode2D(camera);

    for (int i = 0; i < squares.size(); i++) {
      DrawRectangleRec(squares[i], values[i]?RED:BLACK);
    }
    //Draw a grid around the squares
    for (int i = 0; i < numberOfCols; i++) {
      DrawLine(i * SQR_SIZE, 0, i * SQR_SIZE, screenHeight, DARKGRAY);
    }
    for (int i = 0; i < numberOfRows; i++) {
      DrawLine(0, i * SQR_SIZE, screenWidth, i * SQR_SIZE, DARKGRAY);
    }
    DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f / deltaTime)),
             GetScreenWidth() - 220, 40, 20, GREEN);
    EndMode2D();

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}



std::bitset<numberOfSquares> generateNewGeneration(std::bitset<numberOfSquares> bits, int NCols, int NRows){
  std::bitset<numberOfSquares> newGeneration = bits;
  for (int i = 0; i < bits.size(); i++) {
    int aliveNeighbours = 0;
    int x = i % NCols;
    int y = i / NCols;
    if (x - 1 > 0) {
      if (bits[i - 1])
        aliveNeighbours++;
    }
    if (x + 1 < NCols) {
      if (bits[i + 1])
        aliveNeighbours++;
    }
    if (y - 1 > 0) {
      if (bits[(y - 1) * NCols + x])
        aliveNeighbours++;
    }
    if (y + 1 < NRows) {
      if (bits[(y + 1) * NCols + x])
        aliveNeighbours++;
    }
    if (x - 1 > 0 && y - 1 > 0) {
      if (bits[(y - 1) * NCols + (x - 1)])
        aliveNeighbours++;
    }
    if (x - 1 > 0 && y + 1 < NRows) {
      if (bits[(y + 1) * NCols + (x - 1)])
        aliveNeighbours++;
    }
    if (x + 1 < NCols && y + 1 < NRows) {
      if (bits[(y + 1) * NCols + (x + 1)])
        aliveNeighbours++;
    }
    if (x + 1 < NCols && y - 1 > 0) {
      if (bits[(y - 1) * NCols + (x + 1)])
        aliveNeighbours++;
    }
    if (bits[i]) {
      if (aliveNeighbours < 2 || aliveNeighbours > 3) {
        newGeneration[i] = false;
      }
    } else if (aliveNeighbours == 3) {
      newGeneration[i] = true;
    }
  }
  return newGeneration;
}
