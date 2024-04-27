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
