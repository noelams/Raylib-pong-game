# Raylib Pong (Single Paddle)

A simple Pong-style arcade game built in **C++** using **raylib**.

Control a single paddle at the bottom of the screen and keep the ball in play as long as possible. Miss the ball and it resets to the center. No score, no win state — just survival.

This project started from the raylib quickstart template and evolved into a small standalone game experiment.

## Gameplay

- One paddle, one ball
- The ball bounces off walls and the paddle
- Missing the ball resets it
- Sound effects play on collisions

The goal is endurance, not victory.

## Controls

- **Left Arrow** — move paddle left
- **Right Arrow** — move paddle right
- **ESC** — quit the game

## Built With

- **C++**
- **raylib**
- raylib audio module for sound effects

## Building and Running

This project uses the standard **raylib quickstart** build setup.

### VS Code (Recommended)

1. Open the project folder in VS Code
2. Ensure a C++ compiler toolchain is installed
3. Run the build task (`Ctrl + Shift + B`)
4. Run the executable from the `bin/` directory

## Assets

Audio files are loaded at runtime from the `resources` directory:

- `collision_sound.wav` — wall collision
- `paddle_sound.mp3` — paddle collision

The game expects the working directory to be set correctly so these files can be found.

## Technical Notes

- Collision uses `CheckCollisionCircleRec`
- Ball movement is frame-rate independent via `GetFrameTime()`
- Audio is handled with raylib’s sound module
- The game is intentionally minimal: one paddle, one ball, no scoring

## License

This project is based on the **raylib quickstart** template.

- raylib quickstart © 2020–2025 Jeffery Myers
- Game code and modifications © your name

The original license terms apply. See the LICENSE file for details.
