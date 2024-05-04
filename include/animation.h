/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:55:56 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:52:01 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "image.h"

typedef struct s_animation
{
	t_image	*sprites;
	t_pixel	one_sprite_size;
	int		sprites_num;
	int		frames_per_sprite;
	int		frames_since_start;
	bool	play;
}		t_animation;

void	init_leg_animation(t_animation *leg, t_image *sprites);
void	animation_put_to_image(t_image *dest, t_pixel insert_pos,
			t_animation *anim);

#endif  // ANIMATION_H
