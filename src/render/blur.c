/**
 * SIT102 - Introduction to Programming
 *
 * Exercise:       cubed [WSL: Ubuntu-22.04]
 * Student Name:   Your name (File->Preferences->Settings SIT102)
 * Student ID:     Your student ID (File->Preferences->Settings SIT102)
 */

#include "render.h"
#include <string.h>x1

void texture_blur(t_texture t)
{
	//int *const colour = malloc(t.width * t.height * sizeof(int));
	int	colour[t.width * t.height * sizeof(int)];
	int x;
	int y;
	int sum[4];
	int col[9];

	y = -1;
	while (++y < t.height)
	{
		x = -1;
		while (++x < t.width)
		{
			if (x < 1 || y < 1 || x + 1 == t.width || y + 1 == t.height)
				continue;
			col[0] = pixel_get(t, x, y);			// C
			col[1] = pixel_get(t, x + 1, y);		// R
			col[2] = pixel_get(t, x - 1, y);		// L
			col[3] = pixel_get(t, x, y - 1);		// B
			col[4] = pixel_get(t, x, y + 1);		// T

			col[5] = pixel_get(t, x + 1, y + 1); // RT
			col[6] = pixel_get(t, x + 1, y - 1); // RB
			col[7] = pixel_get(t, x - 1, y + 1); // LT
			col[8] = pixel_get(t, x - 1, y - 1); // TB

			sum[0] = (col[0]  >> OF_BLUE) & 0xFF;
			sum[0] += (col[1] >> OF_BLUE) & 0xFF;
			sum[0] += (col[2] >> OF_BLUE) & 0xFF;
			sum[0] += (col[3] >> OF_BLUE) & 0xFF;
			sum[0] += (col[4] >> OF_BLUE) & 0xFF;
			sum[0] += (col[5] >> OF_BLUE) & 0xFF;
			sum[0] += (col[6] >> OF_BLUE) & 0xFF;
			sum[0] += (col[7] >> OF_BLUE) & 0xFF;
			sum[0] += (col[8] >> OF_BLUE) & 0xFF;
			
			sum[1] = (col[0]  >> OF_GREEN) & 0xFF;
			sum[1] += (col[1] >> OF_GREEN) & 0xFF;
			sum[1] += (col[2] >> OF_GREEN) & 0xFF;
			sum[1] += (col[3] >> OF_GREEN) & 0xFF;
			sum[1] += (col[4] >> OF_GREEN) & 0xFF;
			sum[1] += (col[5] >> OF_GREEN) & 0xFF;
			sum[1] += (col[6] >> OF_GREEN) & 0xFF;
			sum[1] += (col[7] >> OF_GREEN) & 0xFF;
			sum[1] += (col[8] >> OF_GREEN) & 0xFF;

			sum[2] = (col[0]  >> OF_RED) & 0xFF;
			sum[2] += (col[1] >> OF_RED) & 0xFF;
			sum[2] += (col[2] >> OF_RED) & 0xFF;
			sum[2] += (col[3] >> OF_RED) & 0xFF;
			sum[2] += (col[4] >> OF_RED) & 0xFF;
			sum[2] += (col[5] >> OF_RED) & 0xFF;
			sum[2] += (col[6] >> OF_RED) & 0xFF;
			sum[2] += (col[7] >> OF_RED) & 0xFF;
			sum[2] += (col[8] >> OF_RED) & 0xFF;
			
			sum[0] *= 1.0 / 9;
			sum[1] *= 1.0 / 9;
			sum[2] *= 1.0 / 9;
			colour[x + y * t.width] = R_ALPHA;
			colour[x + y * t.width] |= sum[0] << OF_BLUE;
			colour[x + y * t.width] |= sum[1] << OF_GREEN;
			colour[x + y * t.width] |= sum[2] << OF_RED;
		}
	}
	ft_memcpy(t.data, colour, t.width * t.height * sizeof(int));
	//free(colour);
}