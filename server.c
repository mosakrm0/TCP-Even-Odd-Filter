#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){
int sockfd = socket(AF_INET,SOCK_STREAM,0); //open socket

char* ip = "127.0.0.1";
struct sockaddr_in address;
address.sin_port = htons(5001);
address.sin_family = AF_INET;
inet_pton(AF_INET,ip,&address.sin_addr.s_addr);

bind(sockfd, &address, sizeof address);
listen(sockfd,1);


struct sockaddr_in caddr; socklen_t l = sizeof caddr; // New Struct
int cfd = accept(sockfd, (void*)&caddr, &l); // accept the connection

FILE *fp = fopen("input.txt","r"); //open file
fp = fopen("input.txt", "r");
char line[50];
int a,b,c;
char name[50];
fscanf(fp,"%49[^ (](%d,%d,%d)",name, &a,&b,&c); //extract the file
int sum;

char* ame = name;

int keep_even = (strncmp(name, "EVEN", 4) == 0);
int keep_odd  = (strncmp(name, "ODD",  3) == 0);

if (keep_even || keep_odd) {
    ame = keep_even ? "EVEN" : "ODD";
    int target = keep_even ? 0 : 1; 

    if (a % 2 != target) a = 0;
    if (b % 2 != target) b = 0;
    if (c % 2 != target) c = 0;
}

sum = a+b+c;

//send to client type and sum

int ssum = htonl(sum);
send(cfd, ame, strlen(ame), 0);
send(cfd, &ssum, sizeof(ssum), 0);


printf("Name: %s\n", ame);
printf("Sum: %d\n", sum);


}