/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:36:18 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:42:03 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void			ft_printf_field_width3(t_env *e, char *format, int start)
{
	e->field_width = ft_atoi(format + start);
	if (e->field_width < 0)
	{
		e->flag_moins = 1;
		e->field_width *= -1;
	}
}

static void			ft_printf_field_width2(t_env *e)
{
	e->field_width = va_arg(e->pa, int);
	if (e->field_width < 0)
	{
		e->flag_moins = 1;
		e->field_width *= -1;
	}
	e->i++;
}

static int			ft_printf_field_width(t_env *e, char *format)
{
	int start;

	start = e->i;
	if (format[e->i] == '*')
	{
		ft_printf_field_width2(e);
		return (0);
	}
	if (format[e->i] >= '1' && format[e->i] <= '9')
	{
		while (format[e->i] && format[e->i] >= '0' && format[e->i] <= '9')
		{
			e->i++;
		}
		if (start != e->i)
		{
			ft_printf_field_width3(e, format, start);
			return (0);
		}
	}
	return (-1);
}

static int			ft_printf_isflag(char c, t_env *e)
{
	if (c == '-')
		e->flag_moins = 1;
	else if (c == '+')
		e->flag_plus = 1;
	else if (c == ' ')
		e->flag_space = 1;
	else if (c == '0')
		e->flag_zero = 1;
	else if (c == '#')
		e->flag_diese = 1;
	else
		return (-1);
	e->i++;
	return (0);
}

void				ft_printf_parser(t_env *e, char *format)
{
	e->i++;
	while (format[e->i])
	{
		if (ft_printf_isflag(format[e->i], e) == 0)
			continue ;
		if (ft_printf_field_width(e, format) == 0)
			continue ;
		if (ft_printf_precision(e, format) == 0)
			continue ;
		if (ft_printf_length(e, format) == 0)
			continue ;
		if (ft_printf_conversion(e, format[e->i]) == 0)
		{
			e->i++;
			break ;
		}
		else
			break ;
		e->i++;
	}
}
