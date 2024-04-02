#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <texture.h>
#include <mlx.h>

#define IMGBM_WIDTH 1000
#define IMGBM_HEIGHT 1000
#define SAMPLES 100
#define BENCHMARK_MAX 100
#define BM_START 1
#define BM_END 2
#define BM_RESET 3

void	benchmark_act(char *name, int activity)
{
	static char		*marks[BENCHMARK_MAX];
	static float	times[BENCHMARK_MAX];
	float			end_time;
	static int		fold;

	if (activity == BM_START)
	{
		marks[fold] = name;
		times[fold] = ((float)clock() / CLOCKS_PER_SEC);
		fold++;
	}
	else if (activity == BM_END)
	{
		fold--;
		end_time = (float)clock() / CLOCKS_PER_SEC;
		printf("%s%f\n", marks[fold], end_time - times[fold]);
	}
}


static void run_xy_tests(int *array, int *data)
{	
	benchmark_act("xy int array:", BM_START);
	for (size_t i = 0; i < SAMPLES; i++)
	{
		for (int x = 0; x < IMGBM_WIDTH; x++)
		{
			for (int y = 0; y < IMGBM_HEIGHT; y++)
			{
				array[x + y * IMGBM_WIDTH] = x * y;
			}
		}
	}
	benchmark_act(NULL, BM_END);
	benchmark_act("xy t_texture:", BM_START);
	for (size_t i = 0; i < SAMPLES; i++)
	{
		for (int x = 0; x < IMGBM_WIDTH; x++)
		{
			for (int y = 0; y < IMGBM_HEIGHT; y++)
			{
				data[x + y * IMGBM_HEIGHT] = x * y;
			}
		}
	}
	benchmark_act(NULL, BM_END);
}

static void run_yx_tests(int *array, int *data)
{

	benchmark_act("yx int array:", BM_START);
	for (size_t i = 0; i < SAMPLES; i++)
	{
		for (int y = 0; y < IMGBM_HEIGHT; y++)
		{
			for (int x = 0; x < IMGBM_WIDTH; x++)
			{
				array[x + y * IMGBM_WIDTH] = x * y;
			}
		}
	}
	benchmark_act(NULL, BM_END);
	benchmark_act("yx t_texture:", BM_START);
	for (size_t i = 0; i < SAMPLES; i++)
	{
		for (int y = 0; y < IMGBM_HEIGHT; y++)
		{
			for (int x = 0; x < IMGBM_WIDTH; x++)
			{
				data[x + y * IMGBM_WIDTH] = x * y;
			}
		}
	}
	benchmark_act(NULL, BM_END);
}

int main()
{
	void		*mlx = mlx_init();
	t_texture	texture = texture_create(mlx, IMGBM_WIDTH, IMGBM_HEIGHT);
	volatile int *array = malloc(IMGBM_WIDTH * IMGBM_HEIGHT * sizeof(int));
	
	run_yx_tests(array, (volatile int *)texture.data);
	run_xy_tests(array, (volatile int *)texture.data);
	printf("%d\n", array[50 + 25 * IMGBM_WIDTH]);
	printf("%d\n", (volatile int*)(texture.data)[50 + 25 * IMGBM_WIDTH]);
	return 0;
}
