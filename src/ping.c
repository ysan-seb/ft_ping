#include "ft_ping.h"
#include <signal.h>

static int					error(char *_emsg)
{
	dprintf(2, "%s\n", _emsg);
	return (-1);
}

static struct addrinfo		init_hints(void)
{
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	return (hints);
}

static void					*get_target(struct addrinfo *_res)
{
	struct addrinfo			*_tmp;
	struct sockaddr_in		*_ipv4;

	_tmp = _res;
	while (_tmp)
	{
		if (_tmp->ai_family == AF_INET)
		{
			_ipv4 = (struct sockaddr_in *)_tmp->ai_addr;
			return (&(_ipv4->sin_addr));
		}
		_tmp = _tmp->ai_next;
	}
	return (NULL);
}

unsigned short eval_checksum(unsigned short *_data, int _size)
{
	unsigned long _checksum = 0;

	while (_size > 1)
	{
		_checksum = _checksum+*_data++;
		_size = _size - sizeof(unsigned short);
	}

	if (_size)
		_checksum = _checksum + *(unsigned char *)_data;

	_checksum = (_checksum >> 16) + (_checksum & 0xffff);
	_checksum = _checksum + (_checksum >> 16);

	return (unsigned short)(~_checksum);
}

void						create_icmp_packet(void)
{
	g_ping.packet.icmp_type = ICMP_ECHO;
	g_ping.packet.icmp_code = 0;
	g_ping.packet.icmp_cksum = 0;
	g_ping.packet.icmp_id = getpid();
	g_ping.packet.icmp_seq = 0;
	g_ping.packet.icmp_cksum = eval_checksum((unsigned short *)&g_ping.packet, sizeof(g_ping.packet));
}


struct buffer {
	struct iphdr	ip;
	struct icmphdr	icmp;
};

void						get_rtt(float time)
{
	g_ping.rtt.tt += time;
	if (g_ping.rtt.min == 0.0)
		g_ping.rtt.min = time;
	if (g_ping.rtt.max == 0.0)
		g_ping.rtt.max = time;
	if (time < g_ping.rtt.min)
		g_ping.rtt.min = time;
	if (time > g_ping.rtt.max)
		g_ping.rtt.max = time;
	g_ping.rtt.avg = g_ping.rtt.tt / (float)g_ping.iseq;
}

void						sighandler(int sig)
{
	int		_status;

	if (sig == SIGALRM)
	{
		alarm(1);
		create_icmp_packet();
		if ((_status = sendto(g_ping.sockfd, &g_ping.packet, sizeof(g_ping.packet), 0, (struct sockaddr *)&g_ping.to, sizeof(g_ping.to))) < 0)
		{
			dprintf(2, "[\e[38;5;160m-\e[0m] sendto error.\n");
			return ;
		}
		g_ping.spack++;
		struct timeval _before;
		memset(&_before, 0, sizeof(_before));
		gettimeofday(&_before, NULL);

		//printf("[\e[38;5;82m+\e[0m] Sendto success (%d bytes send).\n", _status);
		//		char buffer[548];

		_status = 0;
		//
		struct buffer buffer;	
		struct sockaddr_storage src_addr;

		struct iovec iov[1];
		iov[0].iov_base=&buffer;
		iov[0].iov_len=sizeof(buffer);

		struct msghdr message;
		message.msg_name=&src_addr;
		message.msg_namelen=sizeof(src_addr);
		message.msg_iov=iov;
		message.msg_iovlen=1;
		message.msg_control=0;
		message.msg_controllen=0;
		if ((_status = recvmsg(g_ping.sockfd, &message, 0)) < 0)
		{
			perror("recvmsg");
			return ;
		}
		struct timeval _after;
		memset(&_after, 0, sizeof(_after));
		gettimeofday(&_after, NULL);
		
		double time;

		time = ((_after.tv_sec - _before.tv_sec) * 1000.0) + ((_after.tv_usec - _before.tv_usec) / 1000.0);
		//printf("[\e[38;5;82m+\e[0m] recvmsg success (%d bytes receive).\n", _status);
		g_ping.iseq++;
		get_rtt(time);
		if (buffer.icmp.type != 0 && buffer.icmp.code != 0)
			printf("From %s: icmp_seq=%d type: %d code: %d\n", g_ping.ipv4, g_ping.iseq, buffer.icmp.type, buffer.icmp.code);
		else
		{
			g_ping.rpack++;
			//if (time < 1.0)
			//	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", _status, g_ping.ipv4, g_ping.iseq, buffer.ip.ttl, time);
			//else
				printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", _status, g_ping.ipv4, g_ping.iseq, buffer.ip.ttl, time);
		}
	}
	else if (sig == SIGINT)
	{
		int percent;
		percent = (g_ping.spack > 0 ) ? 100 - (g_ping.rpack * 100 / g_ping.spack) : 0;
		g_ping.do_ping = FALSE;
		printf("\r--- %s ping statistics ---\n", g_ping.node);
		printf("\r%d/%d packets, %d%% loss, min/avg/max/mdev = %.3f/%.3f/%.3f/0.0 ms\n", g_ping.rpack, g_ping.spack, percent, g_ping.rtt.min, g_ping.rtt.avg, g_ping.rtt.max);
	}
	else if (sig == SIGQUIT)
	{
		int percent;
		percent = (g_ping.spack > 0 ) ? 100 - (g_ping.rpack * 100 / g_ping.spack) : 0;
		printf("\r%d/%d packets, %d%% loss, min/avg/ewma/max = %.3f/%.3f/0.0/%.3f ms\n", g_ping.rpack, g_ping.spack, percent, g_ping.rtt.min, g_ping.rtt.avg, g_ping.rtt.max);
	}
}

int							ping(char *_node)
{
	int						_status;
	struct addrinfo			_hints;
	struct addrinfo			*_res;
	void					*_src;

	memset(&g_ping, 0, sizeof(g_ping));
	g_ping.do_ping = TRUE;
	g_ping.node = _node;
	_hints = init_hints();
	if ((_status = getaddrinfo(_node, 0, &_hints, &_res)) != 0)
		return (error("[\e[38;5;160m-\e[0m] Getaddrinfo failed."));
//	printf("[\e[38;5;82m+\e[0m] Getaddrinfo success.\n");
	if (!(_src = get_target(_res)))
		return (error("[\e[38;5;160m-\e[0m] get_target failed."));
	inet_ntop(AF_INET, _src, g_ping.ipv4, sizeof(g_ping.ipv4));
//	printf("target: %s -> %s\n", _node, g_ping.ipv4);
	if ((g_ping.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		return (error("[\e[38;5;160m-\e[0m] Socket error.\n"));
//	printf("[\e[38;5;82m+\e[0m] Socket success.\n");
	g_ping.to.sin_family = AF_INET;
	g_ping.to.sin_addr.s_addr = inet_addr(g_ping.ipv4);
	//struct timeval tv;
	//tv.tv_sec = 1;
	//setsockopt(g_ping.sockfd, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
	printf("PING %s (%s) ?(?) bytes of data.\n", _node, g_ping.ipv4);
	alarm(1);
	signal(SIGALRM, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	while (g_ping.do_ping)
		;
	freeaddrinfo(_res);
	return (0);
}
