# Brotato Clone

A 2D top-down roguelike survival shooter, built in C++ with [raylib](https://www.raylib.com/).
The game is built on top of a small custom engine that lives in the same repo.

## Architecture

A lightweight Unity-style entity component system:

- **`Scene`** owns and drives all entities each frame.
- **`GameObject`** is a container for components.
- **`Component`** defines behavior, subclass it and override `start()`, `update(dt)`, or `draw()`.

```cpp
Scene scene;
GameObject &player = scene.spawn();
player.addComponent<TransformComponent>(x, y);
player.addComponent<VelocityComponent>(speed);
player.addComponent<PlayerInputComponent>();
```

## Build

Requires `clang++`, `make`, and [raylib](https://github.com/raysan5/raylib) (resolved via `pkg-config`).

```sh
make          # release build
make run      # build and run
make debug    # debug build with -g -O0
make sanitize # debug build with AddressSanitizer
make clean    # remove build artifacts
```

## Documentation

API docs are generated from `///` comments in the headers.
Requires [Doxygen](https://www.doxygen.nl/) (and [Graphviz](https://graphviz.org/) for class diagrams).

```sh
make docs                  # generate HTML docs into docs/html/
open docs/html/index.html  # view in browser
```
