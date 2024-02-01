#include "mini_map.h"
#include "texture.h"
#include "state.h"

void	mmap_input(t_game *game, t_mmap *mmap)
{
	if (input_keydown(&game->input, KEY_M))
	{
		if(mmap->mm_small == true)
		{
			mmap->mm_big = true;
			mmap->mm_small = false;
		}
		else
		{
			mmap->mm_big = false;
			mmap->mm_small = true;
		}
	}
}
