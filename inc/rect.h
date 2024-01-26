#ifndef RECT_H
# define RECT_H
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
#endif