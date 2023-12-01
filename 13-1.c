#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9002

int main() {
	int sd;
	char buf[256];
	struct sockaddr_in sin;

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ((sd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("listen");
		exit(1);
	}

	if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("connect");
		exit(1);
	}

	printf("**From Server : %s\n", buf);

	strcpy(buf, "I want a HTTP");

	if (send(sd, buf, sizeof(buf) + 1, 0) == -1) {
		perror("send");
		exit(1);
	}

	close(sd);
}
