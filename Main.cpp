#include "Canvas.h"
#include "Image.h"
#include "SDL.h"
#include <iostream>

int main(int, char**)
{
	const unsigned int width = 800;
	const unsigned int height = 600;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("2D Renderer", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Canvas canvas(renderer, width, height);
	Image image1;
	image1.Load("cat.bmp");

	Image image2;
	image2.Load("sus.bmp");

	Image image3;
	image3.Load("color.bmp", 120);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		canvas.Clear({ 0, 0, 0, 255 });

		// point
		for (int i = 0; i < 20; i++)
		{
			canvas.DrawPoint({ rand() % width, rand() % height }, { 255, 255, 255, 255 });
		}

		// rect
		for (int i = 0; i < 5; i++)
		{
			canvas.DrawRect({ rand() % width, rand() % height, rand() % 100, rand() % 100 }, { 255, 0, 255, 255 });
		}

		// line
		for (int i = 0; i < 5; i++)
		{
			canvas.DrawLine({ rand() % width, rand() % height }, { rand() % width, rand() % height }, { 255, 255, 255, 255 });
		}

		// line list
		std::vector<SDL_Point> points;
		for (int i = 0; i < 20; i++) points.push_back({ rand() % width, rand() % height });
		canvas.DrawLineList(points, { 0, 255, 0, 255 });

		// triangle
		for (int i = 0; i < 5; i++)
		{
			canvas.DrawTriangle({ rand() % width, rand() % height },
				{ rand() % width, rand() % height },
				{ rand() % width, rand() % height },
				{ 255, 255, 0, 255 });
		}

		// circle
		for (int i = 0; i < 10; i++)
		{
			canvas.DrawCircle({ rand() % width, rand() % height }, { rand() % 30 }, { 0, 255, 255, 255 });
		}

		canvas.DrawImage(&image1, { 100, 100 });
		canvas.DrawImage(&image2, { 250, 250 }, {0, 255, 0, 255});
		canvas.DrawImage(&image3, { 200, 200 });

		canvas.Update();

		SDL_RenderClear(renderer);
		canvas.Draw(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}
