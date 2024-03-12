/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/12 13:28:46 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "scene_description.h"

int	extract_tx_path_from_line(char **str, char **tx_path)
{
	skip_spaces(str);
	if (**str == '\0')
		return (FAILURE);
	ft_str_chr_replace(*str, ' ', '\0');
	*tx_path = ft_strdup(*str);
	if (!*tx_path)
		return (perror("extract_tx_path_from_line: ft_strdup"), FAILURE);
	if (ft_file_check_extension(*tx_path, ".xpm") == false)
		return (free(*tx_path), print_error("Wall textures "
			"in scene description have to be .xpm files."));
	return (SUCCESS);
}

int	add_wall(t_sprite_sources *sprites, t_scene_element *element)
{
	char	**texture_path;

	if (element->scene_type == NORTH)
		texture_path = &sprites->wall_no;
	else if (element->scene_type == SOUTH)
		texture_path = &sprites->wall_so;
	else if (element->scene_type == WEST)
		texture_path = &sprites->wall_we;
	else if (element->scene_type == EAST)
		texture_path = &sprites->wall_ea;
	else
		return (free(element->tx_path), print_error("critical: "
			"add_tx_wall: invalid scene_type."));
	if (*texture_path != NULL)
		return (free(element->tx_path), print_error("Found duplicate "
			"wall element in scene description."));
	*texture_path = element->tx_path;
	return (SUCCESS);
}
