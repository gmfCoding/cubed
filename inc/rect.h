#ifndef RECT_H
# define RECT_H
# include <stdbool.h>
# include "vector2.h"
typedef struct s_rect t_rect; 
struct s_rect
{
    union {
        t_vec2 pos;
        t_vec2 min;
    };
    union
    {
        t_vec2 max;
        t_vec2 size;
    };
};

t_rect	rect_getbounded(t_rect rect);
bool	rect_contains_v2(t_rect rect, t_vec2 pos);
#endif