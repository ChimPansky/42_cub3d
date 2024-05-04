/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:43:31 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 20:08:11 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"

void	init_leg_animation(t_animation *leg, t_image *sprites)
{
	leg->play = false;
	leg->frames_since_start = 0;
	leg->sprites_num = 3;
	leg->sprites = sprites;
	leg->one_sprite_size = pixel(400, 400);
	leg->frames_per_sprite = 6;
}

void	animation_put_to_image(t_image *dest, t_pixel insert_pos,
	t_animation *anim)
{
	const int		idx = anim->frames_since_start++ / anim->frames_per_sprite;

	if (idx >= anim->sprites_num)
	{
		anim->frames_since_start = 0;
		anim->play = false;
		return ;
	}
	image_put_to_image(dest, anim->sprites, insert_pos, pix_square(
			anim->one_sprite_size.x * idx, 0,
			anim->one_sprite_size.x * (idx + 1), anim->one_sprite_size.y));
}
