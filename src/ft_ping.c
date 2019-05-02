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

static int					ft_gai_sterror(int ecode)
{
	static char *emsg[] = {
		[EAI_ADDRFAMILY] = "address family for hostname not supported",
		[EAI_AGAIN] = "temporary failure in name resolution",
		[EAI_BADFLAGS] = "invalid value for ai_flags",
		[EAI_FAIL] = "non-recoverable failure in name resolution",
		[EAI_FAMILY] = "ai_family not supported",
		[EAI_MEMORY] = "memory allocation failure",
		[EAI_NODATA] = "no address associated with hostname",
		[EAI_NONAME] = "hostname nor servname provided, or not known",
		[EAI_SERVICE] = "servname not supported for ai_socktype",
		[EAI_SOCKTYPE] = "ai_socktype not supported",
		[EAI_SYSTEM] = "system error returned in errno",
		[EAI_BADHINTS] = "invalid value for hints",
		[EAI_PROTOCOL] = "resolved protocol is unknown",
		[EAI_OVERFLOW] = "argument buffer overflow",
	};

	dprintf(2, "ft_ping: %s\n", emsg[ecode]);
	return (-1);
}

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
	int				ecode;
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				sock;

	hints = init_hints();
	if ((ecode = getaddrinfo(host, 0, &hints, &res) != 0))
		return (ft_gai_sterror(ecode));
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		dprintf(2, "ft_ping: Error in connection.\n");
		return (-1);
	}
	printf("ft_ping: connected.\n");
	//printf("PING %s (%%ip): 56 data bytes\n", host);
	//printf("64 bytes from %%ip: icmp_seq=%d ttl=%d time=%d ms\n", 0, 0, 0);
	return (0);
}
