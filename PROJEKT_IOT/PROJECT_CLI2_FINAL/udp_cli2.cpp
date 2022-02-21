// udp client driver program                                  
#include <stdio.h>                                    
#include <string.h>                            
#include <sys/types.h>                                         
#include <arpa/inet.h>               
#include <sys/socket.h>       
#include <netinet/in.h>                              
#include <unistd.h>       
#include <stdlib.h>   
#include <time.h>      
#define PORT 8080          
#define MAXLINE 1000  

void help(char *arg[]);

// Driver code     
int main( int argc, char* argv[])
{       
	if(argc != 4){help(&argv[0]);}
	char buffer[100];
	int sockfd, n;
	char test[100]="Received Data";
	time_t ticks;
	struct tm * broketime;
	char timestamp[20];
	
	if(strcmp(argv[1],"IPv4") == 0){
		
		struct sockaddr_in servaddr;
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_addr.s_addr = inet_addr(argv[2]);
    	servaddr.sin_port = htons(PORT);
    	servaddr.sin_family = AF_INET;
		if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			fprintf(stderr,"socket error : %s\n", strerror(errno));
                return 1;
		} 
		
		if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    	{
        	printf("\n Error : Connect Failed \n");
        	exit(0);
    	}
		for(;;){
			ticks=time(NULL);
			broketime=localtime(&ticks);
			strftime(timestamp,16,"%y.%m.%d %H:%M",broketime);
        	printf("%s\n",timestamp);
			float r3 = 1.f +(rand()%10) + 70 + (rand()%100/100.f);
	        int x = sprintf(buffer,"%s\n%s: %.2f %%%",timestamp,argv[3],r3);
	        sendto(sockfd, buffer, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
	        sleep(60);
        }
	}
	else if(strcmp(argv[1],"IPv6") == 0){
		
		struct sockaddr_in6 servaddr;
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin6_port = htons(PORT);
        servaddr.sin6_family = AF_INET6;
		inet_pton(AF_INET6, argv[2], &servaddr.sin6_addr);
		if((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
			fprintf(stderr,"socket error : %s\n", strerror(errno));
                return 1;
		}
		
		if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    	{
        	printf("\n Error : Connect Failed \n");
        	exit(0);
    	}
		for(;;){
			ticks = time(NULL);
			broketime=localtime(&ticks);
            strftime(timestamp,16,"%y.%m.%d %H:%M",broketime);
            printf("%s\n",timestamp);
        	float r3 = 1.f +(rand()%10) + 70 + (rand()%100/100.f);
        	int x = sprintf(buffer,"%s\n%s: %.2f %%%",timestamp,argv[3],r3);                        
			sendto(sockfd, buffer, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
            sleep(60);
    	}
	
	}
	else{help(&argv[0]);} 
 }

void help(char *arg[]){
	printf("NOT CORRECT RUN\n");
	printf("IoT humidity client program usage:");
	printf("%s <IPv4|IPv6> <server_ip_addr> <name_of_humidity_sensor>\n",arg[0]);
	printf("e.g.: %s IPv4 192.168.1.14 Humidity_sensor_1\n",arg[0]);
	printf("Remember to pass the name of sensor as one word e.g. with underscore: _ \n");
	exit(0);
}
