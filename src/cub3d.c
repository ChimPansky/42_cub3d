/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:02:15 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:24:27 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <mlx.h>
#include "app.h"
#include "render/render.h"
#include "logic/logic.h"
#include "utils.h"
#include <time.h>
#include "cub3d.h"

#include <stdio.h>

static void	print_game_info(t_app *app)
{
	char	player[100];
	char	phi[100];

	mlx_string_put(app->mlx, app->gr.win, app->gr.scene.width - 150, 10, 0,
		"DEBUG INFO:");
	sprintf(player, "Player: %.2f, %.2f", app->game_state.player.pos.x,
		app->game_state.player.pos.y);
	sprintf(phi, "Player Phi: %.2f",
		fmod(app->game_state.player.angle + 2 * M_PI, 2 * M_PI));
	mlx_string_put(app->mlx, app->gr.win, app->gr.scene.width - 150, 20, 0,
		player);
	mlx_string_put(app->mlx, app->gr.win, app->gr.scene.width - 150, 30, 0,
		phi);
}

int	main_loop(void *data)
{
	t_app	*app;

	app = (t_app *)data;
	process_inputs(&app->game_state, &app->inputs);
	change_state_for_next_frame(&app->game_state);
	render_scene(app);
	mlx_put_image_to_window(app->mlx, app->gr.win,
		app->gr.scene.image, 0, 0);
	render_minimap(&app->gr.minimap, &app->game_state);
	mlx_put_image_to_window(app->mlx, app->gr.win,
		app->gr.minimap.image.image, MM_X, MM_Y);
	print_game_info(app);
	return (0);
}

int	main(int ac, char *av[])
{
	t_app	app;

	if (ac < 2)
		return (print_error("Please provide a scene description "
				"as parameter (.cub file).", NULL), FAILURE);
	if (ac > 2)
		return (print_error("Too many arguments!", NULL), FAILURE);
	if (app_init(&app, av[1]) != SUCCESS)
		return (FAILURE);
	set_hooks(&app);
	mlx_loop_hook(app.mlx, main_loop, &app);
	mlx_loop(app.mlx);
	app_destroy(&app);
	return (SUCCESS);
}
