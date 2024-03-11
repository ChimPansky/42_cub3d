#include "../graphics/graphics.h"
#include "../cub3d.h"
#include <sys/types.h>
#include "mlx.h"
#include "render.h"

// printf("iter: %d; zoom: %.2g\n", fractol->iterations, fractol->zoom);
// complexity: width * higth * iterations * c
void	render(t_app *app)
{
	int	x;
	int	y;

    app->gr.minimap;
    put_pixel(fractol->rend_img, x, y,
				calc_color(fractol, point(x, y)))

	x = 0;
	while (x < fractol->width)
	{
		y = 0;
		while (y < fractol->height)
		{
			;
			y++;
		}
		x++;
	}
	replace_image(fractol);
	if (0 != mlx_put_image_to_window(fractol->mlx, fractol->win,
			fractol->img->image, 0, 0))
		close_failure(fractol, "mlx_put_image_to_window");
}

void	minimap_pixel_to_coord(t_pixel *pix, t_pos *coord, t_pos *center)
{
	t_pixel	center_pix;
	int		dx;
	int		dy;

	center_pix.x = MM_W / 2.;
	center_pix.y = MM_H / 2.;
	dx = pix->x - center_pix.x;
	dy = pix->y - center_pix.y;
	coord->x = center->x + dx / MM_PIXEL_PER_FIELD;
	coord->y = center->y + dy / MM_PIXEL_PER_FIELD;
}

t_map_syms coord_to_map_sym(t_pos *coord, t_map *map)
{
	return map->raw_map[(int)coord->y * map->width + (int)coord->x];
}

void	render_minimap(t_image *mm_image, t_cube *cub)
{
	t_pixel	pix;
	t_pos	coord;
	t_map_syms sym;

	pix.x = 0;
	pix.y = 0;
	while (pix.x < MM_W)
	{
		pix.y = 0;
		while (pix.y < MM_H)
		{
			minimap_pixel_to_coord(&pix, &coord, &cub->player.pos);
			sym = coord_to_map_sym(&coord, &cub->player.pos);
			put_pixel(cub->player->pos.x );
			y++;
		}
		x++;
	}
}
