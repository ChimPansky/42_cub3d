#include "graphics.h"
#include "mlx.h"
#include <stddef.h>
#include <stdlib.h>


void	graphics_init(t_graph *gr)
{
	gr->mlx = mlx_init();
	gr->win = mlx_new_window(gr->mlx, 640, 480, "Hello world!");
	if (NULL == init_image(gr->mlx, &gr->minimap, MM_W, MM_H)) {
		exit(1);
	}
	if (NULL == init_image(gr->mlx, &gr->minimap, APP_W, APP_H)) {
		exit(1);
	}
}

void	graphics_destroy(t_graph *gr)
{
	mlx_destroy_window(gr->mlx, gr->win);
	mlx_destroy_display(gr->mlx);
}