#include <mlx.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "input.h"
#include "texture.h"
#include "cubed.h"
#include "vector2i.h"
/*
	This file is an almost verbtim implementation of the textured raycaster
	from https://lodev.org/cgtutor/raycasting.html
*/

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
	{
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
		{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
		{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
		{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
		{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

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
	// printf("1.0 / (%ld - %ld / 1000000.0)", time_get_ms(), timeprev);
	printf("fps:%f\n", 1.0 / ((time_get_ms() - timeprev) / 1000000.0));
	timeprev = time_get_ms();
}

// t_vec2 stepSize = {sqrt(1 + rayDir.y / rayDir.x * rayDir.y / rayDir.x), sqrt(1 + rayDir.x / rayDir.y * rayDir.x / rayDir.y)};
int map_index2(int x, int y)
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

	t_texture textures[8];
} t_game2;

void generate_textures(t_game2 *game)
{
	game->textures[0] = texture_create(game->app.mlx, texWidth, texHeight);
	game->textures[1] = texture_create(game->app.mlx, texWidth, texHeight);
	game->textures[2] = texture_create(game->app.mlx, texWidth, texHeight);
	game->textures[3] = texture_create(game->app.mlx, texWidth, texHeight);
	game->textures[4] = texture_create(game->app.mlx, texWidth, texHeight);
	game->textures[5] = texture_create(game->app.mlx, texWidth, texHeight);
	game->textures[6] = texture_create(game->app.mlx, texWidth, texHeight);
	game->textures[7] = texture_create(game->app.mlx, texWidth, texHeight);
	// generate some textures
	for (int x = 0; x < texWidth; x++)
	{
		for (int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			// int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			pixel_set(game->textures[0], x, y, 65536 * 254 * (x != y && x != texWidth - y));  // flat red texture with black cross
			pixel_set(game->textures[1], x, y, xycolor + 256 * xycolor + 65536 * xycolor);	  // sloped greyscale
			pixel_set(game->textures[2], x, y, 256 * xycolor + 65536 * xycolor);			  // sloped yellow gradient
			pixel_set(game->textures[3], x, y, xorcolor + 256 * xorcolor + 65536 * xorcolor); // xor greyscale
			pixel_set(game->textures[4], x, y, 256 * xorcolor);								  // xor green
			// pixel_set(game->textures[5], x, y, 65536 * 192 * (x % 16 && y % 16)); //red bricks
			pixel_set(game->textures[5], x, y, (int)(x / 64.0 * 255) << 8 | (int)(y / 64.0 * 255) << 16);
			pixel_set(game->textures[6], x, y, 65536 * ycolor);				   // red gradient
			pixel_set(game->textures[7], x, y, 128 + 256 * 128 + 65536 * 128); // flat grey texture
		}
	}
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

		// texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; // 1 subtracted from it so that texture 0 can be used!
		// calculate value of wallX
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = game->posY + perpWallDist * rayDirY;
		else
			wallX = game->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// Calculate height of line to draw on screen
		int lineHeight = (int)(SCR_HEIGHT / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCR_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCR_HEIGHT / 2;
		if (drawEnd >= SCR_HEIGHT)
			drawEnd = SCR_HEIGHT - 1;
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - SCR_HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = pixel_get(game->textures[texNum], texX, texY);
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			pixel_set(game->rt0, x, drawStart++, color);
		}
	}
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->rt0.img, 0, 0);

	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[0].img, 0, 0);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[1].img, texWidth * 1, 0);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[2].img, texWidth * 2, 0);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[3].img, texWidth * 3, 0);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[4].img, texWidth * 4, 0);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[5].img, texWidth * 5, 0);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[6].img, texWidth * 6, 0);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->textures[7].img, texWidth * 7, 0);
	usleep(6666);
	input_process(&game->input);
	measure_frame_rate(game->app);
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
	game.posY = 11.5; // x and y start position
	game.dirX = -1;
	game.dirY = 0; // initial direction vector
	game.planeX = 0;
	game.planeY = 0.5;				   // the 2d raycaster version of camera plane
	game.moveSpeed = 1.0 / 60.0 * 5.0; // the constant value is in squares/second
	game.rotSpeed = 1.0 / 60.0 * 3.0;  // the constant value is in radians/second
	generate_textures(&game);
	input_setup(game.app.mlx, game.app.win, &game.input);
	mlx_loop_hook(game.app.mlx, (void *)render2, &game);

	mlx_loop(game.app.mlx);
}