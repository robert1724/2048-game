# 2048-game
Terminal-based implementation of the classic 2048 game written in C, using ncurses library to create a text-based graphical interface in the terminal. 

The game runs on a 4×4 matrix where tiles move using W, A, S, D controls. I implemented the full movement and merge logic manually for all four directions, making sure the tiles combine correctly and the score updates after every merge. After each valid move, a new tile (2 or 4) is generated randomly in an empty cell.

The interface includes:
  - A start menu with New Game, Resume, and Quit
  - A visually drawn board using ncurses line characters
  - Colored tiles for better readability
  - Real-time score display

The game ends when:
  - The board is full (Game Over)
  - The player reaches 2048 (You won)

I built this project to better understand matrix manipulation, game logic implementation, and how to use the ncurses library for interactive terminal applications.
Technologies used: C, ncurses, random number generation, non-blocking keyboard input.


BUILD & RUN:
git clone https://github.com/robert1724/2048-game.git
cd 2048-game
gcc 2048.c -o 2048 -lncurses
./2048
