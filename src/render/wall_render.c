#include "cubed.h"
#include "vector2.h"
#include "vector2i.h"

typedef struct s_vertical
{
	int			x;
	double		camera_x;
	t_vec2		dir;
	t_rayinfo	ray;

}			t_vertical;

typedef struct s_column
{
	int		texture;
	int		shaded;
	double	sample_dy;
	int		x;
	t_vec2	uv;
	t_vec2i	sample;
	t_vec2i	range;
}			t_column;

t_column	calculate_column(t_game *game, t_vertical *vertical, t_hitpoint hit)
{
	t_column	col;
	int			height;

	col.texture = texmap[hit.x + MAP_WIDTH * hit.y] - 1;
	col.uv.x = game->player.pos.x + hit.depth * vertical->dir.x;
	if (hit.side == 0)
		col.uv.x = game->player.pos.y + hit.depth * vertical->dir.y;
	col.uv.x -= floor(col.uv.x);
	col.sample.x = (int)(col.uv.x * (double)WALL_TEX_SIZE);
	if (hit.side == 0 && vertical->dir.x > 0)
		col.sample.x = WALL_TEX_SIZE - col.sample.x - 1;
	if (hit.side == 1 && vertical->dir.y < 0)
		col.sample.x = WALL_TEX_SIZE - col.sample.x - 1;
	height = (int)(R_HEIGHT / hit.depth);
	col.range.s = -height / 2 + R_HEIGHT / 2;
	if (col.range.s < 0)
		col.range.s = 0;
	col.range.e = height / 2 + R_HEIGHT / 2;
	if (col.range.e >= R_HEIGHT)
		col.range.e = R_HEIGHT - 1;
	col.sample_dy = 1.0 * WALL_TEX_SIZE / height;
	col.uv.y = (col.range.s - R_HEIGHT / 2 + height / 2) * col.sample_dy;
	col.shaded = hit.side == 1;
	return (col);
}

void	render_column(t_game *game, t_column col)
{
	int	f;
	int	s;
	int	y;

	y = col.range.s;
	while (++y < col.range.e)
	{
		col.sample.y = (int)col.uv.y & (WALL_TEX_SIZE - 1);
		f = pixel_get(game->textures[col.texture], col.sample.x, col.sample.y);
		if ((f & M_APLHA) != R_ALPHA)
		{
			s = pixel_get(game->rt0, col.x, y);
			f = colour_blend(f, s);
		}
		col.uv.y += col.sample_dy;
		if (col.shaded == 1)
			f = (f >> 1) & 0x7F7F7F;
		pixel_set(game->rt0, col.x, y, R_ALPHA | f);
	}
}

void	render_vertical(t_game *game, t_vertical info)
{
	t_column	col;
	int			d;

	d = info.ray.hits;
	while (--d >= 0)
	{
		col = calculate_column(game, &info, info.ray.depths[d]);
		col.x = info.x;
		render_column(game, col);
	}
}

void render_wall(t_game *game)
{
	t_vertical	vert;

	vert.x = -1;
	while (++vert.x < R_HEIGHT)
	{
		vert.camera_x = 2 * vert.x / (double)R_WIDTH - 1;
		vert.dir = v2add(game->player.dir, \
		v2muls(game->player.plane, vert.camera_x));
		vert.ray = raycast(map, game->player.pos, vert.dir);
		if (vert.x == R_HEIGHT / 2)
			game->half = vert.ray;
		render_vertical(game, vert);
	}
}