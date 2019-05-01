/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:23:05 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/05/17 14:00:53 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!s1 || !(tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	if (tmp != NULL)
	{
		while (s1[i] != '\0')
		{
			tmp[i] = s1[i];
			i++;
		}
	}
	tmp[i] = '\0';
	return (tmp);
}
