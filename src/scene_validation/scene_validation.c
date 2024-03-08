/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:09:10 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/08 21:47:48 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

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
			"in scene description."), FAILURE);
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
		return (extract_trgb_from_line(str, &element->trgb));
	return (extract_tx_path_from_line(str, &element->tx_path));
}

static int get_next_element(int scene_fd, t_scene_element *element)
{
	t_line	line;
	char	*ptr_free;

	while (true)
	{
		line = get_next_line(scene_fd);
		ptr_free = line.str;
		if (line.error)
			return (perror("get_next_element: get_next_line"), FAILURE);
		if (line.str == NULL)
			return (print_error("Missing texture element "
				"in scene description."), FAILURE);
		ft_str_chr_replace(line.str, '\n', '\0');
		if (ft_string_is_empty(line.str))
			free(ptr_free);
		else
		{
			if (extract_element_from_line(&line.str, element) != SUCCESS)
				return (free(ptr_free), FAILURE);
			free(ptr_free);
			break ;
		}
	}
	return (SUCCESS);
}

static int	read_walls_floor_ceiling(t_cube *cub, int scene_fd)
{
	t_scene_element 	element;
	int					elements_read;

	elements_read = 0;
	while (elements_read < WALLS_FLOOR_CEILING_COUNT)
	{
		if (get_next_element(scene_fd, &element) != SUCCESS)
			return (FAILURE);
		if (element.scene_type == FLOOR || element.scene_type == CEILING)
		{
			if (add_floor_ceiling(cub, &element) != SUCCESS)
				return (FAILURE);
		}
		else
		{
			if (add_wall(cub, &element) != SUCCESS)
				return (FAILURE);
		}
		elements_read++;
	}
	print_textures(cub->walls_floor_ceiling);
	return (SUCCESS);
}

void	read_scene_description(t_cube *cub, char *fpath)
{
	int	scene_fd;

	if (ft_file_check_extension(fpath, ".cub") == false)
	{
		print_error("Scene description must be a .cub file.");
		error_exit(cub, FAILURE);
	}
	scene_fd = open(fpath, O_RDONLY);
	if (scene_fd == -1)
	{
		print_error("Could not open scene description file.");
		error_exit(cub, FAILURE);
	}
	if (read_walls_floor_ceiling(cub, scene_fd) != SUCCESS
		|| read_map(cub, scene_fd) != SUCCESS)
	{
		close(scene_fd);
		error_exit(cub, FAILURE);
	}
}
