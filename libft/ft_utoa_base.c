/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:41:13 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:41:15 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_unblen_base(unsigned long long n, int base)
{
	int			len;
	long double	pow;

	pow = 1;
	len = 0;
	while (n >= (pow *= base))
		len++;
	return (len + 1);
}

char			*ft_utoa_base(unsigned long long nb, int base)
{
	char	*s;
	int		len;

	len = ft_unblen_base(nb, base);
	if (!(s = ft_strnew(len)))
		return (NULL);
	if (nb == 0)
	{
		s[0] = '0';
		s[1] = 0;
		return (s);
	}
	while (nb)
	{
		s[--len] = nb % base > 9 ? nb % base - 10 + 'a' : nb % base + '0';
		nb /= base;
	}
	return (s);
}
