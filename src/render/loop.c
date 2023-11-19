#include <stdlib.h>
#include "cubed.h"
#include <stdbool.h>

bool inside(int x, int y, int maxX, int maxY)
{
	return (x >= 0 && y >= 0 && x < maxX && y < maxY);
}

void render(t_game *ctx)
{
	static t_vec2 position;
	static t_vec2 velocity;
	static bool set = false;
	if (!set)
	{
		velocity = v2new(0.04f, 0.05f);
		position = v2new(SCR_WIDTH / 2, SCR_HEIGHT / 2);
		set = true;
	}
	//pixel_set(ctx->rt0, position.x, position.y, 0x000000);
	position = v2add(position, velocity);
	if (position.x >= SCR_WIDTH || position.x < 0)
	{
		velocity.x = -velocity.x;
		velocity.y += (((rand() % 100) - 50) / 100.0f);
		velocity.x += (((rand() % 100) - 50) / 100.0f);
	}
	if (position.y >= SCR_HEIGHT || position.y < 0)
	{
		velocity.y = -velocity.y;
		velocity.x += (((rand() % 100) - 50) / 100.0f);
		velocity.y += (((rand() % 100) - 50) / 100.0f);
	}
	if (inside(position.x, position.y, SCR_WIDTH, SCR_HEIGHT))
		pixel_set(ctx->rt0, position.x, position.y, 0xff0000);
	texture_draw(ctx, ctx->rt0, v2new(0,0));
}