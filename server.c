#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 9000

int main() {
	// init
	char buf[2048];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);

	// gen server socket
	if ((sd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	printf("==Create Socket==\n");

	// set addr
	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	// bind
	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("bind");
		exit(1);
	}
	printf("==Create Socket==\n");

	// listen
	if (listen(sd, 5)) {
		perror("listen");
		exit(1);
	}
	printf("==Listen Socket==\n");

	while (1) {
		if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) {
			perror("accept");
			exit(1);
		}
		printf("==Accept Client\n");

		switch (fork()) {
			case 0:
				printf("====Fork Client\n");
				close(sd);
				sprintf(buf, "%d", ns);
				execlp("./bit", "bit", buf, (char *)0);
				close(ns);
		}
		close(ns);
	}
}
