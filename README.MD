# Conway's Game of Life

A simple implementation of Conway's Game of Life using C++ and [raylib](https://www.raylib.com/) library.

## Description

Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. The game consists of a grid of cells, each of which can be in one of two states: alive or dead. The state of each cell evolves over time based on a set of rules.

## Features

- Click to toggle cells alive or dead.
- Press SPACE to start/pause the simulation.
- Press R to clear the grid.
- Press N to generate the next generation manually.
- Real-time FPS display.

## How to Run

1. Clone this repository.
2. Compile the code with `g++ main.cpp -lraylib -O2 && ./a.out`.

## Controls

- Left Mouse Button: Toggle cell alive.
- Right Mouse Button: Toggle cell dead.
- SPACE: Start/Pause simulation.
- R: Clear the grid.
- N: Generate the next generation manually.

## Rules

- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Dependencies

- raylib library



