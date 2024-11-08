/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/03 15:26:38 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "input_parsing.h"
#include <stdio.h>

int	extract_tx_path_from_line(char **str, char **tx_path)
{
	skip_spaces(str);
	if (**str == '\0')
		return (FAILURE);
	*tx_path = ft_substr(*str, 0, ft_strchr(*str, ' ') - *str);
	if (!*tx_path)
		return (perror("extract_tx_path_from_line: ft_strdup"), FAILURE);
	*str += ft_strlen(*tx_path);
	if (ft_file_check_extension(*tx_path, ".xpm") == false)
		return (free(*tx_path), print_error("Wall textures "
				"in scene description have to be .xpm files.", NULL));
	return (SUCCESS);
}
