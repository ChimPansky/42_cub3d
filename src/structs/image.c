#include "image.h"

#include "mlx.h"
#include "trgb.h"
#include <stddef.h>

t_image	*image_init(void *mlx, t_image *img, int width, int height)
{
	img->image = mlx_new_image(mlx, width, height);
	if (!img->image)
		return (NULL);
	img->addr = mlx_get_data_addr(img->image, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void	image_destroy(void *mlx, t_image *img)
{
	mlx_destroy_image(mlx, img->image);
}

void	image_put_pixel(t_image *img, t_pixel pix, t_trgb color)
{
	char	*dst;

	dst = img->addr + (pix.y * img->line_length + pix.x * (img->bits_per_pixel / 8));
	*(t_trgb *)dst = color;
}
