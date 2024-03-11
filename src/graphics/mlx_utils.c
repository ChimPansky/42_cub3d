#include "mlx_utils.h"

#include "mlx.h"
#include <stddef.h>

t_image	*init_image(
	void *mlx, t_image *img, int width, int height)
{
	img->image = mlx_new_image(mlx, width, height);
	if (!img->image)
		return (NULL);
	img->addr = mlx_get_data_addr(img->image, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void	put_pixel(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	pixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
	return (r << 16 | g << 8 | b | a << 24);
}
