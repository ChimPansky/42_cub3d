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

# include "structs/game_state.h"
# include "structs/minimap.h"
# include "structs/image.h"
# include "structs/app.h"

// should be something between 1.0 and 3.0
# define WALL_HEIGHT 1.0
// 60 degrees player field of view
# define FOV M_PI / 3

void	render_minimap(t_minimap *minimap, t_game_state *game_state);
void	render_scene(t_image *scene_image, t_static_graphics *sprites,
			t_game_state *game);

#endif  // RENDER_H
