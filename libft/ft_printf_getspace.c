/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getspace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:30:39 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:35:24 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*flagcompar(t_env *e, char *s)
{
	if (e->type == 'c' && ft_strcmp(s, "") == 0)
		e->field_width -= 1;
	if (e->type == 'c')
		e->precision = -1;
	if ((e->flag_moins == 1 || e->precision >= 0) && e->flag_zero == 1 &&
			(e->type == 'd' || e->type == 'u' || e->type == 'o'
			|| e->type == 'x' || e->type == 'X'))
		e->flag_zero = 0;
	if (e->flag_plus == 1 && e->neg == 1)
		e->flag_plus = 0;
	if (e->flag_plus == 1 && e->flag_space == 1)
		e->flag_space = 0;
	if (e->neg == 1 && e->flag_space == 1)
		e->flag_space = 0;
	if (e->flag_space == 1)
		e->field_width -= 1;
	return (s);
}

char			*getspace(t_env *e, char *space, char *s)
{
	flagcompar(e, s);
	space = malloc(sizeof(char) * 2);
	if (e->type == 'd' && e->flag_space == 1)
		space[0] = ' ';
	else
		space[0] = '\0';
	space[1] = '\0';
	return (space);
}
