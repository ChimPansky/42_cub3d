/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:44:57 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:56:55 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

t_pixel	pixel(int x, int y)
{
	t_pixel	pix;

	pix.x = x;
	pix.y = y;
	return (pix);
}

t_pix_square	pix_square(int top_left_x, int top_left_y,
		int bottom_right_x, int bottom_right_y)
{
	t_pix_square	sq;

	sq.tl_x = top_left_x;
	sq.tl_y = top_left_y;
	sq.br_x = bottom_right_x;
	sq.br_y = bottom_right_y;
	return (sq);
}
