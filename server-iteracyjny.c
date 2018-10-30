#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


void childend(int signo) {
wait(NULL);
}

int main() {

int fd = socket(PF_INET, SOCK_STREAM, 0);
socklen_t sl;
int sfd,cfd, on =1;
struct sockaddr_in saddr, caddr;

signal(SIGCHLD, childend);

saddr.sin_family = AF_INET;
saddr.sin_addr.s_addr = INADDR_ANY;
saddr.sin_port = htons(8080);
sfd = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *) on, sizeof(on));
bind(fd, (struct sockaddr*)&saddr, sizeof(saddr));

listen(fd, 5);
while(1) {

sl = sizeof(caddr);
cfd = accept(fd, (struct sockaddr*)&caddr, &sl);
if(fork()!=0) {
close(cfd);
continue;
}
close(sfd);
char pdwh[5];
read(cfd, pdwh, 6);
write(1,pdwh, 6);
write(1, " ", 1);
printf("new connection from %s:%d\n", inet_ntoa((struct in_addr) caddr.sin_addr), ntohs(caddr.sin_port)); 
write(1, "\n" ,1);

if ( pdwh[0] == '1' && pdwh[1] == '3' && pdwh[2] == '2' && pdwh[3] == '2' && pdwh[4] == '1' && pdwh[5] == '0') {
write(cfd, "HUBERT DOLNY ", 13);
}
else {
write(cfd, "NOT FOUND ", 10);
}
close(cfd);
return 0;
}
close(sfd);
close(fd);
return 0;
}

