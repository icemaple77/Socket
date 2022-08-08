#include"tcpSocket.h"


bool init_Socket()
{
	//wsa => windows socket async 
	//parameter 1 apply the socket version, parameter 2 out parameter
	WSADATA wsadata;
	int nErr = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (nErr != 0)//if 0 means that the function can be ran successfully.
	{
		err("WSAStartup");
	}
	return false;
}
bool close_Socket()
{
	int nnErr = WSACleanup();
	if (nnErr != 0)
	{
		err("WSACleanup");
	}
	return false;
	
}

SOCKET createSocketServer(ipaddr,port)
{
	//1.create blank socket // like a new phone
	//parm1: af IP address family
	//parm2: type the type of potocal: stream:tcp|| dgram:udp
	//parm3:protocal often use "0"
	SOCKET fd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)//failure
	{
		err("socket");
		return INVALID_SOCKET;
	}
	
	//2. bind the Ip address and a port;like buying a sim card;
	

	struct sockaddr_in addr;
	addr.sin_family = AF_INET; //same as the parm of socket
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = ipaddr;//ADDR_ANY; //or inet_addr("127.0.0.1");


	if (bind(fd, &addr, sizeof(addr)) == SOCKET_ERROR)
	{
		err("bind");
		return false;
	}

	//3,Listen //like waiting a call;
	listen(fd, 10);
	return fd;
}

SOCKET createSocketClient(ipaddr,port)
{
	//1.create blank socket // like a new phone
	//parm1: af IP address family
	//parm2: type the type of potocal: stream:tcp|| dgram:udp
	//parm3:protocal often use "0"
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)//failure
	{
		err("socket");
		return INVALID_SOCKET;
	}

	//2. bind the Ip address and a port;like buying a sim card;


	struct sockaddr_in addr;
	addr.sin_family = AF_INET; //same as the parm of socket
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ipaddr);

	printf("\nConnecting to Server....\n");
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		err("Connect");
		return false;

	}



	return fd;
}

struct timezone
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval* tv, struct timezone* tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag = 0;

	if (NULL != tv)
	{
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		tmpres /= 10;  /*convert into microseconds*/
		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tv->tv_sec = (int)(tmpres / 1000000UL);
		tv->tv_usec = (int)(tmpres % 1000000UL);
	}

	if (NULL != tz)
	{
		if (!tzflag)
		{
			_tzset();
			tzflag++;
		}
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime = _daylight;
	}

	return 0;
}



