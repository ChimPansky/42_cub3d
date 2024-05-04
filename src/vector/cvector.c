/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/04 15:22:42 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>
#include <stdio.h>

t_cvector	cvector(double x, double y)
{
	t_cvector	result;

	result.x = x;
	result.y = y;
	return (result);
}

double	cvector_get_mod(const t_cvector *cvec)
{
	return (sqrt(cvec->x * cvec->x + cvec->y * cvec->y));
}

t_cvector	cvector_transform(t_cvector *src, t_pvector *trans)
{
	t_cvector	result;

	result.x = src->x * trans->r * cos(trans->phi)
		- src->y * trans->r * sin(trans->phi);
	result.y = src->x * trans->r * sin(trans->phi)
		+ src->y * trans->r * cos(trans->phi);
	return (result);
}

void	cvector_print(const t_cvector *cvec)
{
	printf("(%f/%f)\n", cvec->x, cvec->y);
}
