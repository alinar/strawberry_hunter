#pragma once
#include "game_engine.h"

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <iostream>
#undef main

struct Engine {
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Texture *textures[50];
  uint32_t currentTexture = 0;

  struct {
    bool quit, left, right, space;
  } keys;
} game_engine;

void initEngine(const char* name,uint32_t width, uint32_t height) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    exit(1);
  }
  if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    printf("Warning: Linear texture filtering not enabled!");
    exit(1);
  }
  game_engine.window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if(game_engine.window == nullptr) {
    printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    exit(1);
  }
  game_engine.renderer = SDL_CreateRenderer(game_engine.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(game_engine.renderer == nullptr) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_SetRenderDrawColor(game_engine.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    exit(1);
  }
}

void destroyEngine() {
  for(uint32_t i = 0; i < game_engine.currentTexture; i++)
    SDL_DestroyTexture(game_engine.textures[i]);
  SDL_DestroyRenderer(game_engine.renderer);
  SDL_DestroyWindow(game_engine.window);
  game_engine = {};
}

Sprite loadSprite(const char *path) {
  SDL_Texture* newTexture = nullptr;
  SDL_Surface* loadedSurface = IMG_Load(path);
  if(loadedSurface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    exit(1);
  }
  Sprite sprite = {};
  game_engine.textures[game_engine.currentTexture] = SDL_CreateTextureFromSurface(game_engine.renderer, loadedSurface);
  sprite.textureId = game_engine.currentTexture;
  ++game_engine.currentTexture;

  sprite.width = loadedSurface->w;
  sprite.height = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);
  return sprite;
}

void drawSprite(const Sprite &sprite, uint32_t x, uint32_t y) {
  SDL_Rect renderQuad = { int32_t(x), int32_t(y), int32_t(sprite.width), int32_t(sprite.height) };
  SDL_RenderCopy(game_engine.renderer, game_engine.textures[sprite.textureId], nullptr, &renderQuad);
}

void drawSpriteWithRotation(const Sprite &sprite, uint32_t x, uint32_t y, float angle, float rotationPointx, float rotationPointy) {
  SDL_Rect renderQuad = { int32_t(x), int32_t(y), int32_t(sprite.width), int32_t(sprite.height) };
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Point center = { int32_t(rotationPointx), int32_t(rotationPointy) };
  SDL_RenderCopyEx(game_engine.renderer, game_engine.textures[sprite.textureId], nullptr, &renderQuad, angle, &center, flip);
}

void sleep(uint32_t ms) {
  SDL_Delay(ms);
}

bool isKeydown(Keys key) {
  switch(key) {
  case LEFT:
    return game_engine.keys.left;
    break;
  case RIGHT:
    return game_engine.keys.right;
    break;
  case SPACE:
    return game_engine.keys.space;
    break;
  default:
    printf("key is not supported\n");
    exit(1);
    return false;
  }
}

uint32_t currentTimeInMs() {
  return SDL_GetTicks();
}

bool startFrame() {
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type) {
    case SDL_QUIT:
      game_engine.keys.quit = true; break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
      case SDLK_LEFT: game_engine.keys.left = true; break;
      case SDLK_RIGHT: game_engine.keys.right = true; break;
      case SDLK_SPACE: game_engine.keys.space = true; break;
      }
      break;
    case SDL_KEYUP:
      switch(event.key.keysym.sym) {
      case SDLK_LEFT: game_engine.keys.left = false; break;
      case SDLK_RIGHT: game_engine.keys.right = false; break;
      case SDLK_SPACE: game_engine.keys.space = false; break;
      }
    }
  }
  if(game_engine.keys.quit){
  return false;
  }
  return true;
}

void presentFrame() {
  SDL_RenderPresent(game_engine.renderer);
}
