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

#include "vector/vector.h"
#include <math.h>

double min(double a, double b)
{
	if (a < b)
		return a;
	return b;
}

double max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

t_cvector	cvector_mul_pvector(t_cvector *cvec, t_pvector *pvec)
{
	t_cvector result;

	result.x = cvec->x * pvec->r * cos(pvec->phi) - cvec->y * pvec->r * sin(pvec->phi);
	result.y = cvec->x * pvec->r * sin(pvec->phi) + cvec->y * pvec->r * cos(pvec->phi);
	return (result);
}

bool is_pixel_on_pict(t_image *image, t_pixel *pix)
{
	if (pix->x < 0 || pix->x >= image->width)
		return (false);
	if (pix->y < 0 || pix->y >= image->height)
		return (false);
	return (true);
}

void	image_put_transformed_to_image(
		t_image *dest,
		t_image *src,
		t_pixel insert_pos,
		t_pvector trans)
{
	// lead is the vector from center to one of the corners
	t_cvector src_center = cvector(src->width / 2., src->height / 2.);
	t_cvector proj = cvector_mul_pvector(&src_center, &trans);

	// get the rect of transformed size
	int trans_radius = cvector_get_mod(&src_center) * trans.r + 1;

	// reverse transform to get pix from dest on source
	trans.phi *= -1;
	trans.r = 1 / trans.r;

	t_pixel cur;
	t_pixel dest_pix;
	t_pixel src_pix;
	t_trgb	col;

	cur.x = -trans_radius - 1;
	while (++cur.x <= trans_radius)
	{
		dest_pix.x = insert_pos.x + cur.x;
		cur.y = -trans_radius - 1;
		while (++cur.y <= trans_radius)
		{
			dest_pix.y = insert_pos.y + cur.y;
			if (!is_pixel_on_pict(dest, &dest_pix))
				continue;
			t_cvector vec = cvector(cur.x, cur.y);
			proj = cvector_mul_pvector(&vec, &trans);
			src_pix.x = src_center.x + proj.x;
			src_pix.y = src_center.y + proj.y;
			if (!is_pixel_on_pict(src, &src_pix))
				continue;
			col = image_get_pixel_color(src, &src_pix);
			if (col)
				image_put_pixel(dest, dest_pix, col);
		}
	}
}
