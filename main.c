#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define COLOR_WHITE 0Xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_BLUE 0x34c3eb
#define COLOR_GRAY 0x1f1f1f1f
#define CELL_SIZE 20
#define COLUMNS SCREEN_WIDTH/CELL_SIZE
#define ROWS SCREEN_HEIGHT/CELL_SIZE
#define LINE_WIDTH 2
#define SOLID_TYPE 0
#define WATER_TYPE 1

struct Cell
{
	int type;	// Solido o liquido
	int fill_state;	// Cuanto liquido en esa celda
	int x;
	int y;
};

void draw_cell(SDL_Surface* surface, struct Cell cell)
{
	int pixel_x = cell.x*CELL_SIZE;
	int pixel_y = cell.y*CELL_SIZE;
	SDL_Rect cell_rect = (SDL_Rect){pixel_x, pixel_y, CELL_SIZE, CELL_SIZE};
	Uint32 color = COLOR_WHITE;
	if (cell.type == WATER_TYPE)
		color = COLOR_BLUE;

	SDL_FillRect(surface, &cell_rect, color);
}

void draw_grid(SDL_Surface* surface)
{
	for (int i=0; i<COLUMNS; i++)
	{
		SDL_Rect column = (SDL_Rect) {i*CELL_SIZE, 0, LINE_WIDTH, SCREEN_HEIGHT};
		SDL_FillRect(surface, &column, COLOR_GRAY); 
	}
	for (int j=0; j<ROWS; j++)
	{
		SDL_Rect row = (SDL_Rect) {0, j*CELL_SIZE, SCREEN_WIDTH, LINE_WIDTH};
		SDL_FillRect(surface, &row, COLOR_GRAY); 
	}
	
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Simulador de fluidos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,0);
	
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	draw_grid(surface);

	int simulation_running = 1;
	SDL_Event event;
	int current_type = SOLID_TYPE;
	while(simulation_running)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				simulation_running = 0;
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				if (event.motion.state != 0)
				{
				int cell_x = event.motion.x / CELL_SIZE;
				int cell_y = event.motion.y / CELL_SIZE;
				struct Cell cell = (struct Cell){current_type,0,cell_x,cell_y};
				draw_cell(surface, cell);
				}
			}
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_SPACE)
					current_type = !current_type;
		}

		SDL_Rect rectangle = (SDL_Rect){50,50,100,50};
		SDL_FillRect(surface, &rectangle, COLOR_WHITE);

		SDL_Rect blue_rectangle = (SDL_Rect){150,50,100,50};
		SDL_FillRect(surface, &blue_rectangle, COLOR_BLUE);
		SDL_UpdateWindowSurface(window);

		SDL_Delay(100);

	}

}
