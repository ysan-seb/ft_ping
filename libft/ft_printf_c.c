/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:29:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:29:55 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf_c(t_env *e)
{
	char	*tmp;
	int		c;

	tmp = ft_strnew(2);
	e->type = 'c';
	if (e->m_l == 1)
	{
		ft_printf_cmaj(e);
		return ;
	}
	else
		c = va_arg(e->pa, int);
	if (c == 0)
	{
		e->size++;
		ft_printf_putflags(e, ft_strdup(""));
		ft_printf_buffer_flush(e);
		if (e->family == 0)
			ft_putchar(0);
		return ;
	}
	tmp[0] = c;
	tmp[1] = '\0';
	ft_printf_putflags(e, tmp);
}
