#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

void send_file(FILE *fp, int sockfd){ //function to send file, while loop
char buffer [265]; 
while(!feof(fp)){
int n = fread(buffer,1,265,fp);
if(n>0){
send(sockfd,buffer,n,0);
}
}
}


int main(int argc, char* argv[]){ 
int sockfd = socket(AF_INET,SOCK_STREAM,0); //open socket

char* ip = "127.0.0.1";

struct sockaddr_in address; //where to connect
address.sin_port = htons(5001);
address.sin_family = AF_INET;
inet_pton(AF_INET,ip,&address.sin_addr.s_addr);

int con = connect(sockfd, &address, sizeof address); //connect


if(con == 0) { //if success send the file
printf("Connection Success\n");
FILE *fp;
char line[256];
fp = fopen("input.txt","rb");
send_file(fp, sockfd);
fclose(fp);
}
else {printf("Connection Failed\n");} //if failed



// recive the sum and type from the server
int sum = 0;
char msg[50] = {0}; 

read(sockfd, msg, 50); 
recv(sockfd, &sum, sizeof(sum), 0); 

int ssum = ntohl(sum);
printf("Name: %s\n", msg);
printf("Sum: %d\n", ssum);
}