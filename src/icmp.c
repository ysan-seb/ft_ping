#include "ft_ping.h"

void			*imp_packet()
{
	struct icmphdr	icmp_header;
	struct iphdr	ip_header;
	void			*packet;

	if (!(packet = malloc(sizeof(icmp_header) + sizeof(ip_header)))
		return (NULL);
	icmp_header = (struct icmphdr)packet;
	icmp.type = 8;
	icmp.code = 0;
	icmp.checksum = 0;
	icmp.echo.id = getpid();
	icmp.echo.sequence = 0;
	ip_header = (struct ip_header)(packet + sizeof(icmp_header));


}
