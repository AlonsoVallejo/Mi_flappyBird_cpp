#include "flappy_Bird.h"
#include <cstdlib>

// Pipe class implementation
Pipe::Pipe(Texture& topTexture, Texture& bottomTexture) {
    topPipe.setTexture(topTexture);
    bottomPipe.setTexture(bottomTexture);

    // Scale the pipes
    topPipe.setScale((float)PIPE_WIDTH / topPipe.getLocalBounds().width,
                     (float)PIPE_HEIGHT / topPipe.getLocalBounds().height);
    bottomPipe.setScale((float)PIPE_WIDTH / bottomPipe.getLocalBounds().width,
                        (float)PIPE_HEIGHT / bottomPipe.getLocalBounds().height);

    // Set initial positions
    int pipeY = rand() % (BOARD_HEIGHT / 2);
    topPipe.setPosition(BOARD_WIDTH, pipeY - PIPE_HEIGHT); // Position top pipe at the top
    bottomPipe.setPosition(BOARD_WIDTH, pipeY + PIPE_GAP); // Position bottom pipe with a gap
}

void Pipe::move(int velocityX) {
    topPipe.move(velocityX, 0);
    bottomPipe.move(velocityX, 0);
}

// Bird class implementation
Bird::Bird(Texture& texture) {
    sprite.setTexture(texture);
    
    // Scale the bird
    sprite.setScale((float)BIRD_WIDTH / sprite.getLocalBounds().width, 
                     (float)BIRD_HEIGHT / sprite.getLocalBounds().height);
                     
    sprite.setPosition(BOARD_WIDTH / 8, BOARD_HEIGHT / 2);
}

void Bird::move() {
    velocityY += GRAVITY;
    sprite.move(0, velocityY);
    if (sprite.getPosition().y < 0) sprite.setPosition(sprite.getPosition().x, 0);
}

void Bird::jump() {
    velocityY = BIRD_JUMP;
}
