/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:37:36 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:37:37 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_printf_check_ml(t_env *e)
{
	char *tmp;

	if (e->m_ll)
		tmp = ft_utoa_base(va_arg(e->pa, unsigned long long), 10);
	else if (e->m_l)
		tmp = ft_utoa_base(va_arg(e->pa, unsigned long), 10);
	else if (e->m_j)
		tmp = ft_utoa_base(va_arg(e->pa, uintmax_t), 10);
	else if (e->m_z)
		tmp = ft_utoa_base(va_arg(e->pa, size_t), 10);
	else if (e->m_h)
		tmp = ft_utoa_base((unsigned short)va_arg(e->pa, unsigned int), 10);
	else if (e->m_hh)
		tmp = ft_utoa_base((unsigned char)va_arg(e->pa, unsigned int), 10);
	else
		tmp = ft_utoa_base(va_arg(e->pa, unsigned int), 10);
	return (tmp);
}

void			ft_printf_u(t_env *e)
{
	char *tmp;

	tmp = NULL;
	e->type = 'u';
	tmp = ft_printf_check_ml(e);
	if (ft_strcmp(tmp, "0") == 0)
	{
		if (e->precision == 0)
			ft_printf_putflags(e, ft_strdup(""));
		else
			ft_printf_putflags(e, tmp);
		return ;
	}
	ft_printf_putflags(e, tmp);
}
