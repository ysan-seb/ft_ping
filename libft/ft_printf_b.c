/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:29:38 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:29:39 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_printf_b(t_env *e)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_stoa_base(va_arg(e->pa, int), 2);
	e->type = 'b';
	if (ft_strcmp(tmp, "0") == 0 && e->precision == 0)
		ft_printf_putflags(e, ft_strdup(""));
	else
		ft_printf_putflags(e, tmp);
}
