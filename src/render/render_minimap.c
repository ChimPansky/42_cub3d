#include "render.h"
#include <sys/types.h>
#include "structs/trgb.h"
#include "vector/vector.h"
#include <math.h>

static void	minimap_pixel_to_coord(
	t_minimap *minimap, t_pixel *pix, t_pos *coord, t_pos *center)
{
	t_pixel	center_pix;
	int		dx;
	int		dy;

	center_pix.x = minimap->width / 2.;
	center_pix.y = minimap->height / 2.;
	dx = pix->x - center_pix.x;
	dy = pix->y - center_pix.y;
	coord->x = center->x + dx / minimap->pix_per_field;
	coord->y = center->y + dy / minimap->pix_per_field;
}


static void	render_player(t_minimap *minimap, t_player *player, t_image *minimap_cursor)
{
	t_pixel	pix;

	pix.x = minimap->width / 2 - MM_PLAYER_PIX_SZ - 1;
	while (++pix.x < minimap->width / 2 + MM_PLAYER_PIX_SZ)
	{
		pix.y = minimap->height / 2 - MM_PLAYER_PIX_SZ - 1;
		while (++pix.y < minimap->height / 2 + MM_PLAYER_PIX_SZ)
			image_put_pixel(&minimap->image, pix, MM_PLAYER_COL);
	}
	image_put_transformed_to_image(
		&minimap->image, minimap_cursor,
		pixel(minimap->width / 2, minimap->height / 2),
		pvector(1, player->angle + M_PI_2));
}

void	render_minimap(t_minimap *minimap, t_static_graphics *static_gr, t_game_state *game_state)
{
	t_pixel	pix;
	t_pos	coord;

	pix.x = 0;
	pix.y = 0;
	while (pix.x < minimap->width)
	{
		pix.y = 0;
		while (pix.y < minimap->height)
		{
			minimap_pixel_to_coord(
				minimap, &pix, &coord, &game_state->player.pos);
			image_put_pixel(&minimap->image, pix,
				minimap_color_by_map_sym(
					coord_to_map_sym(&game_state->map, coord)));
			++pix.y;
		}
		++pix.x;
	}
	render_player(minimap, &game_state->player, &static_gr->sprites.minimap_cursor);
}
