/*!
 * \class web
 * \file downloadpage.h
 * \brief Implements retrieval of webpage data
 * \authors Steve Silber
 * \date 2018-11
 */



#pragma once

#include <string>

#ifdef WIN32

#include <winsock2.h>
#include <windows.h>

#else

#include <sys/socket.h>
#include <sys/un.h>

#endif


#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#pragma comment(lib,"ws2_32.lib")

#define HTTP_BUFFER_SIZE 1 << 10
#define HTTP_BUFFER_CONTENT 1 << 16

namespace web
{
	/**
	 * given the url of a webpage, it will download the plaintext http contents using
	 * either linux or windows utilities (based on the compilation system),
	 * since this waits for http reply, this function is blocking.
	 * @param contents A string into which to download the webpage
	 * @param url The web location address of the webpage
	 */
	bool get_page(char *contents, char *hostname, char *url)
	{

#ifdef WIN32
		WSADATA wsa_data;
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) 
		{
			printf("WSAStartup failed.\n");
			return false;
		}

		SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		struct hostent *host;

		if ((host = gethostbyname(hostname)) == NULL)
		{
			printf("Could not resolve hostname\n");
			return false;
		}

		/*
		 * attempt a connection to the webpage
		 */
		SOCKADDR_IN soc_addr;
		soc_addr.sin_port = htons(80);
		soc_addr.sin_family = AF_INET;
		soc_addr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

		if (connect(soc, (SOCKADDR*)(&soc_addr), sizeof(soc_addr)) != 0) 
		{
			printf("Could not connect\n");
			return false;
		}
		
		char requestf[] = "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
		size_t requestl = strlen(hostname) + strlen(url) + (strlen(requestf) - 2) + 1;
		
		// form a string to print request message with URL
		char *request = new char[requestl];
		sprintf(request, requestf, url, hostname);
		
		// send the HTTP request
		send(soc, request, requestl, 0);
		delete[] request;

		// buffer the data into contents
		char buffer[HTTP_BUFFER_SIZE];
		size_t p = 0;
		while (recv(soc, buffer, HTTP_BUFFER_SIZE, 0) > 0)
		{
			int i = 0;
			while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') 
			{
				contents[p++] = buffer[i++];
			}
		}
		contents[p] = '\0';

		closesocket(soc);
		WSACleanup();

		return true;
#else

		int sfd;
		if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			printf("unable to connect ipv4 socket");
		}

		// write hostname
		struct hostent *server = gethostbyname(url);

		/*
		 * attempt a connection to the webpage
		 */
		struct sockaddr_in *soc_addr;
		memset(&soc_addr, 0, sizeof(struct sockaddr));
		
		soc_addr.sin_port = htons(80);
		soc_addr.sun_family = AF_INET;
		memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
		
		if (connect(soc, (struct sockaddr *)(&soc_addr), sizeof(struct sockaddr)) == -1)
		{
			printf("Could not connect\n");
			return false;
		}

		char requestf[] = "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
		size_t requestl = strlen(url) + (strlen(requestf) - 2) + 1;

		// form a string to print request message with URL
		char *request = new char[requestl];
		sprintf(request, requestf, url);

		// send the HTTP request
		write(soc, request, requestl);
		delete[] request;

		// buffer the data into contents
		char buffer[HTTP_BUFFER_SIZE];
		size_t p = 0;
		while (read(soc, buffer, HTTP_BUFFER_SIZE) > 0)
		{
			int i = 0;
			while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
			{
				contents[p++] = buffer[i++];
			}
		}
		contents[p] = '\0';
		close(soc);

#endif
	}

	/**
	 * Given the url of a webpage, it will download the plaintext http contents using
	 * either linux or windows utilities (based on the compilation system),
	 * since this waits for http reply, this function is blocking.
	 * This uses the Qt library to get the webpage.
	 * @param contents A string into which to download the webpage
	 * @param url The web location address of the webpage
	 */
	bool get_page_qt(char *contents, char *url)
	{
		QUrl qurl(url);
		if (!qurl.isValid())
		{
			printf("invalid URL");
			return false;
		}

		// submit the request and wait for the reply
		QNetworkRequest request(qurl);
		QNetworkReply *reply = QNetworkAccessManager().get(request);

		// read in the data into a plain html to put into contents
		char *msg_iter = reply->readAll().data();
		size_t p = 0;
		while (*(msg_iter++))
		{
			contents[p++] = *msg_iter;
		}
		contents[p] = '\0';
		return true;
	}
}
