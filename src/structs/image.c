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
			col = image_get_pixel_color(src, pix);
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

// wtf i spent 3 h on this func
// void	put_transformed_img_to_img(t_image *dest, t_image *src, t_pixel insert_pos, t_pvector trans)
// {
// 	t_pixel	min;
// 	t_pixel	max;

// 	t_cvector lead = cvector(src->width/2, src->height/2);
// 	t_cvector proj = cvec_mul_pvec(lead * trans);
// 	min.x = min(proj.x, -proj.x);
// 	max.x = max(proj.x, -proj.x);
// 	min.y = min(proj.y, -proj.y);
// 	max.y = max(proj.y, -proj.y);

// 	trans.angle *= -1;
// 	trans.mod = 1 / trans.mod;
// 	t_pixel cur;
// 	t_pixel dest_pix;
// 	cur.x = min.x - 1;
// 	while (++cur.x <= max.x)
// 	{
// 		dest_pix.x = insert_pos.x + cur.x;
// 		if (dest_pix.x < 0 || dest_pix.x >= dest->width)
// 			continue;
// 		cur.y = min.y - 1;
// 		while (++cur.y <= max.y)
// 		{
// 			if (dest_pix.y < 0 || dest_pix.y >= dest->height)
// 				continue;


// 		}
// 	}

	//find coords of 4 corners: (+-w/2, +-h/2) * trans: min max x, y
	// rev_tarnsform = (trans.r^-1, -angle)
	// for (x = min_x, x < max_x, y = min_y, y < max_y)
 //  dest_vec = (x,y) - insert_pos;
 //  src_vec = vec * rev_transform
 //  img_pix = (w/2, h/2) + src_vec
 //  get_color(src, img_pix)
 //  put_pix(dest, (x, y)))
// }
