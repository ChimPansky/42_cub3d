#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <sys/types.h>
# include "structs/trgb.h"
#include "vector/vector.h"

typedef struct s_image
{
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

t_pixel			pixel(int x, int y);

t_image			*image_init(void *mlx, t_image *img, int width, int height);
t_image			*image_init_from_xpm(void *mlx, t_image *img, char *xpm_path);
void			image_destroy(void *mlx, t_image *img);

void			image_put_pixel(t_image *img, t_pixel pix, t_trgb color);
t_trgb			image_get_pixel_color(t_image *img, t_pixel *pix);
void			image_put_to_image(t_image *dest, t_image *src, t_pixel insert_pos);

void	image_put_transformed_to_image(
		t_image *dest,
		t_image *src,
		t_pixel insert_pos,
		t_pvector trans);

#endif  // MLX_UTILS_H
