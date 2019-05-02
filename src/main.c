/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:19:02 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/02 17:32:33 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int		usage(char *bin)
{
	dprintf(2, "Usage: %s [-hf] host\n", bin);
	return (1);
}

static char		**invalid_option(char *bin, char c)
{
	dprintf(2, "%s: illegal option -- %c\n", bin, c);
	usage(bin);
	return (NULL);
}

static int		valid_option(char c, t_opt *opt)
{
	if (c == 'h')
		opt->h = 1;
	else if (c == 'v')
		opt->v = 1;
	else
		return (0);
	return (1);
}

static char		**get_options(char **av, t_opt *opt)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][1] == '-')
			{
				if (av[i][2])
					return (invalid_option("ft_ping", av[i][1]));
				else
					return (av + i + 1);
			}
			else if (!valid_option(av[i][j], opt))
				return (invalid_option("ft_ping", av[i][j]));
			j++;
		}
		i++;
	}
	return (av + i);
}

int				main(int ac, char **av)
{
	t_opt	opt;

	if (ac < 2)
		return (usage("ft_ping"));
	memset(&opt, 0, sizeof(opt));
	if (!(av = get_options(av, &opt)))
		return (1);
	if (!strlen(av[0]) || av[1] || opt.h)
		return (usage("ft_ping"));
	if (ft_ping(av[0]) < 0)
		return (-1);
	return (0);
}
