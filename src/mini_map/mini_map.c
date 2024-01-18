#include "state.h"
#include "mini_map.h"
#include <mlx.h>
#include <stdlib.h>

int mapX=6,mapY=6,mapS=32,mapSS=24;

# define MAP_WIDTH 6
# define MAP_HEIGHT 6
# define MAP_POS_X 120
# define MAP_POS_Y 820
int map1[MAP_WIDTH * MAP_HEIGHT] = 
{
	1,1,1,1,1,1,
	1,0,0,0,0,1,
	1,0,0,0,0,1,
	1,0,1,1,0,1,
	1,0,0,0,0,1,
	1,1,1,1,1,1,
};
/*
struct s_player
{
	t_vec2 pos;
	t_vec2 dir;
	t_vec2 plane;

	double moveSpeed;
	double rotSpeed;
};
*/

void mlx_draw_line(void *mlx, void *win, float x1, float y1, float x2, float y2, int color)
{
	mlx_pixel_put(mlx, win, (x1*32)+MAP_POS_X, (y1*32)+MAP_POS_Y, color);
	mlx_string_put (mlx, win, ((x1*32)-1.5)+MAP_POS_X, ((y1*32)+3)+MAP_POS_Y, 0xffffff, "o");
	int dx = (x2*32) - (x1*32);
	int dy = (y2*32) - (y1*32);
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float xIncrement = (float)dx / (float)steps;
	float yIncrement = (float)dy / (float)steps;
	float x = x1*32;
	float y = y1*32;
	for (int i = 0; i < steps; i++)
	{
		x += xIncrement;
		y += yIncrement;
		mlx_pixel_put(mlx, win, (int)x+MAP_POS_X, (int)y+MAP_POS_Y, color);
	}
}

void draw_player(t_game *game)
{
    // Draw a line indicating player direction
    //
   // printf("player x %f player y %f\n", game->player.pos.x, game->player.pos.y);
    float lineEndX = game->player.pos.x + game->player.dir.x * 0.2;
    float lineEndY = game->player.pos.y + game->player.dir.y * 0.2;

    // Draw a line from (player_pos_x, player_pos_y) to (lineEndX, lineEndY)
    mlx_draw_line(game->app.mlx, game->app.win, game->player.pos.x, game->player.pos.y, lineEndX, lineEndY, 0xFFFFFF);
}

void drawMap2D(t_game *game)
{
    int x, y, xo, yo;
    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map1[y * mapX + x] == 1)
            {
                mlx_pixel_put(game->app.mlx, game->app.win, ((x * mapS)+MAP_POS_X)-(game->player.pos.x*mapS), ((y * mapS)+MAP_POS_Y)-(game->player.pos.y*mapS), 0xFFFFFF);
            }
            else
            {
                mlx_pixel_put(game->app.mlx, game->app.win, ((x * mapS)+MAP_POS_X)-(game->player.pos.x*mapS), ((y * mapS)+MAP_POS_Y)-(game->player.pos.y*mapS), 0x000000); // Black for 0
            }

            // Draw horizontal lines
            if (x < mapX - 1 && map1[y * mapX + x] != map1[y * mapX + x + 1])
            {
                for (xo = 0; xo < mapS; xo++)
                {
                    mlx_pixel_put(game->app.mlx, game->app.win, (((x + 1) * mapS - 1)+MAP_POS_X)-(game->player.pos.x*mapS), ((y * mapS + xo)+MAP_POS_Y)-(game->player.pos.y*mapS), 0xFFFFFF);
                }
            }

            // Draw vertical lines
            if (y < mapY - 1 && map1[y * mapX + x] != map1[(y + 1) * mapX + x])
            {
                for (yo = 0; yo < mapS; yo++)
                {
                    mlx_pixel_put(game->app.mlx, game->app.win, ((x * mapS + yo)+MAP_POS_X)-(game->player.pos.x*mapS), (((y + 1) * mapS - 1)+MAP_POS_Y)-(game->player.pos.y*mapS), 0xFFFFFF);
                }
            }
        }
    }
}

/*
void mlx_draw_line(void *mlx, void *win, float x1, float y1, float x2, float y2, int color)
{
	mlx_pixel_put(mlx, win, (x1*32)+MAP_POS_X, (y1*32)+MAP_POS_Y, color);
	mlx_string_put (mlx, win, ((x1*32)-1.5)+MAP_POS_X, ((y1*32)+3)+MAP_POS_Y, 0xffffff, "o");
	int dx = (x2*32) - (x1*32);
	int dy = (y2*32) - (y1*32);
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float xIncrement = (float)dx / (float)steps;
	float yIncrement = (float)dy / (float)steps;
	float x = x1*32;
	float y = y1*32;
	for (int i = 0; i < steps; i++)
	{
		x += xIncrement;
		y += yIncrement;
		mlx_pixel_put(mlx, win, (int)x+MAP_POS_X, (int)y+MAP_POS_Y, color);
	}
}

void draw_player(t_game *game)
{
    // Draw a line indicating player direction
    //
   // printf("player x %f player y %f\n", game->player.pos.x, game->player.pos.y);
    float lineEndX = game->player.pos.x + game->player.dir.x * 0.2;
    float lineEndY = game->player.pos.y + game->player.dir.y * 0.2;

    // Draw a line from (player_pos_x, player_pos_y) to (lineEndX, lineEndY)
    mlx_draw_line(game->app.mlx, game->app.win, game->player.pos.x, game->player.pos.y, lineEndX, lineEndY, 0xFFFFFF);
}

void drawMap2D(t_game *game)
{
    int x, y, xo, yo;
    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map1[y * mapX + x] == 1)
            {
                mlx_pixel_put(game->app.mlx, game->app.win, (x * mapS)+MAP_POS_X, (y * mapS)+MAP_POS_Y, 0xFFFFFF);
            }
            else
            {
                mlx_pixel_put(game->app.mlx, game->app.win, (x * mapS)+MAP_POS_X, (y * mapS)+MAP_POS_Y, 0x000000); // Black for 0
            }

            // Draw horizontal lines
            if (x < mapX - 1 && map1[y * mapX + x] != map1[y * mapX + x + 1])
            {
                for (xo = 0; xo < mapS; xo++)
                {
                    mlx_pixel_put(game->app.mlx, game->app.win, ((x + 1) * mapS - 1)+MAP_POS_X, (y * mapS + xo)+MAP_POS_Y, 0xFFFFFF);
                }
            }

            // Draw vertical lines
            if (y < mapY - 1 && map1[y * mapX + x] != map1[(y + 1) * mapX + x])
            {
                for (yo = 0; yo < mapS; yo++)
                {
                    mlx_pixel_put(game->app.mlx, game->app.win, (x * mapS + yo)+MAP_POS_X, ((y + 1) * mapS - 1)+MAP_POS_Y, 0xFFFFFF);
                }
            }
        }
    }
}
*/















