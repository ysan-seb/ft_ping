/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:42:28 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:42:29 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_printf_check_ml(t_env *e)
{
	char *tmp;

	tmp = NULL;
	if (e->m_ll)
		tmp = ft_stoa_base(va_arg(e->pa, long long), 10);
	else if (e->m_l)
		tmp = ft_stoa_base(va_arg(e->pa, long), 10);
	else if (e->m_j)
		tmp = ft_stoa_base(va_arg(e->pa, intmax_t), 10);
	else if (e->m_z)
		tmp = ft_stoa_base(va_arg(e->pa, ssize_t), 10);
	else if (e->m_h)
		tmp = ft_stoa_base((short)va_arg(e->pa, int), 10);
	else if (e->m_hh)
		tmp = ft_stoa_base((char)va_arg(e->pa, int), 10);
	else
		tmp = ft_stoa_base(va_arg(e->pa, int), 10);
	return (tmp);
}

void			ft_printf_di(t_env *e)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_printf_check_ml(e);
	tmp = remove_min(e, tmp);
	e->type = 'd';
	if (ft_strcmp(tmp, "0") == 0 && e->precision == 0)
		ft_printf_putflags(e, ft_strdup(""));
	else
		ft_printf_putflags(e, tmp);
}
