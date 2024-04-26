/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:38:05 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/17 09:43:33 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "vector.h"
#include <stdio.h>

bool	dbl_is_almost_zero(double a)
{
	if (a == 0)
		return (true);
	if (a < 0 && a > -10e-10)
		return (true);
	if (a > 0 && a < 10e-10)
		return (true);
	return (false);
}

void	cvector_print(const t_cvector *cvec)
{
	printf("(%f/%f)\n", cvec->x, cvec->y);
}

void	pvector_print(const t_pvector *pvec)
{
	printf("(%f, %f)\n", pvec->r, pvec->phi);
}
