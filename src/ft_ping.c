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
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	return (hints);
}

int							ft_ping(char *host)
{
	struct addrinfo	hints;
	struct addrinfo	*res;

	int				sock;
	ssize_t			size;

	hints = init_hints();
	if (getaddrinfo(host, 0, &hints, &res) != 0)
		return (-1);
	while (1)
	{
		if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		{
			dprintf(2, "ft_ping: socket error.\n");
			return (-1);
		}
		//sock opt
		if ((size = sendto(sock, NULL, 0, 0, 0, 0)) < 0)
		{
			dprintf(2, "ft_ping: sendto error.\n");
			return (-1);
		}
		if ((size = recvmsg(sock, NULL, 0)) < 0)
		{
			dprintf(2, "ft_ping: recvmsg error.\n");
			return (-1);
		}
		close (sock);
	}
	return (0);
}
