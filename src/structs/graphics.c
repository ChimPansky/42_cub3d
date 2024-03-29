#include "graphics.h"
#include "mlx.h"
#include "libft.h"
#include "cub3d.h"
#include "stdio.h"

// TODO add checks
int	graphics_init(void *mlx, t_graph *gr)
{
	gr->win = mlx_new_window(mlx, WIN_W, WIN_H, "cub3d");
	minimap_init(mlx, &gr->minimap);
	if (NULL == image_init(mlx, &gr->scene, WIN_W, WIN_H))
		exit(1);
	mlx_do_key_autorepeatoff(mlx);
	return (SUCCESS);
}

static void	destroy_sprites(void *mlx, t_sprites *sprites)
{
	if (sprites->wall_no)
		mlx_destroy_image(mlx, sprites->wall_no);
	if (sprites->wall_so)
		mlx_destroy_image(mlx, sprites->wall_so);
	if (sprites->wall_we)
		mlx_destroy_image(mlx, sprites->wall_we);
	if (sprites->wall_ea)
		mlx_destroy_image(mlx, sprites->wall_ea);
}


void	graphics_destroy(void *mlx, t_graph *gr)
{
	minimap_destroy(mlx, &gr->minimap);
	image_destroy(mlx, &gr->scene);
	mlx_destroy_window(mlx, gr->win);
	mlx_do_key_autorepeaton(mlx);
	mlx_destroy_display(mlx);
}
