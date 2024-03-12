#include "../graphics/graphics.h"
#include "../cub3d.h"
#include <sys/types.h>
#include "mlx.h"
#include "render.h"

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

t_trgb	color_by_sym(t_map_sym sym)
{
	if (sym == PATH_SYM)
		return (MM_PATH_COL);
	else if (sym == WALL_SYM)
		return (MM_WALL_COL);
	return (MM_UNDEFINED_COL);
}

t_map_sym	coord_to_map_sym(t_map *map, t_pos *coord)
{
	const int x = coord->x;
	const int y = coord->y;

	if (x >= (int)map->width || y >= (int)map->height || x < 0 || y < 0)
		return (UNKNOWN_SYM);
	if (map->raw_map.buf[y][x] == WALL_SYM)
		return (WALL_SYM);
	if (map->raw_map.buf[y][x] == PATH_SYM)
		return (PATH_SYM);
	return (UNKNOWN_SYM);
}

void	render_minimap(t_image *mm_image, t_game_state *game_state)
{
	t_pixel	pix;
	t_pos	coord;

	pix.x = 0;
	pix.y = 0;
	while (pix.x < MM_W)
	{
		pix.y = 0;
		while (pix.y < MM_H)
		{
			minimap_pixel_to_coord(&pix, &coord, &game_state->player.pos);
			put_pixel(mm_image, pix.x, pix.y,
				color_by_sym(coord_to_map_sym(&game_state->map, &coord)));
			++pix.y;
		}
		++pix.x;
	}
	pix.x = MM_W / 2 - MM_PLAYER_PIX_SZ - 1;
	while (++pix.x < MM_W / 2 + MM_PLAYER_PIX_SZ)
	{
		pix.y = MM_H / 2 - MM_PLAYER_PIX_SZ - 1;
		while (++pix.y < MM_H / 2 + MM_PLAYER_PIX_SZ)
			put_pixel(mm_image, pix.x, pix.y, MM_PLAYER_COL);
	}
}
