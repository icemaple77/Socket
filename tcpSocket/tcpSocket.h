#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
#include<WinSock2.h>    //Head file for network on windows platform
#include <windows.h>    /* winsock2.h has included windows.h */
#include <time.h>
#include<stdbool.h>
#include "stdio.h"
#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib") //library file

#define key true
#define SERVER_IP_ADDR "127.0.0.1" 
#define PORT 8888 //[0,65535] 0~1024 public port 
#define BUF_length BUFSIZ
#define QUITKEY 0x1b
#define PERIOD 3456  /* in milliseconds */
#define LOOPLIMIT 30  /* loop testing send()/recv() */


#define clear(buf) memset(buf, 0, BUF_length);
#define err(errMsg) printf("[line:%d]%s Failure code %d!!\n",__LINE__,errMsg,WSAGetLastError())


//Open net library
bool init_Socket();
//close net library
bool close_Socket();

//Create server socket
SOCKET createSocketServer();

//Create Client socket
SOCKET createSocketClient(const char *ipaddr);

#include < time.h >
#include < windows.h >

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
    #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
    #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif





#endif // !_TCPSOCKET_H_
