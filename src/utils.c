/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:05:25 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:15:28 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <unistd.h>

void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

bool	string_is_empty(char *str)
{
	while (*str)
	{
		if (*str++ != ' ')
			return (false);
	}
	return (true);
}

int	print_error(char *err_msg1, char *err_msg2)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (err_msg1)
	{
		ft_dprintf(STDERR_FILENO, "Input validation: %s", err_msg1);
		if (err_msg2)
			ft_dprintf(STDERR_FILENO, "%s", err_msg2);
		ft_dprintf(STDERR_FILENO, "\n");
	}
	else
		ft_dprintf(STDERR_FILENO, "Unknown Error\n");
	return (FAILURE);
}

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
