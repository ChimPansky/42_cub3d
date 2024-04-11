#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "structs/image.h"
# include "structs/minimap.h"

# define WIN_W 1920
# define WIN_H 1200

typedef struct s_graph {
	void		*win;
	t_minimap	minimap;
	t_image		scene;
}		t_graph;

int		graphics_init(void *mlx, t_graph *gr);
void	graphics_destroy(void *mlx, t_graph *gr);

#endif  // GRAPHICS_H
