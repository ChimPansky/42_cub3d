#include "graphics.h"
#include <stddef.h>
#include <stdlib.h>

void	graphics_init(t_graph *graph, t_sprite_sources sprites)
{
	graph->mlx = mlx_init();
	graph->win = mlx_new_window(graph->mlx, 640, 480, "Hello world!");
	if (NULL == init_image(graph->mlx, &graph->minimap, MM_W, MM_H))
		exit(1);
	if (NULL == init_image(graph->mlx, &graph->scene, APP_W, APP_H))
		exit(1);
}

void	graphics_destroy(t_graph *gr)
{
	mlx_destroy_window(graph->mlx, graph->win);
	mlx_destroy_display(graph->mlx);
}
