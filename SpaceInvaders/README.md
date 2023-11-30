# Space Invaders Game

This repository contains the source code for a Space Invaders game implemented in C using the Allegro library. The game features a player-controlled spaceship defending against waves of aliens.

## Prerequisites

Before running the game, make sure you have the following dependencies installed:

- Allegro 5 library
- Allegro Image addon
- Allegro Audio addon

## Installation

1. Clone the repository to your local machine:
   ````
   git clone https://github.com/your-username/space-invaders.git
   ```

2. Compile the source code using a C compiler, such as GCC:
   ````
   gcc main.c game.c tiro.c -o space_invaders -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf -lallegro_primitives
   ```

3. Run the game:
   ````
   ./space_invaders
   ```

## Gameplay

- Use the arrow keys to move the spaceship.
- Press the spacebar to shoot bullets and destroy aliens.
- Avoid getting hit by alien bullets and colliding with aliens.
- Your score increases for each alien you destroy.
- You have a limited number of lives. The game ends when you lose all lives.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

- The Space Invaders game concept was originally created by Tomohiro Nishikado.
- This project is based on the work of various contributors to the Allegro library.

