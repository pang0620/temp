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
	struct sockaddr_in sin;
	int sd, len;
	char buf[2048];

	// set addr
	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	// connect server
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	printf("==Create Socket==\n");

	// connect
	if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("connect");
		exit(1);
	}
	printf("==Connect Server==\n");


	// option
	printf("CPU/UNAME/WHO/LAST\n: ");
	scanf("%s", buf);
	//strcpy(buf, "from client");

	//send
	if (send(sd, buf, sizeof(buf)+1, 0) == -1) {
		perror("send");
		exit(1);
	}

	// recieve
	if ((len = recv(sd, buf, sizeof(buf), 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[len]='\0';
	printf("From Server: \n%s", buf);

	close(sd);
}
