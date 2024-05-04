/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:58:44 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 14:58:45 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "image.h"
# include "trgb.h"
# include "map.h"

typedef struct s_minimap
{
	t_image	image;
	int		width;
	int		height;
	int		offset_x;
	int		offset_y;
	double	pix_per_field;
	t_image	*cursor;
}		t_minimap;

int		minimap_init(void *mlx, t_minimap *minimap, t_image *cursor);
void	minimap_destroy(void *mlx, t_minimap *minimap);
t_trgb	minimap_color_by_map_sym(t_map_sym sym);

#endif  // MINIMAP_H
