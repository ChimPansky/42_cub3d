/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:00:12 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/04 15:44:45 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "graphics.h"
#include "cub3d.h"
#include "libft.h"

// mlx_mouse_hide causes leaks! 31567 bytes in 400 blocks
int	graphics_init(void *mlx, t_graph *gr, t_sprites *sprites)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(mlx, &screen_width, &screen_height);
	gr->win = mlx_new_window(mlx,
			screen_width * WIN_SIZE_FACTOR,
			screen_height * WIN_SIZE_FACTOR, "cub3d");
	if (!gr->win)
		return (FAILURE);
	init_leg_animation(&gr->leg, &sprites->leg);
	if (minimap_init(mlx, &gr->minimap, &sprites->minimap_cursor) != SUCCESS)
		return (mlx_destroy_window(mlx, gr->win), FAILURE);
	if (image_init(mlx, &gr->scene,
			screen_width * WIN_SIZE_FACTOR,
			screen_height * WIN_SIZE_FACTOR) == NULL)
		return (mlx_destroy_window(mlx, gr->win),
			minimap_destroy(mlx, &gr->minimap), FAILURE);
	mlx_mouse_move(mlx, gr->win, gr->scene.width / 2, gr->scene.height / 2);
	mlx_mouse_hide(mlx, gr->win);
	return (SUCCESS);
}

void	graphics_destroy(void *mlx, t_graph *gr)
{
	minimap_destroy(mlx, &gr->minimap);
	image_destroy(mlx, &gr->scene);
	mlx_do_key_autorepeaton(mlx);
	mlx_mouse_show(mlx, gr->win);
	mlx_destroy_window(mlx, gr->win);
}
