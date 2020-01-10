#include "sdl_functions.h"
#include "Log.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "SDL_ttf\include\SDL_ttf.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

// Configuration
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 1650
#define SCREEN_HEIGHT 1050
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 1
#define REN_VSYNC 1

//The window we'll be rendering to
SDL_Window* window = nullptr;

//The surface contained by the window
SDL_Surface* screen_surface = nullptr;

//The renderer
SDL_Renderer* renderer = nullptr;



// Textures
#define MAX_TEXTURES 150
SDL_Texture* textures[MAX_TEXTURES] = {};

// Exit application?
int exitApplication = 0;

int Init()
{
	LOG("Init SDL window & surface");

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error:\n");
		LOG(SDL_GetError());
		return 0;
	}

	//Create window
	int width = SCREEN_WIDTH * SCREEN_SIZE;
	int height = SCREEN_HEIGHT * SCREEN_SIZE;
	unsigned int flags = SDL_WINDOW_SHOWN;

	if (WIN_FULLSCREEN == true)
		flags |= SDL_WINDOW_FULLSCREEN;

	if (WIN_BORDERLESS == true)
		flags |= SDL_WINDOW_BORDERLESS;

	if (WIN_RESIZABLE == true)
		flags |= SDL_WINDOW_RESIZABLE;

	if (WIN_FULLSCREEN_DESKTOP == true)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	LOG("Creating Window");
	window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	if (window == NULL)
	{
		LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	//Get window surface
	screen_surface = SDL_GetWindowSurface(window);

	LOG("Creating Renderer context");
	flags = 0;

	if (REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(window, -1, flags);
	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT); //Uncomment to have fullscreen

	LOG("Init SDL input event system");

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	LOG("Init Image library");

	// load support for the PNG image format
	flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		return 0;
	}

	if (TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}
	else
	{
		//font = Load("Assets/Fonts/Minecraftia-Regular.ttf", 12);
	}

	return 1;
}

const Uint8* PreUpdate()
{
	SDL_RenderClear(renderer);

	SDL_Event Events;
	while (SDL_PollEvent(&Events))
	{
		if (Events.type == SDL_QUIT)
			exitApplication = 1;
	}

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	/*for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}*/

	
	
	return keys;
}

void PostUpdate()
{
	SDL_RenderPresent(renderer);
}

void CleanUp()
{
	LOG("Freeing textures and Image library");
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		if (textures[i] != nullptr)
			textures[i] = nullptr;
	}
	IMG_Quit();

	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	LOG("Destroying renderer");
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	LOG("Destroying SDL window and quitting all SDL systems");
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}

// Load new texture from file path
SDL_Texture* LoadTexture(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == NULL)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			bool room = false;
			for (int i = 0; i < MAX_TEXTURES; ++i)
			{
				if (textures[i] == nullptr)
				{
					textures[i] = texture;
					room = true;
					break;
				}
			}
			if (room == false)
				LOG("Texture buffer overflow");
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

//void GetTextureSize(const SDL_Texture* texture, uint& width, uint& height)
//{
//	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
//}

void UnloadTexture(SDL_Texture * texture)
{
	if (texture != nullptr)
	{
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (textures[i] == texture)
			{
				textures[i] = nullptr;
				break;
			}
		}
		SDL_DestroyTexture(texture);
	}
}

// Blit to screen
void Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float angle)
{
	SDL_Rect rect;
	rect.x = x * SCREEN_SIZE;
	rect.y = y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	SDL_Point rotationPoint;
	rotationPoint.x = rect.w/2;
	rotationPoint.y =  rect.h/2;

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, &rotationPoint, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
	}
}

void DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

int SpaceWasPressed()
{
	/*if (keyboard[SDL_SCANCODE_SPACE])
		return 1;
	else
		return 0;*/
	return 0;
}

// Print text using font
SDL_Texture* Print(const char* text, SDL_Color color, _TTF_Font* font)
{
	SDL_Texture* ret = NULL;
	SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);

	if (surface == NULL)
	{
		LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		ret = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	return ret;
}

// calculate size of a text
bool CalcSize(const char* text, int& width, int& height, _TTF_Font* font) 
{
	bool ret = false;

	if (TTF_SizeText(font, text, &width, &height) != 0)
	{
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		ret = true;
	}
	return ret;
}

void UpdateText(const char* text,SDL_Texture* texture,SDL_Color* color,_TTF_Font* font)
{
	SDL_DestroyTexture(texture);

	texture = Print(text, *color, font);
}