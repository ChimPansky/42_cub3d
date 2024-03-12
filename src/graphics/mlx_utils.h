#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <sys/types.h>

typedef struct s_image {
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_image;

t_image			*init_image(void *mlx, t_image *img, int width, int height);

void			put_pixel(t_image *img, int x, int y, unsigned int color);

unsigned int	pixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);

#endif  // MLX_UTILS_H
