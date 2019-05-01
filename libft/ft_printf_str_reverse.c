/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_reverse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:37:29 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:37:30 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_printf_str_reverse(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_strlen(str);
	if (!(tmp = (char *)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	tmp[j] = '\0';
	while (--j >= 0)
	{
		tmp[i] = str[j];
		i++;
	}
	return (tmp);
}
