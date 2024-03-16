#include "libft/libft.h"
#include "src/cub3d.h"
#include <stdbool.h>

int	main(int ac, char **av)
{
	if (ac < 2)
		(void)av;
	char	*src = ft_strdup("");
	char	*new;
	new = ft_strlpad(src, 'X', 10, true);
	printf("%s\n", new);
	free(new);
	ft_printf("test: %-010d", 25);
	return (0);
}
