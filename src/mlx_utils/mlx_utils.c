#include "mlx_utils.h"

#include "mlx.h"
#include <stddef.h>
#include "stdio.h"
#include "libft.h"
#include "cub3d.h"

t_image	*init_image(void *mlx, t_image *img, int width, int height)
{
	img->image = mlx_new_image(mlx, width, height);
	if (!img->image)
		return (NULL);
	img->addr = mlx_get_data_addr(img->image, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

int	xpm_path_to_mlx_img(void *mlx, char *xpm_path, void **target)
{
	int		width;
	int		height;

	*target = mlx_xpm_file_to_image(mlx, xpm_path, &width, &height);
	if (!*target)
		return (print_error(NULL), perror(xpm_path), FAILURE);
	return (SUCCESS);
}

void	destroy_image(void *mlx, t_image *img)
{
	mlx_destroy_image(mlx, img->image);
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

void	mlx_destroy(void *mlx)
{
	if (!mlx)
		return ;
	mlx_destroy_display(mlx);
	free(mlx);
}
