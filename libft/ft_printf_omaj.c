/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_omaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:36:04 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:36:05 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf_omaj(t_env *e)
{
	char				*tmp;
	unsigned long int	octal;

	tmp = NULL;
	e->type = 'O';
	octal = va_arg(e->pa, unsigned long int);
	tmp = ft_utoa_base(octal, 8);
	e->type = 'O';
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
