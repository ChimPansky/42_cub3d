#include "trgb.h"
#include "libft.h"

t_trgb	trgb_create(int t, int r, int g, int b)
{
	t_trgb	color;

	color = 0;
	color |= t << 24;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	return (color);
}

int	get_t_from_trgb(t_trgb color)
{
	return ((color >> 24) & 255);
}

int	get_r_from_trgb(t_trgb color)
{
	return ((color >> 16) & 255);
}

int	get_g_from_trgb(t_trgb color)
{
	return ((color >> 8) & 255);
}

int	get_b_from_trgb(t_trgb color)
{
	return (color & 255);
}
