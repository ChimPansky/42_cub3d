#include "minimap.h"

#include "trgb.h"
#include "map.h"
#include "mlx_utils/mlx_utils.h"
#include "libft.h"
#include "cub3d.h"
#include "stdio.h"

int	minimap_init(void *mlx, t_minimap *minimap)
{
	minimap->width = MM_W;
	minimap->height = MM_H;
	minimap->offset_x = MM_X;
	minimap->offset_y = MM_Y;
	minimap->pix_per_field = MM_PIXEL_PER_FIELD;
	if (NULL
		== init_image(mlx, &minimap->image, minimap->width, minimap->height))
		return (print_error(NULL), perror("minimap_init: init_image"),
			FAILURE);
	return (SUCCESS);
}

void	minimap_destroy(void *mlx, t_minimap *minimap)
{
	destroy_image(mlx, &minimap->image);
}

t_trgb	minimap_color_by_map_sym(t_map_sym sym)
{
	if (sym == PATH_SYM)
		return (MM_PATH_COL);
	else if (sym == WALL_SYM)
		return (MM_WALL_COL);
	return (MM_UNDEFINED_COL);
}
