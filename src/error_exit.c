/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:20:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/04 20:37:44 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(t_cube *cub, char *err_msg, int exit_code)
{
	ft_dprintf(STDERR_FILENO, COLOR_RED);
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (errno)
		perror(err_msg);
	else
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	ft_dprintf(STDERR_FILENO, COLOR_RESET);
	cub_destroy(cub);
	if (errno)
		exit(errno);
	else
		exit(exit_code);
}
