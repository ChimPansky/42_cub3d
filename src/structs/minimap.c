#include "minimap.h"
#include "trgb.h"
#include "map.h"
#include "structs/image.h"
#include "libft.h"

int	minimap_init(void *mlx, t_minimap *minimap, t_image *cursor)
{
	minimap->width = MM_W;
	minimap->height = MM_H;
	minimap->offset_x = MM_X;
	minimap->offset_y = MM_Y;
	minimap->pix_per_field = MM_PIXEL_PER_FIELD;
	minimap->cursor = cursor;
	if (NULL
		== image_init(mlx, &minimap->image, minimap->width, minimap->height))
		return (!SUCCESS);
	return (SUCCESS);
}

void	minimap_destroy(void *mlx, t_minimap *minimap)
{
	image_destroy(mlx, &minimap->image);
}

t_trgb	minimap_color_by_map_sym(t_map_sym sym)
{
	if (sym == PATH_SYM)
		return (MM_PATH_COL);
	else if (sym == WALL_SYM)
		return (MM_WALL_COL);
	else if (sym == DOOR_SYM)
		return (MM_DOOR_COL);
	return (MM_UNDEFINED_COL);
}
