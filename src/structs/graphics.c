#include "graphics.h"
#include "mlx.h"
#include "libft.h"
#include "utils/utils.h"
#include "stdio.h"

// TODO add checks
int	graphics_init(void *mlx, t_graph *gr)
{
	gr->win = mlx_new_window(mlx, WIN_W, WIN_H, "Hello world!");
	if (!gr->win)
		return (print_error(NULL), perror("graphics_init: mlx_new_window"),
			FAILURE);
	if (minimap_init(mlx, &gr->minimap) != SUCCESS)
		return (mlx_destroy_window(mlx, gr->win), FAILURE);
	if (NULL == init_image(mlx, &gr->scene, WIN_W, WIN_H))
		return (mlx_destroy_window(mlx, gr->win),
			minimap_destroy(mlx, &gr->minimap),
			print_error(NULL), perror("graphics_init: init_image"),
			FAILURE);
	mlx_put_image_to_window(mlx,
				 gr->win, gr->sprites.wall_no.image,
				 0, 0);
	mlx_put_image_to_window(mlx,
				 gr->win, gr->sprites.wall_so.image,
				 100, 100);
	mlx_put_image_to_window(mlx,
				 gr->win, gr->sprites.wall_we.image,
				 300, 300);
	mlx_put_image_to_window(mlx,
				 gr->win, gr->sprites.wall_ea.image,
				 400, 400);
	return (SUCCESS);
}

static void	destroy_sprites(void *mlx, t_sprites *sprites)
{
	if (sprites->wall_no.image)
		mlx_destroy_image(mlx, sprites->wall_no.image);
	if (sprites->wall_so.image)
		mlx_destroy_image(mlx, sprites->wall_so.image);
	if (sprites->wall_we.image)
		mlx_destroy_image(mlx, sprites->wall_we.image);
	if (sprites->wall_ea.image)
		mlx_destroy_image(mlx, sprites->wall_ea.image);
}


void	graphics_destroy(void *mlx, t_graph *gr)
{
	destroy_image(mlx, gr->scene.image);
	destroy_sprites(mlx, &gr->sprites);
	minimap_destroy(mlx, &gr->minimap);
	mlx_destroy_window(mlx, gr->win);
}
