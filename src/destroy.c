/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:15:51 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/08 21:33:33 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void textures_destroy(t_textures textures)
{
	print_textures(textures);
	free(textures.wall_no);
	free(textures.wall_so);
	free(textures.wall_we);
	free(textures.wall_ea);
	ft_printf("destroyed textures!\n");
}

void cub_destroy(t_cube *cub)
{
	textures_destroy(cub->walls_floor_ceiling);
	charptr_array_destroy(&cub->map.raw_map);
}
