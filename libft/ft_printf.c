/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:29:18 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 18:43:08 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_printf_init_flags(t_env *e)
{
	e->flag_plus = 0;
	e->flag_diese = 0;
	e->flag_moins = 0;
	e->flag_space = 0;
	e->flag_zero = 0;
	e->field_width = 0;
	e->precision = -1;
	e->field_width = 0;
	e->neg = 0;
	e->m_h = 0;
	e->m_hh = 0;
	e->m_l = 0;
	e->m_ll = 0;
	e->m_j = 0;
	e->m_z = 0;
	e->type = 0;
}

static void		ft_printf_init(t_env *e)
{
	e->i = 0;
	e->size = 0;
	e->index = 0;
	e->nb_arg = 0;
	e->family = 0;
	e->file = NULL;
	e->str = NULL;
	e->fd = 0;
	ft_printf_init_flags(e);
}

static void		ft_printf_add_char(t_env *e, char c)
{
	char s[2];

	if (c == '%')
		e->i++;
	s[0] = c;
	s[1] = '\0';
	ft_printf_add_to_buffer(e, s, 0);
	e->i++;
}

static void		ft_printf_parse(t_env *e, char *format)
{
	if (format[e->i] == '%' && format[e->i + 1])
		ft_printf_parser(e, format);
	else
		e->i++;
}

int				ft_printf(const char *restrict format, ...)
{
	t_env		e;

	ft_printf_init(&e);
	va_start(e.pa, format);
	while (format[e.i] != '\0')
	{
		if (e.index >= 3999)
			ft_printf_buffer_flush(&e);
		if ((format[e.i] != '%') || (format[e.i] == '%'
					&& format[e.i + 1] && format[e.i + 1] == '%'))
			ft_printf_add_char(&e, format[e.i]);
		else
			ft_printf_parse(&e, (char*)format);
		ft_printf_init_flags(&e);
	}
	ft_printf_buffer_flush(&e);
	va_end(e.pa);
	return (e.size);
}
