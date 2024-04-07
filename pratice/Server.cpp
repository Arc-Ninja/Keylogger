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
	//creating server socket
	SOCKET serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serverSocket==INVALID_SOCKET){
		cout<<"socket failed: "<<WSAGetLastError()<<endl;
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
	
	//specifing address
	sockaddr_in serverAddress;
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port = htons(55555);
	serverAddress.sin_addr.s_addr =inet_addr(hostname);
	
	//binding Socket with ip address
	iResult=bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
	if(iResult!=0){
		cout<<"bind failed: "<<WSAGetLastError()<<endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	//listen to assign socket
	iResult=listen(serverSocket,100);
	if(iResult!=0){
		cout<<"listen failed: "<<WSAGetLastError()<<endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	
	//accepting connection request
	SOCKET clientSocket = accept(serverSocket,nullptr,nullptr);
	if(clientSocket==INVALID_SOCKET){
		cout<<"accept failed: "<<WSAGetLastError()<<endl;
		closesocket(clientSocket);
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	
	//reciving data;
	char b[1024]={0};
	iResult=recv(clientSocket,b,sizeof(b),0);
	if(iResult==SOCKET_ERROR){
		cout<<"recv failed: "<<WSAGetLastError()<<endl;
		closesocket(clientSocket);
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	cout<<"Messaage from client: "<<b<<endl;
	
	//closing serverSocket
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	
	return 0;
}