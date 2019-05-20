#include "ft_ping.h"

static int					error(char *emsg)
{
	dprintf(2, "%s\n", emsg);
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
	static int seq = 1;
	_ping.packet.icmp.icmp_type = ICMP_ECHO;
	_ping.packet.icmp.icmp_code = 0;
	_ping.packet.icmp.icmp_cksum = 0;
	_ping.packet.icmp.icmp_id = getpid();
	_ping.packet.icmp.icmp_seq = seq++;
	_ping.packet.icmp.icmp_cksum = eval_checksum((unsigned short *)&_ping.packet, sizeof(_ping.packet));
}

void						sighandler(int sig)
{
	int		status;

	if (sig == SIGALRM)
	{
		create_icmp_packet();
		if ((status = sendto(_ping.sockfd, &_ping.packet, sizeof(_ping.packet), 0, (struct sockaddr *)&_ping.to.to, sizeof(_ping.to.to))) < 0)
		{
			dprintf(2, "[\e[38;5;160m-] sendto error.\n");
			return ;
		}
		alarm(1);
		_ping.spack++;
		_ping.iseq++;
		struct timeval _before;
		memset(&_before, 0, sizeof(_before));
		gettimeofday(&_ping.t.snd_packet, NULL);
	}
	else if (sig == SIGINT)
	{
		int percent;
		percent = (_ping.spack > 0 ) ? 100 - (_ping.rpack * 100 / _ping.spack) : 0;
		_ping.do_ping = FALSE;
		printf("\r--- %s ping statistics ---\n", _ping.to.node);
		printf("%d packets transmitted, %d packets received, %d%% packet loss\n", _ping.spack, _ping.rpack, percent);
		if (_ping.rpack > 0)
			printf("\rround-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", _ping.rtt.min, _ping.rtt.avg, _ping.rtt.max, get_e_type());
		print_e_type();
		exit(EXIT_SUCCESS);
	}
}

int							ping(char *_node, t_opt opt)
{
	int						_status;
	struct addrinfo			_hints;
	struct addrinfo			*_res;
	void					*_src;
	memset(&_ping, 0, sizeof(_ping));
	_ping.do_ping = TRUE;
	_ping.to.node = _node;
	_hints = init_hints();
	if ((_status = getaddrinfo(_node, 0, &_hints, &_res)) != 0)
		return (error("[\e[38;5;160m-] Getaddrinfo failed."));
	if (!(_src = get_target(_res)))
		return (error("[\e[38;5;160m-] get_target failed."));
	inet_ntop(AF_INET, _src, _ping.to.ipv4, sizeof(_ping.to.ipv4));
	if ((_ping.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		return (error("[\e[38;5;160m-] Socket error.\n"));
	_ping.verbose = (opt.v) ? 1 : 0;
	_ping.to.to.sin_family = AF_INET;
	_ping.to.to.sin_addr.s_addr = inet_addr(_ping.to.ipv4);
	printf("PING %s (%s) 56 bytes of data.\n", _node, _ping.to.ipv4);
	signal(SIGALRM, sighandler);
	signal(SIGINT, sighandler);
	alarm(1);
	while (_ping.do_ping) {
		_status = 0;
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
		if ((_status = recvmsg(_ping.sockfd, &message, 0)) < 0)
			return -1;
		double time;
		if (buffer.icmp.icmp_type == ICMP_ECHOREPLY)
		{
			if (buffer.icmp.icmp_id == getpid())
			{
				struct timeval _after;
				memset(&_after, 0, sizeof(_after));
				gettimeofday(&_ping.t.rec_packet, NULL);
				time = ((_ping.t.rec_packet.tv_sec - _ping.t.snd_packet.tv_sec) * 1000.0) + ((_ping.t.rec_packet.tv_usec - _ping.t.snd_packet.tv_usec) / 1000.0);
				get_rtt(time);
				_ping.rpack++;
				if (_ping.verbose)
					printf("From %s: icmp_seq=%d type: %d code: %d\n", _ping.to.ipv4, (!_ping.iseq) ? 0 : _ping.iseq - 1, buffer.icmp.icmp_type, buffer.icmp.icmp_code);
				else
					printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", _status, _ping.to.ipv4, _ping.iseq, buffer.ip.ttl, time);
			}
		}
		else if (buffer.icmp.icmp_type != ICMP_ECHO)
			printf("From %s: icmp_seq=%d type: %d code: %d\n", _ping.to.ipv4, _ping.iseq - 1, buffer.icmp.icmp_type, buffer.icmp.icmp_code);
	}
	freeaddrinfo(_res);
	return (0);
}
