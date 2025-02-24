# Cub3D
10th project for 42cursus

## Concepts
- Raycasting
  - DDA
- File Parsing
- Map check, Floodfill

## Implementation
- Render 3D view from 2D map using MiniLibX

### .cub File
a scene description file with the .cub extension as first argument
> [!NOTE] print errors
> If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.
- 地図は必ずファイル末尾、その他は順不同
- 地図以外は、一個以上の改行あり
- テクスチャ
  - Path to XPM file for wall textures
  - 識別子の後にファイルのパス NO, SO, WE, EA
- F = Floor (床)の色 R,G,B　それぞれ[0~255]
- C = Ceiling (天井)の色 R,G,B　それぞれ[0~255]
- Valid map
  - 0 = empty space in wall
  - 1 = wall
  - N, S, E, W for player position and orientation
  - Enclosed by wall
  - doesn't have to be rectangular

### Key Movement
- W - move forward
- A - move left
- S - move backward
- D - move right
- LEFT ARROW - turn left
- RIGHT ARROW - turn right
- ESC - exit game
