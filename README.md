# so_long

A 2D top-down game written in C using the MiniLibX graphics library as part of the 42 common core curriculum.

## Overview

**so_long** is a simple game where the player navigates a map to collect all items and reach the exit while avoiding enemies. The game features sprite animations, collision detection, and enemy AI.

## Key Features

### Game Mechanics
- **Player Movement**: Navigate the map using arrow keys or WASD
- **Collectibles**: Gather all items on the map to enable the exit
- **Exit**: Reach the exit after collecting all items to win
- **Enemy**: Avoid the bouncing enemy that patrols the map
- **Move Counter**: Tracks the number of moves made during gameplay

### Graphics & Animation
- **Sprite Animation**: Player has directional animations (up, down, left, right)
- **Collectible Animation**: 3-frame collectible animation loop
- **Exit Animation**: 2-frame exit animation
- **64x64 Pixel Tiles**: Standard tile size for consistent rendering

### Map System
- Maps are loaded from `.ber` files (custom map format)
- **Validation**: Maps must be:
  - Rectangular shaped
  - Surrounded by walls
  - Contain exactly one player (P), one exit (E), and at least one collectible (C)
  - Have at least one valid path to the exit
- **Map Elements**:
  - `1` = Wall
  - `0` = Floor/Empty space
  - `C` = Collectible
  - `E` = Exit
  - `P` = Player start position

## Building & Running

### Prerequisites
- GCC compiler
- MiniLibX library (minilibx-linux)
- libft (included in project)

### Compilation
```bash
make          # Compile the project
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Recompile from scratch
```

### Usage
```bash
./so_long maps/map_name.ber
```

## Project Structure

```
.
├── src/              # Main source files
├── includes/         # Header files
├── libft/            # Custom C library (libft + ft_printf + get_next_line)
├── minilibx-linux/   # Graphics library
├── maps/             # Map files (.ber format)
└── Makefile          # Build configuration
```

## Controls

| Key | Action |
|-----|--------|
| Arrow Keys / WASD | Move player |
| ESC / Close Window | Exit game |

## Game Flow

1. Load and validate the map
2. Initialize game window and assets
3. Enter game loop with animations and input handling
4. Render map, player, enemies, and collectibles
5. Win condition: Collect all items and reach the exit
6. Lose condition: Collide with the enemy

## Error Handling

The game validates:
- Correct command-line arguments
- Valid map file format
- Proper map configuration (walls, elements count)
- Image loading and rendering
- Memory allocation

---

*42 Madrid Project | C | MiniLibX*
