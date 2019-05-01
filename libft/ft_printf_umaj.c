/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_umaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:37:43 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:37:44 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_printf_umaj(t_env *e)
{
	char				*tmp;
	unsigned long int	deci;

	deci = va_arg(e->pa, unsigned long int);
	tmp = ft_utoa_base(deci, 10);
	ft_printf_add_to_buffer(e, tmp, 0);
	ft_strdel(&tmp);
}