void	*get_image(t_game *game, bool t, bool l, bool r, bool b)
{
	void *img;
	int	width;
	int 	height;

	if (t == false && l == false && r == false && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm19.xpm", &width, &height));
	if (t == true && l == false && r == false && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm17.xpm", &width, &height));
	if (t == false && l == true && r == false && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm18.xpm", &width, &height));
	if (t == false && l == false && r == true && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm16.xpm", &width, &height));
	if (t == false && l == false && r == false && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm15.xpm", &width, &height));
	if (t == true && l == true && r == false && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm09.xpm", &width, &height));
	if (t == true && l == false && r == true && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm08.xpm", &width, &height));
	if (t == false && l == true && r == false && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm10.xpm", &width, &height));
	if (t == false && l == false && r == true && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm07.xpm", &width, &height));
	if (t == true && l == false && r == false && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm00.xpm", &width, &height));
	if (t == false && l == true && r == true && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm01.xpm", &width, &height));

	if (t == true && l == true && r == true && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm02.xpm", &width, &height));
	if (t == false && l == true && r == true && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm06.xpm", &width, &height));
	if (t == true && l == false && r == true && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm03.xpm", &width, &height));
	if (t == true && l == true && r == false && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm05.xpm", &width, &height));
	if (t == true && l == true && r == true && b == false)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm04.xpm", &width, &height));
	if (t == true && l == true && r == true && b == true)
		return(mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mm02.xpm", &width, &height));
	return(NULL);
}

void	*set_img_surround(t_game *game, int pos)
{

	bool t=false,l=false,r=false,b=false;
	
	if(pos-mapX >= 0 && map1[pos-mapX] == 1)
		t = true;
	if(pos-1 >= 0 && map1[pos-1] == 1 && pos % mapX != 0)
		l = true;
	if(pos+1 < (mapX*mapY) && map1[pos+1] == 1 && (pos + 1) % mapX != 0)
		r = true;
	if(pos+mapX < (mapX*mapY) && map1[pos+mapX] == 1)
		b = true;
	
	return(get_image(game,t,l,r,b));

}

int outside_map_circle(int x, int y)
{
	if (x < MAP_POS_X-85 && y < MAP_POS_Y-85)
		return (0);
	if (x > MAP_POS_X+70 && y > MAP_POS_Y+70)
		return (0);
	if (x < MAP_POS_X-85 && y > MAP_POS_Y+70)
		return (0);
	if (x > MAP_POS_X+70 && y < MAP_POS_Y-85)
		return (0);
	return (1);

}

void draw_map2D(t_game *game)
{
    int x, y;
    int width, height;
    void	*img;
    int textureSize = 24;

    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            int screenX = x * mapSS + MAP_POS_X;
            int screenY = y * mapSS + MAP_POS_Y;

        	if (map1[y * mapX + x] == 1)
        	{
			if (outside_map_circle(screenX-(game->player.pos.x*mapSS), screenY-(game->player.pos.y*mapSS)) == 1)
			{
                		img = set_img_surround(game, y * mapX + x);
				mlx_put_image_to_window(game->app.mlx, game->app.win, img, \
				screenX-(game->player.pos.x*mapSS), screenY-(game->player.pos.y*mapSS));
			}
        	}
        }
    }
}
/*
void    put_mini_map(t_game *game)
{
        int     i;
        void    *img;
        static int      old_anim_counter;

        old_anim_counter = 0;
        i = 0;
        while(map[i])
        {
                mlx_put_image_to_window(game->mlx, game->win, game->map[i].img, game->map[i].pos_x, game->map[i].pos_y);
        }
}

*/


void	draw_mini_map(t_game *game)
{
//	drawMap2D(game);
//	draw_player(game);	
	int	width;
	int	height;
	void *img;

//	img = mlx_xpm_file_to_image(game->app.mlx, "assets/mini/mmcase.xpm", &width, &height);
//	mlx_put_image_to_window(game->app.mlx, game->app.win, img, MAP_POS_X-128, MAP_POS_Y-128);

	draw_map2D(game);
	mlx_string_put (game->app.mlx, game->app.win, MAP_POS_X, MAP_POS_Y, 0x00ff00, "+");
	
}
