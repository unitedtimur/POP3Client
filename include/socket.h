#pragma once

#include <iostream>
#include <string>

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class Socket
{
public:
	explicit Socket(const std::wstring& host, const std::wstring& port);
	~Socket();

	bool start();

	std::wstring get_host() const;
	std::wstring get_port() const;

	bool isReadyRead();

	void operator<<(const std::wstring& message);
	void operator>>(std::wstring& message);

protected:
	bool sendAll(const std::wstring& message);
	bool recvAll(std::wstring& message);

protected:
	std::wstring host;
	std::wstring port;

	SOCKET clientSocket;
	addrinfo* addr;
};