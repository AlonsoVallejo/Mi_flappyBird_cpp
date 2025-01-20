# Flappy Bird Clone

This is a simple clone of the popular game "Flappy Bird" made using SFML.

## Game Description

In this game, you control a bird that tries to fly between sets of pipes without colliding with them. The bird can jump to avoid the pipes by pressing the spacebar. The game keeps track of your score, which increases each time you successfully pass between pipes. If you collide with a pipe or the ground, the game is over.

This code in c++ was based in the work done by Kenny Yip Coding in Java:

https://www.youtube.com/watch?v=Xw2MEG-FBsE&t=149s
https://github.com/ImKennyYip/flappy-bird-java

## How to Run the Game

### Prerequisites

Make sure you have the following installed:
- [SFML](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library)
- A C++ compiler (e.g., `g++`)

### Compilation

To compile the game, follow these steps:

1. Open your terminal or command prompt.
2. Navigate to the directory where your source files are located.
3. Run the following command to compile the code:

    ```sh
    g++ flappyBirdApp.cpp flappyBird.cpp -o flappyBird -lsfml-graphics -lsfml-window -lsfml-system
    ```

### Running the Game

After successfully compiling the code, you can run the game with the following command:

```sh
./flappyBird
