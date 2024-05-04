/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:29:39 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/18 17:31:38 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "game_state.h"
# include "minimap.h"
# include "app.h"

void	render_minimap(t_minimap *minimap, t_game_state *game_state);
void	render_scene(t_app *app);

#endif  // RENDER_H
