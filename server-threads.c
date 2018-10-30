#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>


struct cln {
int cfd;
struct sockaddr_in caddr; 
};

void* cthread(void* arg) {
struct cln* c = (struct cln*)arg;
printf("new connection %s ", inet_ntoa((struct in_addr)c->caddr.sin_addr));
write(c->cfd, "Hello world", 11);
close(c->cfd);
free(c);
return 0;

}

int main() {
int sfd, on =1;
sfd = socket(AF_INET, SOCK_STREAM, 0);
socklen_t sl;

pthread_t tid;
struct sockaddr_in saddr, caddr;


saddr.sin_family = AF_INET;
saddr.sin_addr.s_addr = INADDR_ANY;
saddr.sin_port = htons(50001);
sfd = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *) on, sizeof(on));
int i = bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
printf("i=%d\n", i);
listen(sfd, 5);
while(1) {
struct cln* c = malloc(sizeof(struct cln));
sl = sizeof(c->caddr);
c->cfd = accept(sfd, (struct sockaddr*)&c->caddr, &sl);
pthread_create(&tid, NULL, cthread,c);
pthread_detach(tid); 
}
close(sfd);
return 0;
}