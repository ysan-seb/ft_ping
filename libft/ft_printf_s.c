/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:42:53 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:42:55 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf_s(t_env *e)
{
	char *tmp;
	char *s;

	tmp = NULL;
	if (e->m_l == 1)
	{
		ft_printf_smaj(e);
		return ;
	}
	else
		s = va_arg(e->pa, char*);
	e->type = 's';
	if (s == NULL)
		tmp = ft_strdup("(null)");
	else
		tmp = ft_strdup(s);
	if (tmp != NULL && e->precision >= 0 && e->precision < (int)ft_strlen(tmp)
			&& tmp[e->precision])
		tmp[e->precision] = '\0';
	ft_printf_putflags(e, tmp);
}
