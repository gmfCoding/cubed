# ifndef OPTIMISED_H
#  ifdef EXTRA
	# define PIXEL_SET(tex, x, y, color) \
	{ \
		char	*dst; \
		dst = tex.data + (y * tex.line_size + x * (tex.bpp / 8));\
		*(unsigned int *)dst = color;\
	}
# else
#  define PIXEL_SET pixel_set
# endif
#endif