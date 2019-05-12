/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:18:58 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/02 20:55:36 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

//printf("PING %s (%%ip): 56 data bytes\n", host);
//printf("64 bytes from %%ip: icmp_seq=%d ttl=%d time=%d ms\n", 0, 0, 0);

static struct addrinfo		init_hints(void)
{
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	return (hints);
}

int							ft_ping(char *host)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct addrinfo		*p;
	struct sockaddr_in	*tmp;
	void				*addr;
	char				_host[64];
	int					_status;
	int					sock;
	memset(&_host, 0, 64);
	hints = init_hints();
	if ((_status = getaddrinfo(host, 0, &hints, &res)) != 0)
	{
		dprintf(2, "[\e[38;5;160m-\e[0m] Getaddrinfo failed.\n");
		return (-1);
	}
	printf("[\e[38;5;82m+\e[0m] Getaddrinfo success.\n");
	p = res;
	while (p != NULL)
	{
		if (p->ai_family == AF_INET)
		{
			tmp = (struct sockaddr_in *)p->ai_addr;
			addr = &(tmp->sin_addr);
		}
		p = p->ai_next;
	}
	inet_ntop(AF_INET, addr, _host, sizeof(_host));
	if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		dprintf(2, "[\e[38;5;160m-\e[0m] Socket error.\n");
		return (-1);
	}
	printf("[\e[38;5;82m+\e[0m] Socket success.\n");
	freeaddrinfo(res);
	printf("host: %s -> %s\n", host, _host);
	if ((_status = sendto(sock, "aaaa", 4, 0, (struct sockaddr*)tmp, tmp->sin_addrlen)) < 0)
	{
		perror("sendto");
		dprintf(2, "[\e[38;5;160m-\e[0m] sendto error.\n");
		return (-1);
	}
	printf("[\e[38;5;82m+\e[0m] Sendto success.\n");
	return (0);
}
