/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:56:05 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 14:56:06 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "game_state.h"
# include "graphics.h"
# include "inputs.h"
# include "sprites.h"

typedef struct s_static_graphics
{
	t_sprites		sprites;
	t_trgb			floor_col;
	t_trgb			ceiling_col;
}		t_static_graphics;

typedef struct s_app
{
	void				*mlx;
	t_game_state		game_state;
	t_graph				gr;
	t_inputs			inputs;
	t_static_graphics	static_gr;
	bool				god_mode;
}		t_app;

int		app_init(t_app *app, char *cub_path);
void	app_destroy(t_app *app);

#endif  // APP_H
