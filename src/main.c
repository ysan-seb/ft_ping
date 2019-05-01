/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:19:02 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/01 17:25:29 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ping.h"

typedef struct	s_cmd
{
	char		*host;
	char		opt[3];
}				t_cmd;


int		usage(char *bin)
{
	dprintf(2, "Usage: %s [-hf] host\n", bin);
	return (1);
}

int		main(int ac, char **av)
{
	if (ac < 2)
		return (usage(av[0]));
	// options contient h ?
	//	-> usage
	// ! host
	//	-> usage
	//	go ping ->
	return (0);
}
