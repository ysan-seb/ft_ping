/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putflags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:36:31 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:36:32 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*getprecision(t_env *e, char *s, size_t len)
{
	char		tmp[e->precision - len];
	int			i;
	char		*ret;

	i = 0;
	ret = NULL;
	if (e->type != 'c' && e->type != 'C' && e->type != 'S' && e->type != 's'
			&& e->precision > (int)len)
	{
		while (i < e->precision - (int)len)
		{
			tmp[i] = '0';
			i++;
		}
		tmp[i] = '\0';
		if (!s)
			ret = ft_strjoin(tmp, "");
		else
			ret = ft_strjoin(tmp, s);
		ft_strdel(&s);
		return (ret);
	}
	return (s);
}

static char		*getfield(t_env *e, char *field, int len)
{
	char		c;
	int			i;

	i = 0;
	c = e->flag_zero == 1 ? '0' : ' ';
	if (e->field_width > len)
	{
		field = ft_strnew(e->field_width - len);
		while (i < e->field_width - len)
		{
			field[i] = c;
			i++;
		}
	}
	if (field == NULL)
		return (ft_strdup(""));
	return (field);
}

static char		*getdp(t_env *e, char *dp, char *s)
{
	dp = ft_strnew(2);
	if ((e->flag_diese == 1 && (e->type == 'x' || e->type == 'X'))
	|| e->type == 'p')
	{
		dp[0] = '0';
		if (e->type == 'x' || e->type == 'p')
			dp[1] = 'x';
		else
			dp[1] = 'X';
	}
	else if (e->flag_diese == 1 && (e->type == 'o' || e->type == 'O')
	&& s[0] != '0')
		dp[0] = '0';
	else if (e->type == 'd' || e->type == 'i' || e->type == 'o')
	{
		if (e->neg)
			dp[0] = '-';
		else if (e->flag_plus)
			dp[0] = '+';
	}
	return (dp);
}

static void		addtobuffer(t_env *e, char *s, char *dp, char *space)
{
	char		*field;
	char		*tmp;
	char		*tmp1;

	tmp = NULL;
	tmp1 = NULL;
	field = NULL;
	field = getfield(e, field, ft_strlen(s) + ft_strlen(dp));
	if (e->flag_moins)
		tmp = ft_strjoin(s, field);
	else
		tmp = ft_strjoin((!ft_strlen(field)
					|| field[0] == '0' ? field : dp), s);
	tmp1 = ft_strjoin((e->flag_moins || (!ft_strlen(field) || field[0] == '0')
	? dp : field), tmp);
	ft_printf_add_to_buffer(e, space, 0);
	ft_printf_add_to_buffer(e, tmp1, 0);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	ft_strdel(&field);
	ft_strdel(&dp);
	ft_strdel(&space);
	ft_strdel(&s);
}

void			ft_printf_putflags(t_env *e, char *s)
{
	char		*dp;
	char		*space;
	char		*ret;
	size_t		len;

	ret = NULL;
	len = ft_strlen(s);
	space = NULL;
	dp = NULL;
	space = getspace(e, space, s);
	ret = getprecision(e, s, len);
	if (ret == NULL)
		ret = ft_strdup("");
	dp = getdp(e, dp, ret);
	addtobuffer(e, ret, dp, space);
}
