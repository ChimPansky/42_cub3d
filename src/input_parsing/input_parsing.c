/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:09:10 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/03 11:16:57 by tkasbari         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "input_parsing.h"
#include "utils.h"
#include <stdio.h>
#include <fcntl.h>
#include "sprites.h"

static int	extract_element_type_from_line(char **str,
		t_scene_element *element)
{
	skip_spaces(str);
	if (ft_strncmp(*str, "NO ", 3) == 0)
		element->scene_type = NORTH;
	else if (ft_strncmp(*str, "SO ", 3) == 0)
		element->scene_type = SOUTH;
	else if (ft_strncmp(*str, "WE ", 3) == 0)
		element->scene_type = WEST;
	else if (ft_strncmp(*str, "EA ", 3) == 0)
		element->scene_type = EAST;
	else if (ft_strncmp(*str, "F ", 2) == 0)
		element->scene_type = FLOOR;
	else if (ft_strncmp(*str, "C ", 2) == 0)
		element->scene_type = CEILING;
	else
		return (print_error("Found unknown texture element "
				"in scene description.", NULL), FAILURE);
	if (element->scene_type == CEILING || element->scene_type == FLOOR)
		(*str) += 2;
	else
		(*str) += 3;
	return (SUCCESS);
}

static int	extract_element_from_line(char **str, t_scene_element *element)
{
	if (extract_element_type_from_line(str, element) != SUCCESS)
		return (FAILURE);
	if (element->scene_type == FLOOR || element->scene_type == CEILING)
		return (trgb_parse(str, &element->trgb));
	return (extract_tx_path_from_line(str, &element->tx_path));
}

static int	get_next_element(int scene_fd, t_scene_element *element)
{
	t_line	line;
	char	*ptr_free;

	while (true)
	{
		line = get_next_line_no_nl(scene_fd);
		ptr_free = line.str;
		if (line.error)
			return (perror("get_next_element: get_next_line"), FAILURE);
		if (line.str == NULL)
			return (print_error("Missing texture element.", NULL));
		if (string_is_empty(line.str))
			free(ptr_free);
		else
		{
			if (extract_element_from_line(&line.str, element) != SUCCESS)
				return (free(ptr_free), FAILURE);
			if (!string_is_empty(line.str))
				return (print_error("Unexpected token near ", line.str),
					free(ptr_free), free(element->tx_path), FAILURE);
			free(ptr_free);
			break ;
		}
	}
	return (SUCCESS);
}

static int	read_walls_floor_ceiling(void *mlx, t_static_graphics *static_gr, int scene_fd)
{
	t_scene_element	element;
	int				elements_read;

	elements_read = 0;
	while (elements_read < WALLS_FLOOR_CEILING_COUNT)
	{
		ft_bzero(&element, sizeof(t_scene_element));
		if (get_next_element(scene_fd, &element) != SUCCESS)
			return (sprites_destroy(mlx, &static_gr->sprites), FAILURE);
		if (element.scene_type == FLOOR || element.scene_type == CEILING)
		{
			if (add_floor_ceiling(static_gr, &element) != SUCCESS)
				return (sprites_destroy(mlx, &static_gr->sprites), FAILURE);
		}
		else
		{
			if (add_sprite_img(mlx, &static_gr->sprites, element.scene_type,
				element.tx_path) != SUCCESS)
				return (sprites_destroy(mlx, &static_gr->sprites),
					free(element.tx_path), FAILURE);
			free(element.tx_path);
		}
		elements_read++;
	}
	return (SUCCESS);
}

int	read_scene_description(t_app *app, char *fpath)
{
	int	scene_fd;

	if (ft_file_check_extension(fpath, ".cub") == false
		|| ft_strlen(fpath) < 5 || fpath[ft_strlen(fpath) - 5] == '/')
		return (print_error("Could not open scene description file.", NULL));
	scene_fd = open(fpath, O_RDONLY);
	if (scene_fd == -1)
		return (print_error("Scene description must be a .cub file.", NULL));
	if (read_walls_floor_ceiling(app->mlx, &app->static_gr, scene_fd)
		!= SUCCESS)
			return (close(scene_fd), FAILURE);
	if (read_and_validate_map(&app->game_state, scene_fd) != SUCCESS)
		return (sprites_destroy(app->mlx, &app->static_gr.sprites),
			close(scene_fd), FAILURE);
	return (close(scene_fd), SUCCESS);
}
