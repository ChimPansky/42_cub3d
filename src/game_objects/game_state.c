/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:43:46 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/05 09:00:16 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_state.h"
#include "stdio.h"

int	game_init(t_game_state *game)
{
	ft_bzero(game, sizeof(t_game_state));
	if (charptr_array_init(&game->map.raw_map) != SUCCESS)
		return (perror("cub_init: charptr_array_init"), FAILURE);
	return (SUCCESS);
}

void	game_destroy(t_game_state *game)
{
	doors_destroy(&game->map.doors);
	charptr_array_destroy(&game->map.raw_map);
}
