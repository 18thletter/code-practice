#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

// globals, ugly but serves its purpose here
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;
const char POPULATED_CELL_CHAR = '#';

void populateGrid(bool (&grid)[GRID_HEIGHT][GRID_WIDTH], int populationPercentage) {
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      int randNum  = rand() % 100 + 1;
      if (randNum < populationPercentage) {
        grid[i][j] = 1;
      } else {
        grid[i][j] = 0;
      }
    }
  }
}

void printGrid(bool (&grid)[GRID_HEIGHT][GRID_WIDTH]) {
  // bad practice, but serves its purpose here
  system("clear");
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      cout << (grid[i][j] ? POPULATED_CELL_CHAR : ' ');
    }
    cout << "\n";
  }
}

int neighborsAlive(bool (&grid)[GRID_HEIGHT][GRID_WIDTH], int i, int j) {
  int alive = 0;
  // top left
  if (i > 0 && j > 0 && grid[i - 1][j - 1]) {
    alive++;
  }
  // top
  if (i > 0 && grid[i - 1][j]) {
    alive++;
  }
  // top right
  if (i > 0 && j < GRID_WIDTH - 1 && grid[i - 1][j + 1]) {
    alive++;
  }
  // right
  if (j < GRID_WIDTH - 1 && grid[i][j + 1]) {
    alive++;
  }
  // bottom right
  if (i < GRID_HEIGHT - 1 && j < GRID_WIDTH - 1 && grid[i + 1][j + 1]) {
    alive++;
  }
  // bottom
  if (i < GRID_HEIGHT - 1 && grid[i + 1][j]) {
    alive++;
  }
  // bottom left
  if (i < GRID_HEIGHT - 1 && j > 0 && grid[i + 1][j - 1]) {
    alive++;
  }
  // left
  if (j > 0 && grid[i][j - 1]) {
    alive++;
  }
  return alive;
}

void copyGrid(bool (&grid)[GRID_HEIGHT][GRID_WIDTH], bool (&copy)[GRID_HEIGHT][GRID_WIDTH]) {
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      copy[i][j] = grid[i][j];
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Please enter the population percentage and the number of cycles\n";
    return 0;
  }
  int populationPercentage = atoi(argv[1]);
  int cycles = atoi(argv[2]);

  srand(time(NULL));

  bool grid[GRID_HEIGHT][GRID_WIDTH];

  populateGrid(grid, populationPercentage);

  // make a copy at the beginning so we can change some things
  bool copy[GRID_HEIGHT][GRID_WIDTH];

  for (int cycle = 0; cycle < cycles; cycle++) {
    printGrid(grid);
    copyGrid(grid, copy);
    for (int i = 0; i < GRID_HEIGHT; i++) {
      for (int j = 0; j < GRID_WIDTH; j++) {
        int neighbors = neighborsAlive(grid, i, j);
        bool alive = grid[i][j];

        if (alive && neighbors < 2) {
          copy[i][j] = 0;
        } else if (alive && neighbors > 3) {
          copy[i][j] = 0;
        } else if (!alive && neighbors == 3) {
          copy[i][j] = 1;
        }
      }
    }
    copyGrid(copy, grid);
    // wait .3 sec
    usleep(300000);
  }

  return 0;
}
