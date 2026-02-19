# TCP-Even-Odd-Filter

## Preview

```
┌──────────┐    input.txt     ┌──────────┐
│  Client  │ ───────────────► │  Server  │
│          │                  │ Process  │
│          │ ◄─────────────── │          │
│  Print   │    Sum & Type    │          |
└──────────┘                  └──────────┘
```

---

## `server.c` 

### Used Libraries 

```c
#include <stdio.h>          // printf, fopen, fscanf
#include <string.h>         // strncmp, strlen
#include <arpa/inet.h>      // inet_pton, htonl
#include <sys/socket.h>     // socket, bind, listen, accept, send
#include <netinet/in.h>     // struct sockaddr_in
```

#### What is expeteted in input.txt
```
EVEN(3,4,6)
```
OR
```
ODD(1,2,3)
```


###  Filtering between EVEN / ODD

```c
int keep_even = (strncmp(name, "EVEN", 4) == 0);
int keep_odd  = (strncmp(name, "ODD",  3) == 0);

if (keep_even || keep_odd) {
    ame = keep_even ? "EVEN" : "ODD";
    int target = keep_even ? 0 : 1;

    if (a % 2 != target) a = 0;  
    if (b % 2 != target) b = 0;
    if (c % 2 != target) c = 0;
}

sum = a + b + c;
```

### Sending back to client

```c
int ssum = htonl(sum);                 
send(cfd, ame, strlen(ame), 0);         
send(cfd, &ssum, sizeof(ssum), 0);      
```



---

## `client.c`

###  Used Libraries

```c
#include <stdio.h>          // printf, fopen, fread, feof
#include <sys/socket.h>     // socket, connect, send, recv
#include <netinet/in.h>     // struct sockaddr_in
#include <arpa/inet.h>      // inet_pton
#include <stdlib.h>        
```

### Sending mechanism to server

```c
void send_file(FILE *fp, int sockfd) {
    char buffer[265];
    while (!feof(fp)) {
        int n = fread(buffer, 1, 265, fp);
        if (n > 0) {
            send(sockfd, buffer, n, 0);
        }
    }
}
```



###  Reciving mechanism from server

```c
char msg[100];
int sum = 0;

read(sockfd, msg, 100);              
recv(sockfd, &sum, sizeof(sum), 0);   
int ssum = ntohl(sum);                

printf("Name: %s\n", msg);
printf("Sum: %d\n", ssum);
```
---

## How to Run

```bash
# 1. create input.txt
echo "EVEN(3,4,6)" > input.txt

# 2. compile the code
gcc server.c -o server
gcc client.c -o client

# 3. run the server
./server

# 4. run the client (in another terminal)
./client
```

