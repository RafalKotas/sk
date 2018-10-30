#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char** argv) {

int sfd,rc;
char buf[128];
struct sockaddr_in saddr;
struct hostent* addrent;

addrent = gethostbyname(argv[1]);
sfd = socket(PF_INET, SOCK_STREAM,0);
saddr.sin_family = AF_INET;
saddr.sin_port = htons(atoi(argv[2]));

memcpy(&saddr.sin_addr.s_addr, addrent->h_addr,addrent->h_length);
connect(sfd, (struct sockaddr*)&saddr, sizeof(saddr));

write(sfd, argv[3], 7);
rc = read(sfd, buf, 128);
write(1, buf, rc);
close(sfd);
return 1;
}
