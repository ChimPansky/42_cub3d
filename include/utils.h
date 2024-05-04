/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:59:43 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 14:59:48 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

void	skip_spaces(char **str);
bool	string_is_empty(char *str);
int		print_error(char *err_msg1, char *err_msg2);
bool	dbl_is_almost_zero(double a);

#endif  // UTILS_H
