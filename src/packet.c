/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:58:05 by ysan-seb          #+#    #+#             */
/*   Updated: 2019/05/21 17:01:38 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void						err_type(int type)
{
	static char *emsg[] = {
		[ICMP_DEST_UNREACH] = "Destination Unreachable",
		[ICMP_SOURCE_QUENCH] = "Source Quench",
		[ICMP_REDIRECT] = "Redirect (change route)",
		[ICMP_ECHO] = "Echo Request",
		[ICMP_TIME_EXCEEDED] = "Time Exceeded",
		[ICMP_PARAMETERPROB] = "Parameter Problem",
		[ICMP_TIMESTAMP] = "Timestamp Request",
		[ICMP_TIMESTAMPREPLY] = "Timestamp Reply",
		[ICMP_INFO_REQUEST] = "Information Request",
		[ICMP_INFO_REPLY] = "Information Reply",
		[ICMP_ADDRESS] = "Address Mask Request",
		[ICMP_ADDRESSREPLY] = "Address Mask Reply",
	};

	_ping.err++;
	printf(" %s\n", emsg[type]);
}

unsigned short				eval_checksum(unsigned short *data, int size)
{
	unsigned long checksum;

	checksum = 0;
	while (size > 1)
	{
		checksum = checksum + *data++;
		size = size - sizeof(unsigned short);
	}
	if (size)
		checksum = checksum + *(unsigned char *)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (unsigned short)(~checksum);
}

void						create_icmp_packet(void)
{
	static int seq = 1;

	_ping.packet.icmp.icmp_type = ICMP_ECHO;
	_ping.packet.icmp.icmp_code = 0;
	_ping.packet.icmp.icmp_cksum = 0;
	_ping.packet.icmp.icmp_id = getpid();
	_ping.packet.icmp.icmp_seq = seq++;
	_ping.packet.icmp.icmp_cksum = eval_checksum((unsigned short *)&_ping.packet, sizeof(_ping.packet));
}

int							send_packet(void)
{
	int		status;

	create_icmp_packet();
	if ((status = sendto(_ping.sockfd, &_ping.packet, sizeof(_ping.packet),
					0, (struct sockaddr *)&_ping.to.to, sizeof(_ping.to.to))) < 0)
	{
		dprintf(2, "ft_ping: sending packet: Invalid argument\n");
		exit(1);
	}
	alarm(1);
	_ping.spack++;
	_ping.iseq++;
	ft_memset(&_ping.t.snd_packet, 0, sizeof(_ping.t.snd_packet));
	if (gettimeofday(&_ping.t.snd_packet, NULL) < 0)
		return (-1);
	return (0);
}

int							print_packet(t_buffer buffer, int status)
{
	double	time;

	ft_memset(&_ping.t.rec_packet, 0, sizeof(_ping.t.rec_packet));
	if (gettimeofday(&_ping.t.rec_packet, NULL) < 0)
		return (-1);
	time = ((_ping.t.rec_packet.tv_sec - _ping.t.snd_packet.tv_sec) * 1000.0)
		+ ((_ping.t.rec_packet.tv_usec - _ping.t.snd_packet.tv_usec) / 1000.0);
	get_rtt(time);
	_ping.rpack++;
	if (_ping.verbose)
		printf("From %s: type: %d code: %d\n",
				_ping.to.ipv4, buffer.icmp.icmp_type, buffer.icmp.icmp_code);
	else
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
				status, _ping.to.ipv4, _ping.iseq, buffer.ip.ttl, time);
	return (0);
}

int							recv_packet(void)
{
	int						status;
	t_buffer				buffer;
	struct sockaddr_storage	src_addr;
	struct iovec			iov[1];
	struct msghdr			message;

	status = 0;
	iov[0].iov_base = &buffer;
	iov[0].iov_len = sizeof(buffer);
	message.msg_name = &src_addr;
	message.msg_namelen = sizeof(src_addr);
	message.msg_iov = iov;
	message.msg_iovlen = 1;
	message.msg_control = 0;
	message.msg_controllen = 0;
	if ((status = recvmsg(_ping.sockfd, &message, 0)) < 0)
		return (-1);
	if (buffer.icmp.icmp_type == ICMP_ECHOREPLY)
	{
		if (buffer.icmp.icmp_id == getpid())
			if (print_packet(buffer, status) < 0)
				return (-1);
	}
	else if (buffer.icmp.icmp_type != ICMP_ECHO)
	{
		if (buffer.icmp.icmp_type >= 3 && buffer.icmp.icmp_type <= 18)
		{
			if (_ping.verbose)
				print_packet(buffer, status);
			else
			{
				printf("From %s:", _ping.to.ipv4);
				err_type(buffer.icmp.icmp_type);	
			}
		}
		else
			printf("From %s: type: %d code: %d\n",
				_ping.to.ipv4, buffer.icmp.icmp_type, buffer.icmp.icmp_code);
	}
	return (0);
}
