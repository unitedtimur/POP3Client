#pragma once

#include <string>
#include "socket.h"

class Client
{
public:
	static Client& instance(const std::wstring& host, const std::wstring& port);
	~Client() = default;

	void initialize();

protected:
	explicit Client(const std::wstring& host, const std::wstring& port);

	void client_listen();
	void send_command(const std::wstring& command);
	void client_close();
	bool recv_response(std::wstring& response);

protected:
	Socket clientSocket;
};