/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:28:26 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/09 10:19:49 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(char **str)
{
	while(**str == ' ')
		(*str)++;
}

t_line	get_next_line_no_nl(int scene_fd)
{
	t_line	line;

	line = get_next_line(scene_fd);
	if (line.str != NULL)
		ft_str_chr_replace(line.str, '\n', '\0');
	return (line);
}
