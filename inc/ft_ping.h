/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:09:39 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/02 19:13:43 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdio.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <sys/time.h>

# define FALSE	0
# define TRUE	1

typedef struct			s_opt
{
	int					h;
	int					v;
}						t_opt;


typedef struct			s_icmp_packet
{
	struct icmp			icmp_header;
}						t_icmp_packet;

typedef struct			s_ping
{
	int					do_ping;
	int					sockfd;
	struct sockaddr_in	to;
	char				ipv4[16];
	struct icmp			packet;
	int					iseq;
}						t_ping;


t_ping					g_ping;

int						ping(char *_host);

#endif
