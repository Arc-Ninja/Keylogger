#include <cstring>
#include <iostream>
#include <winsock2.h>
//#include <wa2tcpip.h>
//#include <netinet/in.h>
//#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(){
	
	//Initialize Winsock
	WSADATA wsaData;
	int iResult=WSAStartup(MAKEWORD(2,2),&wsaData);
	if(iResult!=0){
		cout<<"WSAStartup failed: "<<iResult<<endl;
		return 1;
	}
	
	//creating client socket
	SOCKET clientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(clientSocket==INVALID_SOCKET){
		cout<<"socket failed: "<<WSAGetLastError()<<endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	
	//get the hostname
	const char* hostname="localhost";
	
	//Resolve the hostname to an IP Address
	struct hostent *hostinfo = gethostbyname(hostname);
	if(hostinfo==nullptr){
		cout<<"gethostbyname failed with error: "<<WSAGetLastError()<<endl;
		WSACleanup();
		return 1;
	}
	
	//print the IP Address
	cout<<"The IP Address of "<<hostname<<" is: "<<inet_ntoa(*((struct in_addr *)hostinfo->h_addr_list[0]))<<endl;
	hostname = inet_ntoa(*((struct in_addr *)hostinfo->h_addr_list[0]));
	
	//specfing address
	sockaddr_in clientAdress;
	clientAdress.sin_family = AF_INET;
	clientAdress.sin_port = htons(55555);
	clientAdress.sin_addr.s_addr =inet_addr(hostname);
	
	//sending connection to server
	iResult=connect(clientSocket,(struct sockaddr*)&clientAdress,sizeof(clientAdress));
	if(iResult==SOCKET_ERROR){
		cout<<"connect failed: "<<WSAGetLastError()<<endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	
	//sending data
	const char *msg="Hello, Server";
	iResult=send(clientSocket,msg,strlen(msg),0);
	if(iResult==SOCKET_ERROR){
		cout<<"send failed: "<<WSAGetLastError()<<endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	
	//disconnecting from server
	//closing clientSocket
	closesocket(clientSocket);
	WSACleanup();
	
	return 0;
	
}