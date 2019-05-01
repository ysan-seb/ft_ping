/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dmaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:30:31 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:30:32 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf_dmaj(t_env *e)
{
	char				*tmp;
	signed long int		deci;

	tmp = NULL;
	deci = va_arg(e->pa, signed long int);
	tmp = ft_stoa_base(deci, 10);
	e->type = 'D';
	ft_printf_putflags(e, tmp);
}
