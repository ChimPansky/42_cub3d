#include "cub3d.h"

int	game_init(t_game_state *game)
{
	if (charptr_array_init(&game->map.raw_map) != SUCCESS)
		return (perror("cub_init: charptr_array_init"), FAILURE);
	return SUCCESS;
}

void	game_destroy(t_game_state *game)
{
	charptr_array_destroy(&game->map.raw_map);
}
