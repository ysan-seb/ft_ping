/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xmaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:38:10 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:38:12 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_printf_check_ml(t_env *e)
{
	char *tmp;

	if (e->m_ll)
		tmp = ft_utoa_base(va_arg(e->pa, unsigned long long), 16);
	else if (e->m_l)
		tmp = ft_utoa_base(va_arg(e->pa, unsigned long), 16);
	else if (e->m_j)
		tmp = ft_utoa_base(va_arg(e->pa, uintmax_t), 16);
	else if (e->m_z)
		tmp = ft_utoa_base(va_arg(e->pa, size_t), 16);
	else if (e->m_h)
		tmp = ft_utoa_base((unsigned short)va_arg(e->pa, unsigned int), 16);
	else if (e->m_hh)
		tmp = ft_utoa_base((unsigned char)va_arg(e->pa, unsigned int), 16);
	else
		tmp = ft_utoa_base(va_arg(e->pa, unsigned int), 16);
	return (tmp);
}

void			ft_printf_xmaj(t_env *e)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	tmp = ft_printf_check_ml(e);
	while (tmp[i])
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}
	e->type = 'X';
	if (ft_strcmp(tmp, "0") == 0)
	{
		e->flag_diese = 0;
		if (e->precision == 0)
			ft_printf_putflags(e, ft_strdup(""));
		else
			ft_printf_putflags(e, tmp);
		return ;
	}
	ft_printf_putflags(e, tmp);
}
