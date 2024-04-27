/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:00:12 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/27 19:40:56 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "mlx.h"
#include "libft.h"

int	graphics_init(void *mlx, t_graph *gr)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(mlx, &screen_width, &screen_height);
	gr->win = mlx_new_window(mlx,
			screen_width * WIN_SIZE_FACTOR,
			screen_height * WIN_SIZE_FACTOR, "cub3d");
	minimap_init(mlx, &gr->minimap);
	if (NULL == image_init(mlx, &gr->scene,
			screen_width * WIN_SIZE_FACTOR,
			screen_height * WIN_SIZE_FACTOR))
		exit(1);
	//mlx_do_key_autorepeaton(mlx);// TODO: delete
	mlx_do_key_autorepeatoff(mlx); // TODO: uncomment
	return (SUCCESS);
}

void	graphics_destroy(void *mlx, t_graph *gr)
{
	minimap_destroy(mlx, &gr->minimap);
	image_destroy(mlx, &gr->scene);
	mlx_do_key_autorepeaton(mlx);
}
