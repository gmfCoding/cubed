
#include "mini_map.h"
#include "texture.h"
#include "state.h"

/*
 * stores images later on we will change this to be stored in one
 * big img array but for now this will do
 */
void	mmap_init_img_2(t_mmap *mmap, void *mlx)
{
	mmap->mm_img[1] = texture_load(mlx, "assets/minimap/mm01.xpm");
	mmap->mm_img[2] = texture_load(mlx, "assets/minimap/mm02.xpm");
	mmap->mm_img[3] = texture_load(mlx, "assets/minimap/mm03.xpm");
	mmap->mm_img[4] = texture_load(mlx, "assets/minimap/mm04.xpm");
	mmap->mm_img[5] = texture_load(mlx, "assets/minimap/mm05.xpm");
	mmap->mm_img[6] = texture_load(mlx, "assets/minimap/mm06.xpm");
	mmap->mm_img[7] = texture_load(mlx, "assets/minimap/mm07.xpm");
	mmap->mm_img[8] = texture_load(mlx, "assets/minimap/mm08.xpm");
	mmap->mm_img[9] = texture_load(mlx, "assets/minimap/mm09.xpm");
	mmap->mm_img[10] = texture_load(mlx, "assets/minimap/mm10.xpm");
	mmap->mm_img[11] = texture_load(mlx, "assets/minimap/mm11.xpm");
	mmap->mm_img[12] = texture_load(mlx, "assets/minimap/mm12.xpm");
	mmap->mm_img[13] = texture_load(mlx, "assets/minimap/mm13.xpm");
	mmap->mm_img[14] = texture_load(mlx, "assets/minimap/mm14.xpm");
	mmap->mm_img[15] = texture_load(mlx, "assets/minimap/mm15.xpm");
	mmap->mm_img[16] = texture_load(mlx, "assets/minimap/mm16.xpm");
	mmap->mm_img[17] = texture_load(mlx, "assets/minimap/mm17.xpm");
	mmap->mm_img[18] = texture_load(mlx, "assets/minimap/mm18.xpm");
	mmap->mm_img[19] = texture_load(mlx, "assets/minimap/mm19.xpm");
	mmap->mm_img[20] = texture_load(mlx, "assets/minimap/mm20.xpm");
	mmap->mm_img[21] = texture_load(mlx, "assets/minimap/mm21.xpm");
	mmap->mm_img[22] = texture_load(mlx, "assets/minimap/mm22.xpm");
	mmap->mm_img[23] = texture_load(mlx, "assets/minimap/mm23.xpm");
	mmap->mm_img[24] = texture_load(mlx, "assets/minimap/mm24.xpm");
	mmap->mm_img[25] = texture_load(mlx, "assets/minimap/mm25.xpm");
}

void	mmap_init_img_1(t_mmap *mmap, void *mlx)
{
	mmap->img_pr = texture_load(mlx, "assets/minimap/mm_player_r.xpm");
	mmap->img_pp = texture_load(mlx, "assets/minimap/mm_player_p.xpm");
	mmap->img_case[0] = texture_load(mlx, "assets/minimap/mmcase.xpm");
	mmap->img_case[1] = texture_load(mlx, "assets/minimap/mm_back_b.xpm");
	mmap->img_case[2] = texture_load(mlx, "assets/minimap/mm_back_y.xpm");
	mmap->img_case[3] = texture_load(mlx, "assets/minimap/mm_back_r.xpm");
	mmap->mm_img[0] = texture_load(mlx, "assets/minimap/mm00.xpm");
	mmap_init_img_2(mmap, mlx);
}

int	mmap_img_number_2(bool t, bool l, bool r, bool b)
{
	if (t == false && l == false && r == false && b == true)
		return(15);
	if (t == false && l == false && r == true && b == false)
		return(16);
	if (t == true && l == false && r == false && b == false)
		return(17);
	if (t == false && l == true && r == false && b == false)
		return(18);
	if (t == false && l == false && r == false && b == false)
		return(19);
	return (2);
}

/*
 * this function is joined with the one above returns a number
 * of the correct tile type this function can be used for other
 * similar things to check if an object is surrounded by walls
 * or anything just need to pass in the booleans of 4 direction
 * or copy the mmap_decide_img function and tweak it
 */
int	mmap_img_number_1(bool t, bool l, bool r, bool b)
{
	if (t == true && l == false && r == false && b == true)
		return(0);
	if (t == false && l == true && r == true && b == false)
		return(1);
	if (t == true && l == true && r == true && b == true)
		return(2);
	if (t == true && l == false && r == true && b == true)
		return(3);
	if (t == true && l == true && r == true && b == false)
		return(4);
	if (t == true && l == true && r == false && b == true)
		return(5);
	if (t == false && l == true && r == true && b == true)
		return(6);
	if (t == false && l == false && r == true && b == true)
		return(7);
	if (t == true && l == false && r == true && b == false)
		return(8);
	if (t == true && l == true && r == false && b == false)
		return(9);
	if (t == false && l == true && r == false && b == true)
		return(10);
	return(mmap_img_number_2(t, l, r, b));
}

/*
 * used to decide an image it is set to false by default
 * meaning there is no walls or doors around that tile
 * we then go into the above fucntion which returns an index
 * for the image that will be used for that minimap tile
 */
int	mmap_decide_img(t_tile *tile, int w, int h, int pos)
{
	bool	t;
	bool	l;
	bool	r;
	bool	b;
	
	t = false;
	l = false;
	r = false;
	b = false;
	if (pos - w >= 0 && (tile[pos-w].type == WALL || tile[pos-w].type == DOOR))
		t = true;
	if (pos - 1 >= 0 && (tile[pos-1].type == WALL || tile[pos-1].type == DOOR) && pos % w != 0)
		l = true;
	if (pos + 1 < (w * h) && (tile[pos + 1].type == WALL || tile[pos + 1].type == DOOR) && (pos + 1) % w != 0)
		r = true;
	if (pos + w < (w * h) && (tile[pos + w].type == WALL || tile[pos + w].type == DOOR))
		b = true;
	return (mmap_img_number_1(t,l,r,b));
}
