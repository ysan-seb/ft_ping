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

unsigned short eval_checksum(unsigned short *data, int size)
{
	unsigned long checksum = 0;

	while (size > 1)
	{
		checksum = checksum+*data++;
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
	g_ping.packet.icmp_type = ICMP_ECHO;
	g_ping.packet.icmp_code = 0;
	g_ping.packet.icmp_cksum = 0;
	g_ping.packet.icmp_id = getpid();
	g_ping.packet.icmp_seq = 0;
	g_ping.packet.icmp_cksum = eval_checksum((unsigned short *)&g_ping.packet, sizeof(g_ping.packet));
}

void						sighandler(int sig)
{
	int		_status;

	if (sig == SIGALRM)
	{
		create_icmp_packet();
		if ((_status = sendto(g_ping.sockfd, &g_ping.packet, sizeof(g_ping.packet), 0, (struct sockaddr *)&g_ping.to, sizeof(g_ping.to))) < 0)
		{
			dprintf(2, "[\e[38;5;160m-\e[0m] sendto error.\n");
			return ;
		}
		printf("[\e[38;5;82m+\e[0m] Sendto success (%d bytes send).\n", _status);
		char buffer[548];
		struct sockaddr_storage src_addr;

		struct iovec iov[1];
		iov[0].iov_base=buffer;
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
		printf("[\e[38;5;82m+\e[0m] recvmsg success (%d bytes receive).\n", _status);
		//	g_ping.iseq++;
		//printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%f ms\n", _status, g_ping.ipv4, g_ping.iseq, g_ping.ttl, 0.0);
		alarm(1);
	}
	else if (sig == SIGINT)
	{
		g_ping.do_ping = FALSE;
		printf("\r--- ping statistics ---\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("\rtoto\n");
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
	_hints = init_hints();
	if ((_status = getaddrinfo(_node, 0, &_hints, &_res)) != 0)
		return (error("[\e[38;5;160m-\e[0m] Getaddrinfo failed."));
	printf("[\e[38;5;82m+\e[0m] Getaddrinfo success.\n");
	if (!(_src = get_target(_res)))
		return (error("[\e[38;5;160m-\e[0m] get_target failed."));
	inet_ntop(AF_INET, _src, g_ping.ipv4, sizeof(g_ping.ipv4));
	printf("target: %s -> %s\n", _node, g_ping.ipv4);
	if ((g_ping.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		return (error("[\e[38;5;160m-\e[0m] Socket error.\n"));
	printf("[\e[38;5;82m+\e[0m] Socket success.\n");
	g_ping.to.sin_family = AF_INET;
	g_ping.to.sin_addr.s_addr = inet_addr(g_ping.ipv4);
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
