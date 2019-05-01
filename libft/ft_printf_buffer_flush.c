/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer_flush.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:29:45 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:41:59 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		sprintf_addtobuffer(t_env *e)
{
	char *tmp;

	tmp = NULL;
	if (e->str == NULL)
		e->str = ft_strdup(e->result);
	else
	{
		tmp = ft_strdup(e->str);
		ft_strdel(&e->str);
		e->str = ft_strjoin(tmp, e->result);
		ft_strdel(&tmp);
	}
}

void			ft_printf_buffer_flush(t_env *e)
{
	e->result[e->index] = '\0';
	if (e->family == 0)
		ft_putstr(e->result);
	else if (e->family == 1)
		ft_putstr_fd(e->result, e->fd);
	else if (e->family == 2)
		fwrite(&e->result, sizeof(char), e->index, e->file);
	else if (e->family == 3)
		sprintf_addtobuffer(e);
	e->index = 0;
	e->result[0] = '\0';
}
