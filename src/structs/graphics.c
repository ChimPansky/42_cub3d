#include "graphics.h"
#include "mlx.h"
#include "libft.h"

// TODO add checks
int	graphics_init(void *mlx, t_graph *gr)
{
	gr->win = mlx_new_window(mlx, WIN_W, WIN_H, "Hello world!");
	minimap_init(mlx, &gr->minimap);
	if (NULL == init_image(mlx, &gr->scene, WIN_W, WIN_H))
		exit(1);
	return (SUCCESS);
}

void	graphics_destroy(void *mlx, t_graph *gr)
{
	destroy_image(mlx, gr->scene.image);
	minimap_destroy(mlx, &gr->minimap);
	mlx_destroy_window(mlx, gr->win);
	mlx_destroy_display(mlx);
}
