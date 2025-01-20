#include "flappy_Bird.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace sf;

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    // Create the main window
    RenderWindow window(VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Mi Pirate Flappy Bird");

    // Load textures
    Texture birdTexture, backgroundTexture, topPipeTexture, bottomPipeTexture;
    if (!birdTexture.loadFromFile("flappybird.png") || 
        !backgroundTexture.loadFromFile("flappybirdbg.png") || 
        !topPipeTexture.loadFromFile("toppipe.png") || 
        !bottomPipeTexture.loadFromFile("bottompipe.png")) {
        std::cout << "Error loading textures!" << std::endl;
        return -1;
    }

    // Create game objects
    Bird bird(birdTexture);
    Sprite background(backgroundTexture);
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }

    std::vector<Pipe> pipes;
    Clock clock;
    Time frameDuration = seconds(1.f / FRAME_RATE);
    Time lastUpdateTime = Time::Zero;
    Time lastPipeSpawnTime = Time::Zero;
    bool gameOver = false;
    float score = 0;

    // Game loop
    while (window.isOpen()) {
        Time elapsed = clock.restart();
        lastUpdateTime += elapsed;
        lastPipeSpawnTime += elapsed;

        // Event handling
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                if (gameOver) {
                    // Restart the game
                    bird.sprite.setPosition(BOARD_WIDTH / 8, BOARD_HEIGHT / 2);
                    pipes.clear();
                    gameOver = false;
                    score = 0;
                    lastPipeSpawnTime = Time::Zero;
                }
                bird.jump();
            }
        }

        // Update game logic only if enough time has passed for the current frame
        while (lastUpdateTime >= frameDuration) {
            lastUpdateTime -= frameDuration;

            if (!gameOver) {
                // Bird movement
                bird.move();

                // Pipe movement
                for (auto& pipe : pipes) {
                    pipe.move(-4); // Move pipes leftward
                    if (!pipe.passed && bird.sprite.getPosition().x > pipe.topPipe.getPosition().x + PIPE_WIDTH) {
                        pipe.passed = true;
                        score += 1; // Increase score when pipes pass
                    }
                    if (bird.sprite.getGlobalBounds().intersects(pipe.topPipe.getGlobalBounds()) ||
                        bird.sprite.getGlobalBounds().intersects(pipe.bottomPipe.getGlobalBounds())) {
                        gameOver = true;
                    }
                }

                // Remove pipes that have moved off screen
                pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& pipe) {
                    return pipe.topPipe.getPosition().x + PIPE_WIDTH < 0;
                }), pipes.end());

                // Spawn new pipes at regular intervals
                if (lastPipeSpawnTime >= PIPE_SPAWN_INTERVAL) {
                    pipes.emplace_back(topPipeTexture, bottomPipeTexture);
                    lastPipeSpawnTime = Time::Zero;
                }

                // Game over condition
                if (bird.sprite.getPosition().y > BOARD_HEIGHT) {
                    gameOver = true;
                }
            }
        }

        // Rendering
        window.clear();
        window.draw(background);
        for (const auto& pipe : pipes) {
            window.draw(pipe.topPipe);
            window.draw(pipe.bottomPipe);
        }
        window.draw(bird.sprite);

        // Draw score
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(static_cast<int>(score)));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::White);
        window.draw(scoreText);

        // Game Over screen
        if (gameOver) {
            Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("Game Over! Score: " + std::to_string(static_cast<int>(score)));
            gameOverText.setCharacterSize(30);
            gameOverText.setFillColor(Color::Red);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
