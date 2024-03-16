#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx_utils/mlx_utils.h"
# include "structs/minimap.h"

# define WIN_W 640
# define WIN_H 480

typedef struct s_sprites
{
	void	*wall_no;
	void	*wall_so;
	void	*wall_we;
	void	*wall_ea;
	t_trgb	floor;
	t_trgb	ceiling;
}				t_sprites;

typedef struct s_graph {
	void		*win;
	t_minimap	minimap;
	t_image		scene;
	t_sprites	sprites;
}		t_graph;

int		graphics_init(void *mlx, t_graph *gr);
void	graphics_destroy(void *mlx, t_graph *gr);

#endif  // GRAPHICS_H
