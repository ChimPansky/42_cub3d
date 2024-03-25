/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/21 09:48:56 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "input_parsing.h"
#include <stdio.h>

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

int	add_wall(void *mlx, t_sprites *sprites, t_scene_element *element)
{
	t_image	*sprite_ptr;

	sprite_ptr = NULL;
	if (element->scene_type == NORTH)
		sprite_ptr = &sprites->wall_no;
	else if (element->scene_type == SOUTH)
		sprite_ptr = &sprites->wall_so;
	else if (element->scene_type == WEST)
		sprite_ptr = &sprites->wall_we;
	else if (element->scene_type == EAST)
		sprite_ptr = &sprites->wall_ea;
	else
		return (print_error("critical: add_tx_wall: invalid scene_type."));
	if (sprite_ptr->image != NULL)
		return (print_error("Found duplicate wall element in "
				"scene description."));
	if (xpm_path_to_t_image(mlx, sprite_ptr, element->tx_path) == NULL)
		return (FAILURE);
	return (SUCCESS);
}
