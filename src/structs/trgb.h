#ifndef TRGB_H
# define TRGB_H

# include <stdbool.h>

typedef unsigned int	t_trgb;

t_trgb	trgb_create(int t, int r, int g, int b);
int		get_t_from_trgb(t_trgb color);
int		get_r_from_trgb(t_trgb color);
int		get_g_from_trgb(t_trgb color);
int		get_b_from_trgb(t_trgb color);
void	print_trgb(t_trgb color); // TODO: remove

// string to color

#endif  // TRGB_H
