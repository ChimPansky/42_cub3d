/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:20:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/12 12:53:12 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *err_msg)
{
	ft_dprintf(STDERR_FILENO, COLOR_RED);
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		ft_dprintf(STDERR_FILENO, "Unknown Error\n");
	ft_dprintf(STDERR_FILENO, COLOR_RESET);
	return (FAILURE);
}
// dont use exit, instead return to higher level with
// error code (FAILURE)
// void	error_exit(t_app *app, int exit_code, char *err_msg)
// {
// 	if (err_msg)
// 		print_error(err_msg);
// 	app_destroy(app);
// 	if (errno)
// 		exit(errno);
// 	else
// 		exit(exit_code);
// }
