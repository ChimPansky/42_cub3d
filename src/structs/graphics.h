#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx_utils/mlx_utils.h"
# include "structs/minimap.h"

# define WIN_W 640
# define WIN_H 480

typedef struct s_graph {
	void		*win;
	t_minimap	minimap;
	t_image		scene;
}		t_graph;

int		graphics_init(void *mlx, t_graph *gr);
void	graphics_destroy(void *mlx, t_graph *gr);

#endif  // GRAPHICS_H
