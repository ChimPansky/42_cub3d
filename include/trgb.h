/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:59:31 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 14:59:38 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRGB_H
# define TRGB_H

typedef unsigned int	t_trgb;

t_trgb	trgb(int t, int r, int g, int b);

int		trgb_parse(char **str, t_trgb *trgb);

#endif  // TRGB_H
