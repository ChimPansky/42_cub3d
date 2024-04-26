/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartesian_vector2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/17 09:41:47 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	cvector_normalize(t_cvector *cvec)
{
	double		vec_mod;

	vec_mod = cvector_get_mod(cvec);
	if (dbl_is_almost_zero(vec_mod))
		return ;
	cvec->x /= vec_mod;
	cvec->y /= vec_mod;
}
