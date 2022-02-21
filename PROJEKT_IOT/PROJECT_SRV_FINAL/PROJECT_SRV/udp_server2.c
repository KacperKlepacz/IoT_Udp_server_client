// server program for udp connection 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include <sys/time.h>
#include <time.h>

#define PORT 8080 
#define MAXLINE 1000 

void help(char *arg[]);

// Driver code 
int main(int argc, char* argv[]) 
{ 
	if(argc != 2){help(&argv[0]);exit(1);}
	time_t ticks;
	struct tm * broketime;
	char timestamp[16];
	char buffer[100]; 
	char *message = "Received Data"; 
	int listenfd, len;
	FILE *logfile;
	char filename[64];
	char date[8];

	if(strcmp(argv[1],"IPv4") == 0){ 
		struct sockaddr_in servaddr, cliaddr; 
		bzero(&servaddr, sizeof(servaddr)); //Wype³nienie zerowymi

		// Create a UDP Socket 
		if((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			fprintf(stderr,"socket error : %s\n", strerror(errno));
                return 1;
		} 
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //bind the socket to all av intefaces
		servaddr.sin_port = htons(PORT); 
		servaddr.sin_family = AF_INET; 

		// bind server address to socket descriptor
		if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr) < 0 ){
			fprintf(stderr,"bind error : %s\n", strerror(errno));
                return 1;
		}
		while(1){
			len = sizeof(cliaddr); 
			int n = recvfrom(listenfd, buffer, sizeof(buffer), 
					0, (struct sockaddr*)&cliaddr,&len); //receive message from clients 
			buffer[n] = '\0';
			sprintf(date,"%.8s\n",&buffer[0]);
            int r = snprintf(filename,sizeof(char)*64,"IoT_log_%.8s.txt",date);
            logfile=fopen(filename,"a+");
            fprintf(logfile,"%s\n",buffer);
            fclose(logfile);
			 
		}
	}
	
	else if(strcmp(argv[1],"IPv6") == 0){
		struct sockaddr_in6 servaddr, cliaddr;
    	bzero(&servaddr, sizeof(servaddr));

    	// Create a UDP Socket
    	if((listenfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0 ){
    		fprintf(stderr,"socket error : %s\n", strerror(errno));
                return 1;
		}
    	servaddr.sin6_addr = in6addr_any;
    	servaddr.sin6_port = htons(PORT);
    	servaddr.sin6_family = AF_INET6;

    	// bind server address to socket descriptor
    	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    		fprintf(stderr,"bind error : %s\n", strerror(errno));
                return 1;
		}
		while(1){
			len = sizeof(cliaddr);
    		int n = recvfrom(listenfd, buffer, sizeof(buffer),
                    0, (struct sockaddr*)&cliaddr,&len); //receive message from clients
        	buffer[n] = '\0';
			sprintf(date,"%.8s\n",&buffer[0]);
			int r = snprintf(filename,sizeof(char)*64,"IoT_log_%.8s.txt",date);
			logfile=fopen(filename,"a+");
			fprintf(logfile,"%s\n",buffer);
			fclose(logfile);
		}
	}
	else{help(&argv[0]);exit(1);}
} 

void help(char *arg[]){
	printf("NOT CORRECT RUN\n");
	printf("IoT server program usage:");
	printf("%s <IPv4|IPv6>\n",arg[0]);
	printf("e.g. : %s IPv4\n",arg[0]);
}
