/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:30:13 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:30:16 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_printf_conversion3(t_env *e, char c)
{
	e->field_width--;
	if (e->flag_moins == 1)
	{
		ft_printf_buffer_flush(e);
		if (e->family == 0)
			ft_putchar(c);
		else if (e->family == 1)
			ft_putchar_fd(c, e->fd);
		else if (e->family == 2)
			fwrite(&c, sizeof(char), 1, e->file);
		e->size++;
		ft_printf_putflags(e, ft_strdup(""));
		e->i++;
	}
	else
		ft_printf_putflags(e, ft_strdup(""));
}

static int		ft_printf_conversion2(t_env *e, char c)
{
	if (c == 'o')
		ft_printf_o(e);
	else if (c == 'O')
		ft_printf_omaj(e);
	else if (c == 'x')
		ft_printf_x(e);
	else if (c == 'X')
		ft_printf_xmaj(e);
	else if (c == 'c')
		ft_printf_c(e);
	else if (c == 'C')
		ft_printf_cmaj(e);
	else if (c == 'd' || c == 'i')
		ft_printf_di(e);
	else if (c == 'D')
		ft_printf_dmaj(e);
	else if (c == 'b')
		ft_printf_b(e);
	else
		return (-1);
	e->type = c;
	return (1);
}

int				ft_printf_conversion(t_env *e, char c)
{
	if (e->flag_moins == 1 && e->flag_zero == 1)
		e->flag_zero = 0;
	if (ft_printf_conversion2(e, c) == 1)
		return (0);
	if (c == 'u')
		ft_printf_u(e);
	else if (c == 'U')
		ft_printf_umaj(e);
	else if (c == 's')
		ft_printf_s(e);
	else if (c == 'S')
		ft_printf_smaj(e);
	else if (c == 'p')
		ft_printf_p(e);
	else if (c == '%')
		ft_printf_modulo(e);
	else
	{
		ft_printf_conversion3(e, c);
		return (-1);
	}
	return (0);
}
