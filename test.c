#include <stdio.h>
#include <sys/socket.h>

int	main() {
	printf("%lu\n", sizeof(struct msghdr));
}
