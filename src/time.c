/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:53:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/21 16:55:07 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_elem							*add_elem(float time)
{
	t_elem	*elem;

	if (!(elem = (t_elem*)malloc(sizeof(t_elem))))
		return (NULL);
	elem->time = time;
	elem->next = NULL;
	return (elem);
}

t_elem							*e_type(float time)
{
	t_elem	*tmp;

	tmp = _ping.rtt.list;
	if (!tmp)
	{
		if (!(tmp = add_elem(time)))
			return (NULL);
		_ping.rtt.list = tmp;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = add_elem(time)))
			return (NULL);
	}
	return (tmp);
}

float							ft_fabs(float value)
{
	if (value < 0)
		return (-value);
	return (value);
}

float							ft_sqrt(float nb)
{
	float	i;

	i = 0;
	if (nb < 0)
		return (0);
	while (i * i < nb)
		i += 0.000001;
	if (ft_fabs(i * i - nb) < 0.001)
		return (i);
	return (0);
}

float							get_e_type(void)
{
	t_elem	*time;
	float	v;
	float	e_type;

	v = 0;
	time = _ping.rtt.list;
	while (time)
	{
		v += (time->time - _ping.rtt.avg) * (time->time - _ping.rtt.avg);
		time = time->next;
	}
	v /= _ping.spack;
	e_type = ft_sqrt(v);
	return (e_type);
}

void							free_e_type(void)
{
	t_elem	*tmp;
	t_elem	*back;

	tmp = _ping.rtt.list;
	while (tmp)
	{
		back = tmp;
		tmp = tmp->next;
		free(back);
	}
}

void							get_rtt(float time)
{
	_ping.rtt.tt += time;
	e_type(time);
	_ping.rtt.ttsq += time * time;
	if (_ping.rtt.min == 0.0)
		_ping.rtt.min = time;
	if (_ping.rtt.max == 0.0)
		_ping.rtt.max = time;
	if (time < _ping.rtt.min)
		_ping.rtt.min = time;
	if (time > _ping.rtt.max)
		_ping.rtt.max = time;
	_ping.rtt.avg = _ping.rtt.tt / (float)_ping.iseq;
}
