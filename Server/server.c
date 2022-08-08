#include"../tcpSocket/tcpSocket.h"


int main()
{	
	int i = 0, recvStatus;
	char buf[BUF_length] = {0};
	char* request = "R";
	char* ok = "OK";
	char cmd = QUITKEY; /* character ESC */
	bool stop = false;  /* bool tyle in stdbool.h. stop running */
	LARGE_INTEGER beginTime = { 0 };
	LARGE_INTEGER endTime = { 0 };
	SOCKET sockSer, sockClnt;


	init_Socket();
	
	sockSer = createSocketServer(ADDR_ANY,PORT);
	printf("======== TCP Server ========\n");


	//if client apply a connect
	printf("\nServer awaiting connection....\n");
	sockClnt=accept(sockSer, NULL, NULL);
	if (sockClnt == INVALID_SOCKET)
	{
		err("Accept");
	}
	
	//if success, next is communication with client;
	printf("....Connection established\n");

	/*
	char recvbuf[BUFSIZ] = { 0 };
	char sendbuf[BUFSIZ] = { 0 };*/

	while (key)
	{
		QueryPerformanceFrequency(&beginTime);
		//电脑CPU时钟频率
		double pcFreqms = (double)beginTime.QuadPart / 1000.0;
		double pcFrequs = (double)beginTime.QuadPart / 1000000.0;
		double pcFreqns = (double)beginTime.QuadPart / 1000000000.0;
		//开始计时
		QueryPerformanceCounter(&beginTime);
		//sending
		if (SOCKET_ERROR == send(sockClnt, request, strlen(request), 0))
		{
			err("send");
		}
		printf("%2d [Request:     %s]\n", i, request);

		//recv
		clear(buf);
		recvStatus = recv(sockClnt, buf, BUF_length - 1, 0);
		if (recvStatus == 0)
			break;
		if (recvStatus == SOCKET_ERROR) {
			err("receive");
			break;
		}
		QueryPerformanceCounter(&endTime);
		//那么下面计算得出的就是这之间的时间间隔了，单位为微秒

		int timeofms = (endTime.QuadPart - beginTime.QuadPart) / pcFreqms;
		int timeofus = (endTime.QuadPart - beginTime.QuadPart) / pcFrequs;
		long int timeofns = (endTime.QuadPart - beginTime.QuadPart) / pcFreqns;
		//printf("%d ms\n", timeofms);
		//printf("%d us\n", timeofus);
		//printf("%ld ns\n", timeofns);
		buf[recvStatus] = 0x00; /* force ending with '\0' */
		printf("    Replied from Client : [Msg=%s],[RTT=%d ms][RTT=%d us]\n", buf, timeofms, timeofus);
		printf("\n");
		if ((++i) == LOOPLIMIT)     /* LOOPLIMIT reached */
			break;  /* make sure i within integrer limit */

		while ((kbhit()) && (!stop)) {
			cmd = getch();
			fflush(stdout);
			if (cmd == QUITKEY) {
				/*待补充退出的三次握手*/
				stop = true;
				//recv(acptdsock, buffer, BUFLEN - 1, 0);
				//printf("    Replied from Client : [Msg=%s]]\n", buffer);
				//send(acptdsock, request, strlen(ok), 0);
				//printf("Terminating by kbd cmd 0x%x...\n", cmd);
				break;
			}
		}
		if (stop)
			break;


		Sleep(PERIOD); /* PERIOD in milliseconds */
		
	}
	if (SOCKET_ERROR == send(sockClnt, &cmd, 1, 0))
	{
		err("send");
	}
	printf("Exit: [Request =    %s]\n", cmd);


	if ((send(sockClnt, &cmd, 1, 0)) == SOCKET_ERROR) {
		printf("send() failed: \n", WSAGetLastError());
		closesocket(sockSer);
		WSACleanup();
		exit(SOCKET_ERROR);
	}

	/* Step 7: Close socket, in pair with socket() */
	Sleep(2000); /* Allow client to recv last msg without WSAECONNREST err*/
	if ((closesocket(sockSer)) == SOCKET_ERROR) {
		printf("closesocket() failed: %d\n", WSAGetLastError());
		exit(SOCKET_ERROR);
	}


	closesocket(sockSer);
	closesocket(sockClnt);
	printf("....Server returned!\n\n");

	close_Socket();
	

	return 0;

}