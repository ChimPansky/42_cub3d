#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <sys/types.h>
# include "mlx.h"

typedef struct s_image {
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_image;

typedef struct s_pixel
{
	int	x;
	int	y;
}		t_pixel;

t_image			*image_init(void *mlx, t_image *img, int width, int height);
void			image_destroy(void *mlx, t_image *img);

void			image_put_pixel(t_image *img, t_pixel pix, unsigned int color);

#endif  // MLX_UTILS_H
