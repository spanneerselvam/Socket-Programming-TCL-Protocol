 /**************************
 *     socket example, server
 *     spring 2018
 ***************************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>

int main (int, char *[]); 


/*********************
 * main
 *********************/
int main (int argc, char *argv[])
{
	size_t n, data;
	FILE  *f2;
	char fileName[1024]; //so we read 10 characters at a time
	//char temp[1024];
	size_t size=0;
	size_t i=0;
	char c;
	char *p; 
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr; 
	char buff[10];
	if(argc != 2)
	{
		printf("Usuage: %s <port number> \n",argv[0]);
		return 1;
	}
	// set up
	memset (&serv_addr, '0', sizeof (serv_addr));
	memset (buff, '0', sizeof (buff)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	serv_addr.sin_port = htons (atoi(argv[1])); 

	// create socket, bind, and listen
	listenfd = socket (AF_INET, SOCK_STREAM, 0);
	bind (listenfd, (struct sockaddr*)&serv_addr, sizeof (serv_addr)); 
	listen (listenfd, 10); 

	// accept and interact
	connfd = accept (listenfd, (struct sockaddr*)NULL, NULL); 
//	read(connfd, temp, sizeof(temp));
/*	
	while(c != "/0")
	{
		c = temp[i];
		i = i+1;
		size = size + 1;
		
	}
*/	
	if(n = read(connfd, fileName, sizeof(fileName))> 0)
	{
		printf("%s", fileName);
		f2 = fopen(fileName, "w");
		sleep(1);
	}
		// receive data and reply
	while ((data = read (connfd, buff, sizeof(buff)))>0)
	{
	

		fwrite (buff,1,data,f2); 
	}
	fclose(f2);
	close (connfd);
}
