/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_smaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:36:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:36:54 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_printf_parse_smaj(t_env *e, wchar_t *s, char *s1, char *s2)
{
	char	*tmp;
	int		ret;
	int		total;

	tmp = ft_strnew(5);
	ret = 0;
	total = 0;
	s1 = ft_strnew(1);
	while (*s)
	{
		ret = ft_printf_unicode((unsigned char*)tmp, *s);
		tmp[ret] = '\0';
		total += ret;
		if (total > e->precision && e->precision >= 0)
		{
			total -= ret;
			s1[total] = '\0';
			break ;
		}
		s2 = ft_strjoin_free(s1, tmp, 1);
		s1 = s2;
		s++;
	}
	ft_printf_putflags(e, s1);
	ft_strdel(&tmp);
}

void			ft_printf_smaj(t_env *e)
{
	wchar_t *s;
	char	*s1;
	char	*s2;

	s = va_arg(e->pa, wchar_t*);
	s1 = NULL;
	s2 = NULL;
	e->type = 'S';
	if (s == NULL)
	{
		ft_printf_putflags(e, ft_strdup("(null)"));
	}
	else
		ft_printf_parse_smaj(e, s, s1, s2);
}
