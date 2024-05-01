#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "ctime"
#include "SDL_mixer.h"
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#pragma comment(lib, "SDL2_mixer.lib")
#define BALL_COUNT 5
#define MUSHROOM_COUNT 5
Mix_Chunk* Sound = NULL;
Mix_Music* fon = NULL;
SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 221,49, 160 };
	SDL_Color back_color = { 0,0,0 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}
void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 0,0, 70, 150 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text2(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 0,0, 55, 100 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void init_balls(SDL_Rect balls[], int count)
{
	for (int i = 0; i < count; i++)
	{
		balls[i] = { i * (rand() % 150 + 1) + 100,i * 100 + 20 ,50 + 10 * i ,50 + 10 * i };
	}
}
void init_balls2(SDL_Rect balls[], int count)
{
	for (int i = 0; i < count; i++)
	{
		int x = rand() % 40;
		balls[i] = { 15,i * 100 + 105 ,50 + x,50 + x };
	}
}
void draw_text_kryg(int k1, SDL_Renderer*& renderer, SDL_Rect balls[], TTF_Font* my_font) {
	char text1[10];
	for (int i = 0; i < 5; i++) {
		k1 = i + 1;
		_itoa_s(k1, text1, 10);
		SDL_Rect rect = { balls[i].x + 10 + i * 2,balls[i].y + 10 + i * 2, balls[i].w - 25 - i * 3, balls[i].h - 25 - i * 3 };
		SDL_Texture* textTexture1 = get_text_texture(renderer, text1, my_font);
		SDL_RenderCopy(renderer, textTexture1, NULL, &rect);
	}
}
void draw_balls(SDL_Renderer*& renderer, SDL_Rect balls[], int count, SDL_Texture* texture) {
	for (int i = 0; i < count; i++)
	{
		if (balls[i].w == 0) continue;
		SDL_RenderCopy(renderer, texture, NULL, &balls[i]);
	}
}
bool is_ball_hit(SDL_Rect ball, int x, int y)
{
	if (ball.w == 0) return false;
	int centerX = ball.x + ball.w / 2;
	int centerY = ball.y + ball.h / 2;
	int radius = ball.w / 2;
	return sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y)) < radius;
}
void loadmusic()
{
	fon = Mix_LoadMUS("fon.wav");
	Mix_PlayMusic(fon, -1);
}
void sound(char* name)
{
	Sound = Mix_LoadWAV(name);
	Mix_PlayChannel(-1, Sound, 0);
}
void draw_fon(SDL_Renderer*& renderer, SDL_Texture* texture) {
	SDL_Rect rect = { 0,0,800,600 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void init_mushrooms(SDL_Rect mushrooms[], int count)
{
	for (int i = 0; i < count; i++)
	{
		int x = rand() % 550;
		mushrooms[i] = { x + i * 50,i * 50 + 205 ,60, 60 };
	}
}
void init_korz(SDL_Rect mushrooms[], int count)
{
	for (int i = 0; i < count; i++)
	{
		int x = rand() % 550;
		mushrooms[i] = { x + i * 50,i * 50 + 205 ,100, 100 };
	}
}
void draw_mushroom(SDL_Renderer*& renderer, SDL_Rect mushrooms[], int count, SDL_Texture* texture) {
	for (int i = 0; i < count; i++)
	{
		if (mushrooms[i].w == 0) continue;
		SDL_RenderCopy(renderer, texture, NULL, &mushrooms[i]);
	}
}
SDL_Texture* get_text_texture2(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 129,94, 66 };
	textSurface = TTF_RenderText_Blended(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}
SDL_Texture* get_text_texture3(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	const char* text1 = "Tries:";
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 129,94, 66 };
	textSurface = TTF_RenderUTF8_Blended(font, text1, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}
void draw_text4(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 25,0, 50, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text3(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 75,0, 50, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void task1( ){
	SDL_Window* window = SDL_CreateWindow("Click the balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Rect balls[BALL_COUNT];
	init_balls(balls, BALL_COUNT);

	SDL_Surface* ballImage = IMG_Load("kryg.bmp");
	SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
	SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
	SDL_FreeSurface(ballImage);

	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("text.ttf", 100);
	SDL_Texture* textTexture;
	int k1 = 0;
	int k = 0;
	char text[10];
	_itoa_s(k, text, 10);
	textTexture = get_text_texture(renderer, text, my_font);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	char music[10] = "music.wav";

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{
				for (int i = 0; i < BALL_COUNT; i++)
				{
					if (is_ball_hit(balls[i], event.button.x, event.button.y))
					{
						sound(music);
						balls[i].w = balls[i].h = 0;
						k += i + 1;
						_itoa_s(k, text, 10);
						SDL_DestroyTexture(textTexture);
						textTexture = get_text_texture(renderer, text, my_font);
					}
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		draw_balls(renderer, balls, BALL_COUNT, ballTexture);
		draw_text(renderer, textTexture);
		draw_text_kryg(k1, renderer, balls, my_font);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(ballTexture);
	TTF_CloseFont(my_font);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void task2() {
	SDL_Window* window = SDL_CreateWindow("Click the balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Rect balls[BALL_COUNT];
	init_balls2(balls, BALL_COUNT);

	SDL_Surface* ballImage = IMG_Load("kryg.bmp");
	SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
	SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
	SDL_FreeSurface(ballImage);

	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("text.ttf", 100);
	SDL_Texture* textTexture;
	int k = 0;
	char text[10];
	_itoa_s(k, text, 10);
	textTexture = get_text_texture(renderer, text, my_font);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	char music[10] = "music.wav";
	int dx=1;
	SDL_Event event;
	bool quit = false;
	loadmusic();
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { quit = true; }
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				for (int i = 0; i < BALL_COUNT; i++)
				{
					if (is_ball_hit(balls[i], event.button.x, event.button.y))
					{
						sound(music);
						balls[i].w = balls[i].h = 0;
						k += i + 1;
						_itoa_s(k, text, 10);
						SDL_DestroyTexture(textTexture);
						textTexture = get_text_texture(renderer, text, my_font);
					}
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		for (int i = 0; i < BALL_COUNT; i++) {
				balls[i].x += dx;
				balls[i].y =50+ i*100+ 40*sin(balls[i].x * 0.01);
				SDL_RenderCopy(renderer, ballTexture, NULL, &balls[i]);
				if (balls[i].x == 800) { quit = true; SDL_Delay(10); }
		}
		SDL_Delay(10);
		draw_balls(renderer, balls, BALL_COUNT, ballTexture);
		draw_text2(renderer, textTexture);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(ballTexture);
	TTF_CloseFont(my_font);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void task3() {
	SDL_Window* window = SDL_CreateWindow("Click the balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Rect mushrooms[MUSHROOM_COUNT];
	SDL_Rect myh[1];
	SDL_Rect klever[1];
	SDL_Rect korzina[1];
	init_mushrooms(mushrooms, MUSHROOM_COUNT);
	init_mushrooms(myh, 1);
	init_mushrooms(klever, 1);
	init_korz(korzina, 1);
	SDL_Surface* fonImage = IMG_Load("polyana.bmp");
	SDL_SetColorKey(fonImage, SDL_TRUE, SDL_MapRGB(fonImage->format, 255, 255, 255));
	SDL_Texture* fonTexture = SDL_CreateTextureFromSurface(renderer, fonImage);

	SDL_Surface* mushroomImage = IMG_Load("grib1.bmp");
	SDL_SetColorKey(mushroomImage, SDL_TRUE, SDL_MapRGB(mushroomImage->format, 255, 255, 255));
	SDL_Texture* mushroomTexture = SDL_CreateTextureFromSurface(renderer, mushroomImage);

	SDL_Surface* myhImage = IMG_Load("myh2.bmp");
	SDL_SetColorKey(myhImage, SDL_TRUE, SDL_MapRGB(myhImage->format, 255, 255, 255));
	SDL_Texture* myhTexture = SDL_CreateTextureFromSurface(renderer, myhImage);

	SDL_Surface* kleverImage = IMG_Load("kleverr.bmp");
	SDL_SetColorKey(kleverImage, SDL_TRUE, SDL_MapRGB(kleverImage->format, 255, 255, 255));
	SDL_Texture* kleverTexture = SDL_CreateTextureFromSurface(renderer, kleverImage);

	SDL_Surface* korzinaImage = IMG_Load("korzina1.bmp");
	SDL_SetColorKey(korzinaImage, SDL_TRUE, SDL_MapRGB(korzinaImage->format, 255, 255, 255));
	SDL_Texture* korzinaTexture = SDL_CreateTextureFromSurface(renderer, korzinaImage);

	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("text.ttf", 100);
	SDL_Texture* textTexture;
	SDL_Texture* textTexture2;
	int k = 0;
	int tries = 3;
	char text[30];
	_itoa_s(tries, text, 10);
	textTexture = get_text_texture2(renderer, text, my_font);
	textTexture2 = get_text_texture3(renderer, text, my_font);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	char music[10] = "music.wav";
	int dx = 1;
	SDL_Event event;
	bool quit = false;
	loadmusic();
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { quit = true; }
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				for (int i = 0; i < BALL_COUNT; i++)
				{
					if (is_ball_hit(mushrooms[i], event.button.x, event.button.y))
					{
						sound(music);
						mushrooms[i].w = mushrooms[i].h = 0;
						k += 5;
						tries -= 1;
						_itoa_s(tries, text, 10);
						SDL_DestroyTexture(textTexture);
						textTexture = get_text_texture2(renderer, text, my_font);
						SDL_DestroyTexture(textTexture2);
						textTexture2 = get_text_texture3(renderer, text, my_font);
					}
					if (is_ball_hit(myh[i], event.button.x, event.button.y))
					{
						sound(music);
						myh[i].w = myh[i].h = 0;
						k -= 5;
						tries -= 1;
						_itoa_s(tries, text, 10);
						SDL_DestroyTexture(textTexture);
						textTexture = get_text_texture2(renderer, text, my_font);
						SDL_DestroyTexture(textTexture2);
						textTexture2 = get_text_texture3(renderer, text, my_font);
					}
					if (is_ball_hit(klever[i], event.button.x, event.button.y))
					{
						sound(music);
						klever[i].w = klever[i].h = 0;
						tries += 3;
						_itoa_s(tries, text, 10);
						SDL_DestroyTexture(textTexture);
						textTexture = get_text_texture2(renderer, text, my_font);
						SDL_DestroyTexture(textTexture2);
						textTexture2 = get_text_texture3(renderer, text, my_font);
					}
					if (is_ball_hit(korzina[i], event.button.x, event.button.y))
					{
						sound(music);
						korzina[i].w = korzina[i].h = 0;
						k += 10;
						tries -= 1;
						_itoa_s(tries, text, 10);
						SDL_DestroyTexture(textTexture);
						textTexture = get_text_texture2(renderer, text, my_font);
						SDL_DestroyTexture(textTexture2);
						textTexture2 = get_text_texture3(renderer, text, my_font);
					}
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		draw_fon(renderer, fonTexture);
		draw_mushroom(renderer, mushrooms, MUSHROOM_COUNT, mushroomTexture);
		draw_mushroom(renderer, myh, 1, myhTexture);
		draw_mushroom(renderer, klever, 1, kleverTexture);
		draw_mushroom(renderer, korzina, 1, korzinaTexture);
		draw_text3(renderer, textTexture);
		draw_text4(renderer, textTexture2);
		SDL_RenderPresent(renderer);
		if (tries == 0) { SDL_Delay(1000); quit = true; }
	}
	SDL_DestroyTexture(mushroomTexture);
	SDL_FreeSurface(mushroomImage);
	SDL_DestroyTexture(fonTexture);
	SDL_FreeSurface(fonImage);
	SDL_RenderPresent(renderer);
	TTF_CloseFont(my_font);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	int t;
	do {
		printf("Введите номер задания (1,2,3) или ноль для выхода: "); scanf_s("%d", &t);
		switch (t) {
		case 1: task1(); break;
		case 2: task2(); break;
		case 3: task3();  break;
		case 0: printf("Выход\n");  break;
		default: break;
		}
	} while (t != 0);
	return 0;
}