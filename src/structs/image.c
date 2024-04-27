#include "image.h"

#include "mlx.h"
#include "trgb.h"
#include <stddef.h>

t_image	*image_init(void *mlx, t_image *img, int width, int height)
{
	img->image = mlx_new_image(mlx, width, height);
	img->width = width;
	img->height = height;
	if (!img->image)
		return (NULL);
	img->addr = mlx_get_data_addr(img->image, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

// TODO error processing, mb success !success
t_image	*image_init_from_xpm(void *mlx, t_image *img, char *xpm_path)
{
	img->image = mlx_xpm_file_to_image(mlx, xpm_path, &img->width, &img->height);
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

t_pixel			pixel(int x, int y)
{
	t_pixel	pix;

	pix.x = x;
	pix.y = y;
	return (pix);
}

void	image_put_to_image(t_image *dest, t_image *src, t_pixel insert_pos)
{
	t_trgb	col;
	t_pixel	pix;
	t_pixel	dpix;

	pix.x = 0;
	while (pix.x < src->width)
	{
		pix.y = 0;
		while (pix.y < src->height)
		{
			col = image_get_pixel_color(src, &pix);
			dpix.x = insert_pos.x + pix.x;
			dpix.y = insert_pos.y + pix.y;
			if (col && dpix.x >= 0 && dpix.y >= 0 && dpix.x < dest->width && dpix.y < dest->height)
				image_put_pixel(dest, dpix, col);
			pix.y++;
		}
		pix.x++;
	}
}

t_trgb	image_get_pixel_color(t_image *img, t_pixel *pix)
{
	char	*dst;

	dst = img->addr + (pix->y * img->line_length + pix->x * (img->bits_per_pixel / 8));
	return (*(t_trgb *)dst);
}
