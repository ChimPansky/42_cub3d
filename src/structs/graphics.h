/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:01:22 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/27 18:41:33 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "structs/image.h"
# include "structs/minimap.h"
# include "animation.h"

# define WIN_SIZE_FACTOR 0.50

typedef struct s_graph
{
	void		*win;
	t_minimap	minimap;
	t_image		scene;
	t_animation	leg;
}		t_graph;

int		graphics_init(void *mlx, t_graph *gr, t_sprites *sprites);
void	graphics_destroy(void *mlx, t_graph *gr);

#endif  // GRAPHICS_H
