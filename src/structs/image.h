#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <sys/types.h>

typedef struct s_image {
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}		t_image;

typedef struct s_pixel
{
	int	x;
	int	y;
}		t_pixel;

t_image			*image_init(void *mlx, t_image *img, int width, int height);
t_image			*image_init_from_xpm(void *mlx, t_image *img, char *xpm_path);
void			image_destroy(void *mlx, t_image *img);

void			image_put_pixel(t_image *img, t_pixel pix, unsigned int color);

#endif  // MLX_UTILS_H
