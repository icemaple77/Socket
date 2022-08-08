#include"../tcpSocket/tcpSocket.h"

int main()
{
	SOCKET sockClnt;

	int sendStatus, i = 0;

	char* ackmsg = "ACK at";
	char* ok = "OK";
	char buf[BUF_length] = { 0 };

	bool stop = false;

	time_t t;
	time_t tmpcal_ptr;

	struct tm* tmp_ptr = NULL;

	struct timeval tv; //set up time for usec

	
	printf("======== TCP Client ========\n");
	//Init
	init_Socket();
	/* Intializes random number generator */
	srand((unsigned)time(&t));
	
	//Create 
	sockClnt=createSocketClient(SERVER_IP_ADDR, PORT);
	
	
	while (key)
	{	
		//recv		
		if (recv(sockClnt, buf, BUF_length-1, 0) == SOCKET_ERROR)
		{
			err("Receive");
		}
		buf[BUF_length - 1] = 0x00;  /* force ending with '\0' */


		if (buf[0] == QUITKEY)
			break;

		printf("%2d Request from Server: %s\n", i++, buf);
		/* send message */
		sendStatus = send(sockClnt, buf, strlen(buf), 0);
		if (sendStatus == 0)
			break;  /* nothing has been sent */
		if (sendStatus == SOCKET_ERROR) {
			err("Sending");
			break;
		}
		time(&tmpcal_ptr); // set up time as usec
		tmp_ptr = localtime(&tmpcal_ptr);
		gettimeofday(&tv, NULL); // get time in usec
		printf("   Sent: TCP=[%s %02d:%02d:%02d:%03d:%03d]£¬ Random=[%03d] \n", 
			ackmsg, tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec, tv.tv_usec / 1000, tv.tv_usec % 1000, rand() % 1000);
		
	}
	if ((closesocket(sockClnt)) == SOCKET_ERROR) {
		printf("closesocket() failed: %d\n", WSAGetLastError());
		exit(SOCKET_ERROR);
	}






	closesocket(sockClnt);
	close_Socket();
	printf("....Client returned!\n\n");

	return 0;
}