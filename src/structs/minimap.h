#ifndef MINIMAP_H
# define MINIMAP_H

# include "mlx_utils/mlx_utils.h"
# include "trgb.h"
# include "map.h"

// minimap offset and size
# define MM_X 20
# define MM_Y 20
# define MM_W 100
# define MM_H 75
# define MM_PIXEL_PER_FIELD 10.

// square MM_PLAYER_PIX_SZ * 2 + 1
# define MM_PLAYER_PIX_SZ 1

# define MM_WALL_COL 0xFFFFFFFF
# define MM_PATH_COL 0x00000000
# define MM_UNDEFINED_COL 0x0000FF00
# define MM_PLAYER_COL 0x00FF0000

typedef struct s_minimap
{
	t_image	image;
	int		width;
	int		height;
	int		offset_x;
	int		offset_y;
	double	pix_per_field;
}		t_minimap;

int		minimap_init(void *mlx, t_minimap *minimap);
void	minimap_destroy(void *mlx, t_minimap *minimap);
t_trgb	minimap_color_by_map_sym(t_map_sym sym);

#endif  // MINIMAP_H