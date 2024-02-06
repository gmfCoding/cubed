#include <stddef.h>
#include "ui.h"
#include "input.h"

void	ui_process_draw(t_ui_context *ctx, t_inputctx *in, t_texture target)
{
	t_button	*curr;
	t_rect		aabb;
	int			i;
	int			col;
	bool		invoke;

	i = -1;
	while (++i < (int)(sizeof(ctx->buttons) / sizeof(t_button)))
	{
		if (!curr->visible)
			continue ;
		curr = &ctx->buttons[i];
		col = curr->colour;
		aabb = curr->rect;
		if (curr->enabled && rect_contains_v2(aabb, v2itov2(in->mouse)))
		{
			col = R_GREEN | R_ALPHA;
			invoke = input_keydown(in, MB_LEFT);
			invoke |= curr->repeat && input_keyheld(in, MB_LEFT);
			if (invoke && curr->callback != NULL)
				curr->callback(curr, ctx);
		}
		texture_draw_line(target, aabb.min, aabb.max, col);
		texture_draw_line(target, aabb.min, v2new(aabb.min.x, aabb.max.y), col);
		texture_draw_line(target, aabb.min, v2new(aabb.max.x, aabb.min.y), col);
		texture_draw_line(target, aabb.max, v2new(aabb.max.x, aabb.min.y), col);
		texture_draw_line(target, aabb.max, v2new(aabb.min.x, aabb.max.y), col);
	}
}
