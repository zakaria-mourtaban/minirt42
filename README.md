# So Long And Thanks For All The Fish!

![image](https://github.com/user-attachments/assets/cbceef76-aa4f-4c15-97d5-615af163da3e)

## Overview
This project is a 2D game developed in C using MiniLibX(for linux), focusing on graphics, sprite animation, and basic gameplay mechanics. The goal is to navigate a map, collect items, and reach the exit while avoiding obstacles.

## Features
- **Gameplay**: Use WASD or arrow keys to move the player. Collect all items and find the shortest path to the exit.
- **Graphics**: Utilizes MiniLibX for window management and smooth graphical display.
- **Map**: Maps are defined in .ber files and consist of walls, collectibles, and player/exit positions.
- **Bonus Features**: Includes sprite animations and on-screen display of movement counts.

## Requirements
- Written in C adhering to project-specific norms.
- Utilizes dynamic memory allocation with proper error handling.
- Includes a Makefile for compilation with necessary flags and rules.
- Integration with MiniLibX for graphical management.

## Usage
1. **Compile**: Use the provided Makefile (`make` command).
2. **Run**: Execute the program with a map file as an argument (`./so_long map.ber`).
3. **Controls**: Use WASD or arrow keys to move the player. Press ESC or close the window to exit.
