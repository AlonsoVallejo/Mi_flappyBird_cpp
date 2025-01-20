#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace sf;

// Game settings
const int BOARD_WIDTH = 360;
const int BOARD_HEIGHT = 640;
const int PIPE_WIDTH = 64;
const int PIPE_HEIGHT = 512;
const int BIRD_WIDTH = 34;
const int BIRD_HEIGHT = 24;
const int GRAVITY = 1;
const float BIRD_JUMP = -9.f;
const int PIPE_GAP = 150;
const int FRAME_RATE = 60; // Target frame rate (FPS)
const Time PIPE_SPAWN_INTERVAL = seconds(1.5f); // Time interval to spawn pipes

class Pipe {
public:
    Sprite topPipe;
    Sprite bottomPipe;
    bool passed = false;

    Pipe(Texture& topTexture, Texture& bottomTexture);
    void move(int velocityX);
};

class Bird {
public:
    Sprite sprite;
    int velocityY = 0;

    Bird(Texture& texture);
    void move();
    void jump();
};

#endif // FLAPPY_BIRD_H
