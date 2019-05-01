/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_remove_min.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:36:37 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:36:40 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*remove_min(t_env *e, char *tmp)
{
	int i;
	int y;

	i = 1;
	y = 0;
	if (tmp[0] != '-')
		return (tmp);
	while (tmp[i])
	{
		tmp[y] = tmp[i];
		i++;
		y++;
		tmp[y] = '\0';
	}
	e->neg = 1;
	return (tmp);
}
