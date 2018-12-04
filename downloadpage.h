/*!
 * \class web
 * \file downloadpage.h
 * \brief Implements retrieval of webpage data
 * \authors Steve Silber
 * \date 2018-11
 */

#pragma once

#include <string>
#include <mutex>
#include <thread>
#include <functional>

#include <QEventLoop>
#include <Qtimer>
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#pragma comment(lib,"ws2_32.lib")

#define HTTP_BUFFER_MEDIUM 1 << 16
#define HTTP_BUFFER_CONTENT 1 << 28
#define SCAN_BUFFER 1 << 10

namespace web
{
	/**
	 * given the url of a webpage, it will download the plaintext http contents using
	 * either linux or windows utilities (based on the compilation system),
	 * since this waits for http reply, this function is blocking.
	 * @param contents A string into which to download the webpage
	 * @param url The web location address of the webpage
	 */
	bool get_page(char *contents, char *hostname, char *url);

	/**
	 * Given the url of a webpage, it will download the plaintext http contents using
	 * either linux or windows utilities (based on the compilation system),
	 * since this waits for http reply, this function is blocking.
	 * This uses the Qt library to get the webpage.
	 * @param contents A string into which to download the webpage
	 * @param url The web location address of the webpage
	 */
	bool get_page_qt(char *contents, char *url);
}
