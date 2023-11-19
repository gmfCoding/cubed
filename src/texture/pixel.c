#include "texture.h"
#include "cerror.h"

__attribute__((always_inline))
inline void	pixel_set(t_texture data, int x, int y, int color)
{
	char	*dst;

	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	*(unsigned int *)dst = color;
}

__attribute__((always_inline))
inline void	pixel_set_s(t_texture data, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x > data.width || y > data.height)
		return ;
	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	*(unsigned int *)dst = color;
}

int	pixel_get(t_texture data, int x, int y)
{
	char	*dst;

	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	return (*(int *)dst);
}

int	pixel_get_s(t_texture data, int x, int y)
{
	char	*dst;
	if (x < 0 || y < 0 || x > data.width || y > data.height)
		ft_assert(1, ERR_BADPARAM, __FILE__, __LINE__);
	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	return (*(int *)dst);
}
