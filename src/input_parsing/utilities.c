/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:28:26 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/19 09:23:53 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	skip_spaces(char **str)
{
	while (**str == ' ')
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

int	get_map_width(t_charptr_array raw_map)
{
	size_t	row;
	int		max_width;
	int		cur_width;

	row = 0;
	max_width = 0;
	cur_width = 0;
	while (row < raw_map.sz)
	{
		cur_width = ft_strlen(raw_map.buf[row++]);
		if (cur_width > max_width)
			max_width = cur_width;
	}
	return (max_width);
}
