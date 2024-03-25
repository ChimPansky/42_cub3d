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

t_image			*image_init(void *mlx, t_image *img, int width, int height);
void			image_destroy(void *mlx, t_image *img);

void			put_pixel(t_image *img, int x, int y, unsigned int color);

unsigned int	pixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);

#endif  // MLX_UTILS_H
