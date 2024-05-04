#ifndef TRGB_H
# define TRGB_H

typedef unsigned int	t_trgb;

t_trgb	trgb(int t, int r, int g, int b);

int     trgb_parse(char **str, t_trgb *trgb);

#endif  // TRGB_H
