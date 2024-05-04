/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:58:36 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 14:58:37 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include <stdbool.h>

# define SAVED_INPUTS_CAP 10

typedef struct s_inputs
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	right;
	bool	left;
	int		mouse_dx;
	int		mouse_dy;
	int		last_inputs[SAVED_INPUTS_CAP];
}		t_inputs;

#endif  // INPUTS_H
