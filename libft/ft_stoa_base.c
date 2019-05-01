/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:38:54 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:38:56 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_nblen_base(long long n, int base)
{
	int			len;
	long double	pow;

	pow = 1;
	len = 0;
	if (n < 0)
		len++;
	n < 0 ? n = -n : 0;
	while (n >= (pow *= base))
		len++;
	return (len + 1);
}

char			*ft_stoa_base(long long nb, int base)
{
	char	*s;
	int		len;

	s = NULL;
	if (nb == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	len = ft_nblen_base(nb, base);
	if (!(s = ft_strnew(len)))
		return (NULL);
	if (nb < 0)
		s[0] = '-';
	nb < 0 ? nb = -nb : 0;
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
