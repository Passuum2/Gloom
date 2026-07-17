# Gloom
Gloom is a modular 2D game engine prototype written in C using SDL2. It features an object-oriented gameplay architecture supporting player movement, collision detection, class selection, and persistent save/load functionality. The engine includes a custom texture asset pipeline and UI menu system, with rendering and system interfaces documented to support integration of artist-created assets and ongoing feature development.

## Features
- Player movement and collision detection
- Class selection system
- Save/load functionality
- UI menu system
- Texture asset pipeline

## Controls
| Key | Action |
| --- | --- |
| Up / Down Arrow Keys | Navigate menus |
| Enter | Select / Confirm |
| W / A / S / D | Move character |
| Arrow Keys | Look around |

## Screenshots
**Main Menu** 
![Screenshot](Screenshots/MainMenu(Gloom).png)
**Character Menu** 
![Screenshot](Screenshots/CharacterMenu(Gloom).png)
**Main Map** 
![Screenshot](Screenshots/MainMap(Gloom).png)

## Tech Stack
- **Language:** C
- **Library:** SDL2

## Build & Run
### Prerequisites
- GCC compiler
- SDL2 

### Steps
1. Clone the repo
2. Build:
   - **Windows:** `./run`
   - **Manual:** `gcc -g -O2 -I include src/*.c -L lib/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -o bin/Gloom.exe`
3. Run the executable: `bin/Gloom.exe`

## Project Structure
src/        — source code
include/    — headers
Textures/   — game art assets
Sound/      — audio assets
bin/        — build output

## Roadmap
- [ ] Combat system
- [ ] Enemy AI
- [ ] Random Map Generation

## Status
Actively developed — solo project, ongoing since October 2025.
