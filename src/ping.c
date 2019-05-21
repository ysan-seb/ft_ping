/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:59:15 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/21 17:01:35 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int					error(char *emsg)
{
	dprintf(2, "%s\n", emsg);
	return (-1);
}

static struct addrinfo		init_hints(void)
{
	struct addrinfo		hints;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	return (hints);
}

static void					*get_target(struct addrinfo *res)
{
	struct addrinfo			*tmp;
	struct sockaddr_in		*ipv4;

	tmp = res;
	while (tmp)
	{
		if (tmp->ai_family == AF_INET)
		{
			ipv4 = (struct sockaddr_in *)tmp->ai_addr;
			return (&(ipv4->sin_addr));
		}
		tmp = tmp->ai_next;
	}
	return (NULL);
}

void						ping_exit(void)
{
	int percent;

	percent = (_ping.spack > 0) ? 100 - (_ping.rpack * 100 / _ping.spack) : 0;
	_ping.do_ping = FALSE;
	printf("\r--- %s ping statistics ---\n", _ping.to.node);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n",
			_ping.spack, _ping.rpack, percent);
	if (_ping.rpack > 0)
	{
		printf("\rround-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
				_ping.rtt.min, _ping.rtt.avg, _ping.rtt.max, get_e_type());
		free_e_type();
	}
	if (!_ping.rpack)
		exit(1);
	if (_ping.err)
		exit(2);
	exit(0);
}

void						sighandler(int sig)
{
	if (sig == SIGALRM)
	{
		if (send_packet() < 0)
			return ;
	}
	else if (sig == SIGINT)
		ping_exit();
}

int							ping(char *node, t_opt opt)
{
	int						status;
	struct addrinfo			hints;
	struct addrinfo			*res;
	struct in_addr			*addr;
	void					*src;

	status = 0;
	ft_memset(&_ping, 0, sizeof(_ping));
	_ping.do_ping = TRUE;
	_ping.to.node = node;
	hints = init_hints();
	if ((status = getaddrinfo(node, 0, &hints, &res)) != 0)
	{
		if (status == -2 || status == -5)
			return (error("ft_ping: unknown host"));
		else
			return (error("[\e[38;5;160m-\e[0m] Getaddrinfo failed."));
	}
	if (!(src = get_target(res)))
		return (error("[\e[38;5;160m-\e[0m] get_target failed."));
	addr = src;
	inet_ntop(AF_INET, src, _ping.to.ipv4, sizeof(_ping.to.ipv4));
	if ((_ping.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		return (error("[\e[38;5;160m-\e[0m] Socket error.\n"));
	_ping.verbose = (opt.v) ? 1 : 0;
	_ping.to.to.sin_family = AF_INET;
	_ping.to.to.sin_addr.s_addr = addr->s_addr;
	printf("PING %s (%s) 56 data bytes\n", node, _ping.to.ipv4);
	signal(SIGALRM, sighandler);
	signal(SIGINT, sighandler);
	alarm(1);
	while (_ping.do_ping)
		recv_packet();
	return (0);
}
