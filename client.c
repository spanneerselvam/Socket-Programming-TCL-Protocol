 /**************************
	socket example, client
	spring 2018
 **************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main (int, char *[]);


/********************
 * main
 ********************/
int main (int argc, char *argv[])
{
	int i;
	int sockfd = 0, n = 0;
	char buff[1024];
	char *p;
	struct sockaddr_in serv_addr; 
	FILE *f1;
	char buffer[10];
	size_t data;
	if (argc != 5)
	{
		printf ("Usage: %s <input file, output file,ip of server,server port> \n",argv[0]);
		return 1;
	} 

	// set up
	memset (buff, '0', sizeof (buff));
	memset (&serv_addr, '0', sizeof (serv_addr)); 

	// open socket
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf ("Error : Could not create socket \n");
		return 1;
	} 

	// set address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[4])); 

	if (inet_pton (AF_INET, argv[3], &serv_addr.sin_addr) <= 0)
	{
		printf ("inet_pton error occured\n");
		return 1;
	} 

	// connect
	if (connect (sockfd, (struct sockaddr *)&serv_addr, sizeof (serv_addr)) < 0)
	{
		printf ("Error : Connect Failed \n");
		return 1;
	} 
	// input, send to server, receive it back, and output it
	f1 = fopen(argv[1], "r");
	if(f1 == NULL)
	{
		printf("can't open %s file \n", argv[1]);
		exit(0);
	}
	write(sockfd, argv[2],strlen(argv[2])+1);
	while (0 < (data =fread(buffer,1,10,f1)))
{
		write (sockfd,buffer, data); 
		
}
	fclose(f1);
	close (sockfd);

	return 0;
}
