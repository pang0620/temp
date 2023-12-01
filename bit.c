#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argb[]) {
	char buf[2048];
	char result[256];
	int len, ns;
	FILE *fp;

	ns = atoi(argb[1]);

	if ((len=recv(ns, buf, sizeof(buf), 0)) == -1) {
		perror("recv");
		exit(1);
	}
	printf("[Bit] From Client: %s\n", buf);

	if (strcmp("CPU", buf) == 0) {
		fp = popen("cat /proc/cpu/alignment /proc/cpu/swp_emulation", "r");
		size_t bytesRead = fread(result, 1, sizeof(result), fp);
		pclose(fp);

		strcpy(buf, result);
		if ((send(ns, buf, strlen(buf) + 1, 0)) == -1) {
			perror("send");
			exit(1);
		} else { printf("==Send Complete==\n"); }
	}

	if (strcmp("UNAME", buf) == 0) {
		fp = popen("uname -a", "r");
		size_t bytesRead = fread(result, 1, sizeof(result), fp);
		pclose(fp);

		strcpy(buf, result);
		if ((send(ns, buf, strlen(buf) + 1, 0)) == -1) {
			perror("send");
			exit(1);
		} else { printf("==Send Complete==\n"); }
	}

	if (strcmp("WHO", buf) == 0) {
		fp = popen("who", "r");
		size_t bytesRead = fread(result, 1, sizeof(result), fp);
		pclose(fp);

		strcpy(buf, result);
		if ((send(ns, buf, strlen(buf) + 1, 0)) == -1) {
			perror("send");
			exit(1);
		} else { printf("==Send Complete==\n"); }
	}

	if (strcmp("LAST", buf) == 0) {
		fp = popen("last", "r");
		size_t bytesRead = fread(result, 1, sizeof(result), fp);
		pclose(fp);

		strcpy(buf, result);
		if ((send(ns, buf, strlen(buf) + 1, 0)) == -1) {
			perror("send");
			exit(1);
		} else { printf("==Send Complete==\n"); }
	}
	



	close(ns);
}

