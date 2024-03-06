/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:09:10 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/06 13:15:21 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include <stdbool.h>

static void	read_map(t_cube *cub, int scene_fd)
{
	(void) cub;
	(void) scene_fd;

}
static int	extract_tx_path_from_line(char **str,
		t_texture_element *tx_element)
{
	size_t	tx_path_len;

	while(**str == ' ')
		(*str)++;
	if (**str == '\0')
		return (FAILURE);
	tx_element->tx_path = ft_strdup(*str);
	if (!tx_element->tx_path)
		return (perror("extract_tx_path_from_line: ft_strdup"), FAILURE);
	if (ft_file_check_extension(tx_element->tx_path, ".xpm") == false) // TODO: add explicit message that .xpm required for texture??
		return (free(tx_element->tx_path), FAILURE);
	return (SUCCESS);
}

static int	extract_tx_type_from_line(char **str,
		t_texture_element *tx_element)
{
	while(**str == ' ')
		(*str)++;
	if (ft_strncmp(*str, "NO ", 3) == 0)
		tx_element->tx_type = NORTH;
	else if (ft_strncmp(*str, "SO ", 3) == 0)
		tx_element->tx_type = SOUTH;
	else if (ft_strncmp(*str, "WE ", 3) == 0)
		tx_element->tx_type = WEST;
	else if (ft_strncmp(*str, "EA ", 3) == 0)
		tx_element->tx_type = EAST;
	if (tx_element->tx_type == UNKNOWN)
		return (FAILURE);
	(*str) += 3;
}

static int get_next_element(int scene_fd, t_texture_element *tx_element)
{
	t_line				line;

	while (true)
	{
		line = get_next_line(scene_fd);
		if (line.error)
			return (perror("get_next_element: get_next_line"), FAILURE);
		if (line.str == NULL)
			return (FAILURE);
		if (line.len == 0)
			free(line.str);
		else
		{
			tx_element->tx_path = NULL;
			tx_element->tx_type = UNKNOWN;
			if (extract_tx_type_from_line(&line.str, tx_element) != SUCCESS)
				return (free(line.str), FAILURE);
			if (extract_tx_path_from_line(&line.str, tx_element) != SUCCESS)
				return (free(line.str), FAILURE);
			free(line.str);
			break ;
		}
	}
	return (SUCCESS);
}
static void	add_tx_floor_ceiling(t_cube *cub, t_texture_element *tx_element)
{
	t_rgba	tx_rgba;

	if (tx_element->tx_type == FLOOR)
		tx_rgba = cub->walls_floor_ceiling.floor;
	else if (tx_element->tx_type == CEILING)
		tx_rgba = cub->walls_floor_ceiling.ceiling;
	if (tx_rgba.blue != -1) // TODO: figure out how to check if tx_rgba has already been set...
	{
		error_exit(cub, "Found duplicate texture in scene description.",
			FAILURE);
	}
	tx_rgba = tx_element->tx_path;
}

static void	add_tx_wall(t_cube *cub, t_texture_element *tx_element)
{
	char	*texture_path;

	if (tx_element->tx_type == NORTH)
		texture_path = cub->walls_floor_ceiling.wall_no;
	if (tx_element->tx_type == SOUTH)
		texture_path = cub->walls_floor_ceiling.wall_so;
	if (tx_element->tx_type == WEST)
		texture_path = cub->walls_floor_ceiling.wall_we;
	if (tx_element->tx_type == EAST)
		texture_path = cub->walls_floor_ceiling.wall_ea;
	if (texture_path != NULL)
	{
		free(tx_element->tx_path);
		error_exit(cub, "Found duplicate texture in scene description.",
			FAILURE);
	}
	texture_path = tx_element->tx_path;
}

static void	read_textures(t_cube *cub, int scene_fd)
{
	t_texture_element 	tx_element;
	int					i;

	i = 0;
	while (i < TX_COUNT)
	{
		if (get_next_element(scene_fd, &tx_element) != SUCCESS)
			error_exit(cub, "Found invalid texture in scene description.",
				FAILURE);
		if (tx_element.tx_type == FLOOR || tx_element.tx_type == CEILING)
			add_tx_floor_ceiling(cub, &tx_element);
		else
			add_tx_wall(cub, &tx_element);
		i++;
	}


}

void	read_scene_description(t_cube *cub, char *fpath)
{
	int	scene_fd;

	if (ft_file_check_extension(fpath, ".cub") == false)
		error_exit(cub, "Scene description must be a .cub file.", FAILURE);
	scene_fd = open(fpath, O_RDONLY);
	if (scene_fd == -1)
		error_exit(cub, "Could not open scene description file.", FAILURE);
	read_textures(cub, scene_fd);
	read_map(cub, scene_fd);
	// if (cub->walls_floor_ceiling.wall_ea == NULL)
	// 	ft_printf("wall_ea is NULL\n");
	// else
	// 	ft_printf("wall_ea is NOT NULL\n");
	// error_exit(cub, "test_exit", 99);
	close(scene_fd);


}
