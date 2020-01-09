#pragma once

// Global variables /////////////////////////////////////////////////////////////

/* Will be 1 when the program has to exit */
extern int exitApplication;

// Lifetime functions ///////////////////////////////////////////////////////////

/* Call it once at the beginning of main() */
int Init();

/* Call it once per frame (at the beginning of the frame). */
void PreUpdate();

/* Call it once per frame (at the end of the frame) */
void PostUpdate();

/* Call it once at the end of main() */
void CleanUp();


// Functions to draw stuff on screen ////////////////////////////////////////////

#include "SDL/include/SDL_rect.h"

struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

SDL_Texture *LoadTexture(const char *filename);

void UnloadTexture(SDL_Texture *texture);

SDL_Texture* Print(const char* text, SDL_Color color, _TTF_Font* font);

bool CalcSize(const char* text, int& width, int& height, _TTF_Font* font);

void UpdateText(const char* text, SDL_Texture* texture, SDL_Color* color, _TTF_Font* font);

//void GetTextureSize(const SDL_Texture* texture, unsigned int& width, unsigned int& height);

void Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section);

void DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

int SpaceWasPressed();

//_TTF_Font*	font;