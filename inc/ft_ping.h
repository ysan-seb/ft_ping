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

typedef struct			s_rtt
{
	float				tt;
	float				min;
	float				avg;
	float				max;
	float				mdev;
}						t_rtt;

typedef struct			s_ping
{
	char				*node;
	int					do_ping;
	int					sockfd;
	struct sockaddr_in	to;
	char				ipv4[16];
	struct icmp			packet;
	int					iseq;
	int					spack;
	int					rpack;
	t_rtt				rtt;
	struct timeval		pstart;
	struct timeval		pend;
}						t_ping;


t_ping					g_ping;

int						ping(char *_host);

#endif
