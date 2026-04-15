*This project has been created as part of the 42 curriculum by ddamiba, mcardoso.*

# cub3D

## Description

cub3D is a 3D maze explorer inspired by the legendary Wolfenstein 3D — the first-ever FPS game. The goal is to implement a basic ray-casting engine from scratch using the C programming language and the MiniLibX graphical library, producing a first-person perspective view of a maze defined by a custom `.cub` map file.

The player can navigate the maze in real time, with each wall rendered using directional textures (North, South, East, West) and the floor/ceiling rendered in configurable flat colors. A minimap is also displayed in the corner for orientation.

Key features:
- DDA (Digital Differential Analysis) ray-casting algorithm for wall rendering
- Textured walls loaded from `.xpm` files, with correct directional mapping
- Configurable floor and ceiling colors via the `.cub` map file
- Player movement (WASD) and rotation (arrow keys)
- Collision detection preventing the player from walking through walls
- Interactive minimap overlay
- Robust `.cub` file parsing with full validation (map integrity, config completeness, character validity, player spawn)

## Instructions

### Requirements

- Linux (Ubuntu/Debian recommended)
- `gcc`, `make`
- X11 development libraries: `xorg`, `libxext-dev`, `libbsd-dev`

Install dependencies on Debian/Ubuntu:
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### Compilation

Clone the repository and build:
```bash
git clone https://github.com/ggte11/42_Cub3d.git cub3D
cd cub3D
make
```

This will compile `libft`, `get_next_line`, `minilibx-linux`, and the main binary `cub3D`.

### Running

```bash
./cub3D maps/big_map.cub
```

You can use any valid `.cub` map file. Several example maps are provided in the `maps/` directory.

### Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate camera |
| `ESC` | Exit |

### Map Format

A `.cub` file must define the four wall textures, floor color, ceiling color, and the map grid:

```
NO sprites/North.xpm
SO sprites/South.xpm
WE sprites/West.xpm
EA sprites/East.xpm

F 220,100,0
C 225,30,0

111111
100N01
111111
```

Valid map characters: `1` (wall), `0` (empty), `N/S/E/W` (player spawn & direction), ` ` (space outside of playable area).

### Cleaning

```bash
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Full rebuild
```

## Resources

### Ray-Casting & 3D Engine

- [Ray-Casting Tutorial (YouTube) — Lode's Computer Graphics Tutorial walkthrough](https://youtu.be/G9i78WoBBIU?si=5M7URHY-vwa4STI6)
- [Ray-Casting from Scratch (YouTube)](https://youtu.be/gYRrGTC7GtA?si=qajrki9Dj6dRFKs-)
- [DDA Line Generation Algorithm — GeeksforGeeks](https://www.geeksforgeeks.org/computer-graphics/dda-line-generation-algorithm-computer-graphics/)
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the definitive written reference for DDA-based ray-casting
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

### AI Usage

AI (Claude) was used during this project for the following tasks:

- **Debugging**: helping identify off-by-one errors in map parsing and boundary checks, and diagnosing texture coordinate calculation issues.
- **Code review**: reviewing wall collision logic and ray-casting math for correctness.