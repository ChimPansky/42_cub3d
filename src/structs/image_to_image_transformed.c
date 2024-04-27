#include "image.h"
#include "trgb.h"
#include "vector/vector.h"
#include <math.h>

bool is_pixel_on_pict(t_image *image, t_pixel *pix)
{
	if (pix->x < 0 || pix->x >= image->width)
		return (false);
	if (pix->y < 0 || pix->y >= image->height)
		return (false);
	return (true);
}

static t_trgb	map_pixel(t_image *src, t_cvector pix_vec, t_cvector src_center, t_pvector trans)
{
	t_cvector proj;
	t_pixel src_pix;

	proj = cvector_mul_pvector(&pix_vec, &trans);
	src_pix.x = src_center.x + proj.x - (proj.x < 0);
	src_pix.y = src_center.y + proj.y - (proj.y < 0);
	if (!is_pixel_on_pict(src, &src_pix))
		return 0;
	return image_get_pixel_color(src, &src_pix);

}

void	image_put_transformed_to_image(
		t_image *dest,
		t_image *src,
		t_pixel insert_pos,
		t_pvector trans)
{
	const t_cvector	src_center = cvector(src->width / 2., src->height / 2.);
	const int		trans_radius = cvector_get_mod(&src_center) * trans.r + 1;
	t_pixel			cur;
	t_pixel			dest_pix;
	t_trgb			col;

	trans = pvector(1 / trans.r, -trans.phi);
	cur.x = -trans_radius - 1;
	while (++cur.x <= trans_radius)
	{
		cur.y = -trans_radius - 1;
		while (++cur.y <= trans_radius)
		{
			dest_pix = pixel(insert_pos.x + cur.x, insert_pos.y + cur.y);
			if (!is_pixel_on_pict(dest, &dest_pix))
				continue;
			col = map_pixel(src, cvector(cur.x, cur.y), src_center, trans);
			if (col)
				image_put_pixel(dest, dest_pix, col);
		}
	}
}
