/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:36:24 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:36:25 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf_precision(t_env *e, char *format)
{
	int start;

	if (format[e->i] != '.')
		return (-1);
	e->i++;
	if (format[e->i] && format[e->i] == '*')
	{
		e->precision = va_arg(e->pa, int);
		if (e->precision < 0)
			return ((e->precision = 0) - 1);
		e->i++;
		return (0);
	}
	start = e->i;
	while (format[e->i] && format[e->i] >= '0' && format[e->i] <= '9')
		e->i++;
	if (start < e->i)
	{
		e->precision = ft_atoi(format + start);
		if (e->precision < 0)
			return ((e->precision = 0) - 1);
		return (0);
	}
	e->precision = 0;
	return (0);
}
