/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:57:39 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 16:02:27 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <sys/types.h>
# include "trgb.h"
# include "vector.h"

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

typedef struct s_pix_square
{
	int	tl_x;
	int	tl_y;
	int	br_x;
	int	br_y;
}		t_pix_square;

t_pixel			pixel(int x, int y);

t_pix_square	pix_square(int top_left_x, int top_left_y,
					int bottom_right_x, int bottom_right_y);
t_image			*image_init(void *mlx, t_image *img, int width, int height);
t_image			*image_init_from_xpm(void *mlx, t_image *img, char *xpm_path);
void			image_destroy(void *mlx, t_image *img);

void			image_put_pixel(t_image *img, t_pixel pix, t_trgb color);
t_trgb			image_get_pixel_color(t_image *img, t_pixel *pix);
void			image_put_to_image(
					t_image *dest,
					t_image *src,
					t_pixel insert_pos,
					t_pix_square sq);

void			image_put_transformed_to_image(
					t_image *dest,
					t_image *src,
					t_pixel insert_pos,
					t_pvector trans);

#endif  // IMAGE_H
