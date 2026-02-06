# miniRT

A minimal ray tracer implementation in C, created as part of the 42 school curriculum. This project renders 3D scenes with basic geometric objects using ray tracing techniques.

## 🎯 Overview

miniRT is a simple ray tracer that can render scenes containing:
- **Spheres** with customizable radius and position
- **Planes** with normal vectors
- **Cylinders** with adjustable height and diameter
- **Ambient lighting** for global illumination
- **Point lights** for directional lighting
- **Camera** with configurable position and orientation

The project implements core ray tracing algorithms including:
- Ray-object intersection calculations
- Phong lighting model
- Anti-aliasing through multi-sampling
- Interactive camera controls

## 🚀 Features

- **Real-time ray tracing** with interactive camera movement
- **Multiple rendering backends**:
  - X11/MiniLibX (Linux native)
  - Raylib (cross-platform)
  - WebAssembly (browser support)
- **Scene file parsing** (.rt format)
- **Phong shading** for realistic lighting
- **Anti-aliasing** support
- **Mouse and keyboard controls** for camera navigation

## 📋 Requirements

### Linux (X11 Backend)
```bash
# Required libraries
sudo apt-get install gcc make
sudo apt-get install libx11-dev libxext-dev
sudo apt-get install libm-dev
```

### Raylib Backend
```bash
# Install Raylib
sudo apt-get install libraylib-dev
# or build from source: https://github.com/raysan5/raylib
```

### WebAssembly
```bash
# Install Emscripten
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

## 🛠️ Installation

1. **Clone the repository**
```bash
git clone https://github.com/zakaria-mourtaban/minirt42.git
cd minirt42
```

2. **Build the project**

For Linux (X11):
```bash
make
```

For Raylib backend:
```bash
make raylib
```

For WebAssembly:
```bash
make wasm
```

## 🎮 Usage

### Running the Program

```bash
./miniRT <scene_file.rt>
```

Example:
```bash
./miniRT tests/simple_scene.rt
```

### Scene File Format

Scene files use the `.rt` extension and follow this format:

```
A  0.2  255,255,255                          # Ambient lighting (ratio, RGB)
C  0,0,0  0,0,1  70                          # Camera (position, orientation, FOV)
L  -40,0,30  0.7  255,255,255                # Light (position, brightness, RGB)

sp 0,0,20  10  255,0,0                       # Sphere (center, diameter, RGB)
pl 0,-10,0  0,1,0  0,255,0                   # Plane (point, normal, RGB)
cy 0,0,20  0,1,0  5  10  0,0,255             # Cylinder (center, axis, diameter, height, RGB)
```

**Format Details:**
- `A`: Ambient light (ratio: 0.0-1.0, color: R,G,B)
- `C`: Camera (position: x,y,z, orientation: x,y,z normalized, FOV: 0-180)
- `L`: Light (position: x,y,z, brightness: 0.0-1.0, color: R,G,B)
- `sp`: Sphere (center: x,y,z, diameter: float, color: R,G,B)
- `pl`: Plane (point: x,y,z, normal: x,y,z normalized, color: R,G,B)
- `cy`: Cylinder (center: x,y,z, axis: x,y,z normalized, diameter: float, height: float, color: R,G,B)

### Controls

**Keyboard:**
- `W/A/S/D`: Move camera forward/left/backward/right
- `SPACE`: Move camera up
- `SHIFT`: Move camera down
- `ESC`: Exit program

**Mouse:**
- Move mouse to rotate camera view

## 🏗️ Project Structure

```
minirt42/
├── source/
│   ├── includes/          # Header files
│   ├── parsing/           # Scene file parsing
│   ├── validation/        # Input validation
│   ├── camera_init.c      # Camera initialization
│   ├── sphere.c           # Sphere intersection
│   ├── plane.c            # Plane intersection
│   ├── cylinder.c         # Cylinder intersection
│   ├── ray.c              # Ray operations
│   ├── vec3*.c            # 3D vector operations
│   ├── color.c            # Color operations
│   ├── phone_lighting.c   # Phong lighting model
│   ├── handle_render.c    # Rendering logic
│   └── main.c             # Entry point
├── libft/                 # Custom C library
├── ft_printf/             # Custom printf implementation
├── minilibx/              # X11 graphics library
├── minilibx_raylib/       # Raylib backend
├── tests/                 # Test scene files
├── Makefile               # Build configuration
└── README.md              # This file
```

## 🧮 Ray Tracing Algorithms

### Ray-Sphere Intersection
Uses quadratic equation to solve for intersection points:
```
t² + 2tb + c = 0
where t is the distance along the ray
```

### Ray-Plane Intersection
Calculates intersection using plane equation:
```
t = (point - ray_origin) · normal / (ray_direction · normal)
```

### Ray-Cylinder Intersection
Combines infinite cylinder intersection with cap checking for finite cylinders.

### Lighting Model
Implements Phong reflection model:
- Ambient component: base lighting
- Diffuse component: angle-dependent lighting
- Specular component: highlights (if implemented)

## 🔧 Technical Details

- **Language**: C (C11 standard)
- **Graphics Libraries**: MiniLibX, Raylib
- **Math**: Custom 3D vector operations
- **Parsing**: Custom .rt file parser
- **Memory Management**: Manual allocation with proper cleanup
- **Rendering**: Single-threaded ray tracing with multi-sampling

## 📚 Learning Outcomes

This project teaches:
- **Computer graphics fundamentals**: Ray tracing, lighting, and rendering
- **Linear algebra**: Vector operations, transformations
- **Geometric algorithms**: Ray-object intersection tests
- **File parsing**: Custom format parsing and validation
- **Graphics programming**: Working with graphics libraries
- **Performance optimization**: Efficient rendering techniques

## 🐛 Known Limitations

- Single-threaded rendering (can be slow for complex scenes)
- No reflection or refraction
- No texture mapping
- Limited anti-aliasing quality
- Basic lighting model

## 🤝 Contributing

This is an educational project for 42 school. While direct contributions are not accepted, feel free to:
- Report bugs via issues
- Suggest improvements
- Fork for your own learning

## 📝 License

This project is part of the 42 school curriculum and follows their academic policies.

## 👥 Author

**zakaria-mourtaban**
- GitHub: [@zakaria-mourtaban](https://github.com/zakaria-mourtaban)

## 🙏 Acknowledgments

- 42 School for the project specifications
- [Ray Tracing in One Weekend](https://raytracing.github.io/) for ray tracing concepts
- MiniLibX and Raylib communities

---

*Made with ☕ at 42 School*