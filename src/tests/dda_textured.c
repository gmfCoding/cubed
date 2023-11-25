#include <mlx.h>
#include <math.h>
#include <stdbool.h>

#include "input.h"
#include "texture.h"
#define SCR_WIDTH 1280
#define SCR_HEIGHT 720

#define mapWidth 24
#define mapHeight 24

/*
	This file is an almost verbtim implementation of the untextured raycaster
	from https://lodev.org/cgtutor/raycasting.html
*/

int worldMap[mapWidth][mapHeight] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
#include "cubed.h"
#include "vector2i.h"
typedef struct s_dda2 t_dda2;
struct s_dda2
{
	t_vec2 delta;
	t_vec2i map;
	t_vec2i step;
	t_vec2 side;
};

void measure_frame_rate2()
{
	static int64_t timeprev = 0;
	//printf("1.0 / (%ld - %ld / 1000000.0)", time_get_ms(), timeprev);
	printf("fps:%f\n", 1.0 / ((time_get_ms() - timeprev) / 1000000.0));
	timeprev = time_get_ms();
}

//t_vec2 stepSize = {sqrt(1 + rayDir.y / rayDir.x * rayDir.y / rayDir.x), sqrt(1 + rayDir.x / rayDir.y * rayDir.x / rayDir.y)};
int	map_index2(int x, int y)
{
	return (x + y * mapWidth);
}

typedef struct s_game2
{
	t_app app;
	t_texture rt0;

	double posX, posY;	   // x and y start position
	double dirX, dirY;	   // initial direction vector
	double planeX, planeY; // the 2d raycaster version of camera plane
	double moveSpeed;
	double rotSpeed;

	t_inputctx input;
} t_game2;

void render2(t_game2 *game)
{
	dda_controls(game);
	texture_clear(game->rt0);
	for (int x = 0; x < SCR_WIDTH; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double)SCR_WIDTH - 1; // x-coordinate in camera space
		double rayDirX = game->dirX + game->planeX * cameraX;
		double rayDirY = game->dirY + game->planeY * cameraX;

		// which box of the map we're in
		int mapX = (int)(game->posX);
		int mapY = (int)(game->posY);


		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;	 // was a NS or a EW wall hit?

		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(SCR_HEIGHT / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCR_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCR_HEIGHT / 2;
		if (drawEnd >= SCR_HEIGHT)
			drawEnd = SCR_HEIGHT - 1;

		int color;
		switch (worldMap[mapX][mapY])
		{
		case 1:
			color = 0xFF0000;
			break; // red
		case 2:
			color = 0x00FF00;
			break; // green
		case 3:
			color = 0x0000FF;
			break; // blue
		case 4:
			color = 0xFFFFFF;
			break; // white
		default:
			color = 0xFFFF00;
			break; // yellow
		}
		// give x and y sides different brightness
		if (side == 1)
		{
			color = color / 2;
		}
		while (drawStart < drawEnd)
			pixel_set(game->rt0, x, drawStart++, color);
	}
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->rt0.img, 0, 0);
	usleep(16666);
	input_process(&game->input);
	measure_frame_rate(game->app);
}

void dda_controls(t_game2 *game)
{
	if (input_keyheld(&game->input, KEY_W))
	{
		if (worldMap[(int)(game->posX + game->dirX * game->moveSpeed)][(int)game->posY] == false)
			game->posX += game->dirX * game->moveSpeed;
		if (worldMap[(int)game->posX][(int)(game->posY + game->dirY * game->moveSpeed)] == false)
			game->posY += game->dirY * game->moveSpeed;
	}
	if (input_keyheld(&game->input, KEY_S))
	{
		if (worldMap[(int)(game->posX - game->dirX * game->moveSpeed)][(int)game->posY] == false)
			game->posX -= game->dirX * game->moveSpeed;
		if (worldMap[(int)game->posX][(int)(game->posY - game->dirY * game->moveSpeed)] == false)
			game->posY -= game->dirY * game->moveSpeed;
	}
	if (input_keyheld(&game->input, KEY_D))
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
		game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
	}
	if (input_keyheld(&game->input, KEY_A))
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
		game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
		game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game2 game;
	game = (t_game2){0};
	game.app.mlx = mlx_init();
	game.app.win = mlx_new_window(game.app.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");
	game.rt0 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);

	game.posX = 22;
	game.posY = 12; // x and y start position
	game.dirX = -1;
	game.dirY = 0; // initial direction vector
	game.planeX = 0;
	game.planeY = 0.66; // the 2d raycaster version of camera plane
	game.moveSpeed = 1.0 / 60.0 * 5.0; // the constant value is in squares/second
	game.rotSpeed = 1.0 / 60.0 * 3.0;  // the constant value is in radians/second

	input_setup(game.app.mlx, game.app.win, &game.input);
	mlx_loop_hook(game.app.mlx, (void *)render2, &game);

	mlx_loop(game.app.mlx);
}