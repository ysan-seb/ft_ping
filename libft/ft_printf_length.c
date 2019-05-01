/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:35:31 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:35:32 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_printf_length2(t_env *e, char *format)
{
	if (format[e->i] == 'h' && format[e->i + 1] && format[e->i + 1] != 'h')
	{
		e->m_h = 1;
		e->i++;
	}
	else if (format[e->i + 1] && format[e->i] == 'h' && format[e->i + 1] == 'h')
	{
		e->m_hh = 1;
		e->i += 2;
	}
	else if (format[e->i + 1] && format[e->i] == 'l' && format[e->i + 1] != 'l')
	{
		e->m_l = 1;
		e->i++;
	}
	else
		return (0);
	return (1);
}

int			ft_printf_length(t_env *e, char *format)
{
	if ((format[e->i] == 'h' || format[e->i] == 'l' || format[e->i] == 'j' ||
				format[e->i] == 'z') && !format[e->i + 1])
	{
		e->i++;
		return (-1);
	}
	if (ft_printf_length2(e, format) == 1)
		return (0);
	if (format[e->i + 1] && format[e->i] == 'l' && format[e->i + 1] == 'l')
	{
		e->m_ll = 1;
		e->i += 2;
	}
	else if (format[e->i] == 'j' && (e->i += 1))
		e->m_j = 1;
	else if (format[e->i] == 'z')
	{
		e->m_z = 1;
		e->i++;
	}
	else
		return (-1);
	return (0);
}
