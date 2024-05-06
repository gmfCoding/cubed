#include <mlx.h>
#include <stddef.h>
#include <stdio.h>
#include "input.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

void    input_print_key_press(int key, void *ctx)
{
    printf("pressed:%d (%s)\n", key, key_get_keystr(key, true));
}

void    input_print_mouse_press(int button, int x, int y, void *ctx)
{
    printf("clicked:%d\n", button);
}

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 100, 100, "Input Print");

    mlx_hook(win, ON_KEYDOWN, (1L<<0), (void *)input_print_key_press, NULL);
	mlx_hook(win, ON_MOUSEDOWN, (1L<<2), (void *)input_print_mouse_press, NULL);
	mlx_do_key_autorepeatoff(mlx);
    mlx_loop(mlx);
}