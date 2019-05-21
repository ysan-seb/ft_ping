/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maki <maki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:09:39 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/21 17:02:57 by ysan-seb         ###   ########.fr       */
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
# include <signal.h>

# define FALSE	0
# define TRUE	1

typedef struct			s_buffer {
	struct iphdr		ip;
	struct icmp			icmp;
	char				b[16];
}						t_buffer;

typedef struct			s_elem
{
	float				time;
	struct s_elem		*next;
}						t_elem;

typedef struct			s_opt
{
	int					h;
	int					v;
}						t_opt;

typedef struct			s_rtt
{
	t_elem				*list;
	float				min;
	float				max;
	float				avg;
	float				tt;
	float				ttsq;
}						t_rtt;

typedef struct			s_time
{
	struct timeval		snd_packet;
	struct timeval		rec_packet;
}						t_time;

typedef struct			s_target
{
	char				*node;
	struct sockaddr_in	to;
	char				ipv4[16];
	char				ip_ref[16];
}						t_target;

typedef struct			s_packet
{
	struct icmp			icmp;
	char				b[28];
}						t_packet;

typedef struct			s_ping
{
	int					verbose;
	int					do_ping;
	int					sockfd;
	int					spack;
	int					rpack;
	int					iseq;
	int					err;
	t_target			to;
	t_packet			packet;
	t_rtt				rtt;
	t_time				t;
}						t_ping;

t_ping					_ping;

int						ping(char *_host, t_opt opt);
void					get_rtt(float time);
void					print_e_type(void);
float					get_e_type(void);
int						send_packet(void);
int						recv_packet(void);
void					free_e_type(void);

#endif
