#pragma once
#include <cstdint>

struct Sprite {
  uint32_t textureId;
  uint32_t width, height;
};

// Keys for controlling gantry
enum Keys {LEFT, RIGHT, SPACE };

// Check status of key
bool isKeydown(Keys key);
// Initialize engine and bring up window.
void initEngine(uint32_t width, uint32_t height);
// Destroy engine and resources.
void destroyEngine();

// Load given sprite and return handle to resource
Sprite loadSprite(const char *path);

// Draw sprite at given position. Top left corner is (0, 0)
void drawSprite(const Sprite &sprite, uint32_t x, uint32_t y);
// Draw sprite at given position with rotation angle in degrees.
// The rotation point is defined locally with regards to the sprite.
void drawSpriteWithRotation(const Sprite &sprite, uint32_t x, uint32_t y, float angle, float rotationPointx, float rotationPointy);

// Sleep for given milliseconds
void sleep(uint32_t ms);

bool startFrame();
void presentFrame();
uint32_t currentTimeInMs();
