/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:41 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:33:44 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_H
# define LOGIC_H

# include "game_state.h"
# include "inputs.h"
# include "app.h"

void	set_hooks(t_app *app);
int		key_release_hook(int key_code, t_app *app);
int		key_press_hook(int key_code, t_app *app);
int		mouse_motion_hook(int dx, int dy, t_app *app);
void	process_inputs(t_game_state *game_state, t_inputs *inputs);
void	change_state_for_next_frame(t_game_state *game_state);
void	player_trigger_action(t_app *app);

#endif  // LOGIC_H
