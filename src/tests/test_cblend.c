#include <inttypes.h>
#include <stdio.h>
#include <texture.h>

void main(void)
{
    printf("%x\n", colour_blend(0x7FFF0000, 0xFF00FF00));
}