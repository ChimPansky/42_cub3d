/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:20:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/08 11:50:59 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *err_msg)
{
	ft_dprintf(STDERR_FILENO, COLOR_RED);
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		ft_dprintf(STDERR_FILENO, "Unknown Error\n");
	ft_dprintf(STDERR_FILENO, COLOR_RESET);
}

void	error_exit(t_cube *cub, int exit_code)
{
	cub_destroy(cub);
	if (errno)
		exit(errno);
	else
		exit(exit_code);
}
