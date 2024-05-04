/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:22 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:33:23 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/X.h>
#include "logic.h"

void	set_hooks(t_app *app)
{
	mlx_hook(app->gr.win, KeyPress, KeyPressMask,
		key_press_hook, app);
	mlx_hook(app->gr.win, KeyRelease, KeyReleaseMask,
		key_release_hook, app);
	mlx_hook(app->gr.win, MotionNotify, PointerMotionMask,
		mouse_motion_hook, app);
	mlx_hook(app->gr.win, DestroyNotify, SubstructureNotifyMask,
		mlx_loop_end, app->mlx);
}

int	mouse_motion_hook(int x, int y, t_app *app)
{
	const int	center_x = app->gr.scene.width / 2;
	const int	center_y = app->gr.scene.height / 2;

	app->inputs.mouse_dx += x - center_x;
	app->inputs.mouse_dy += y - center_y;
	if (app->inputs.mouse_dx || app->inputs.mouse_dy)
		mlx_mouse_move(app->mlx, app->gr.win, center_x, center_y);
	return (0);
}
