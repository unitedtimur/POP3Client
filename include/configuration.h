#pragma once

#include <string>

namespace configuration
{
	static const std::wstring COPYRIGHT = L"POP3Client\nCopyright (c) 2020 by UnitedTimur\nAll rights reserved.\n";
	
	namespace default
	{
		static const std::wstring HOST = L"127.0.0.1";
		static const std::wstring PORT = L"9090";
		static const int BUFFER_SIZE = 1024;
	}

	namespace functionality
	{
		static const std::wstring HOSTNAME = L"Input hostname: ";
		static const std::wstring PORT = L"Input port: ";
	}

	namespace error
	{
		static const std::wstring WSASTARTUP = L"Error -> WSAStartup failed!";
		static const std::wstring GETADDRINFO = L"Error -> getaddrinfo failed!";
		static const std::wstring SOCKET = L"Error -> failed to create socket!";
		static const std::wstring HOST = L"Error -> inet_pton failed!";
		static const std::wstring CONNECT = L"Error -> connect failed!";
		static const std::wstring SERVER_RESPONSE_TIMEOUT = L"Error -> Server response timeout!";
	}

	namespace status
	{
		static const std::wstring START = L"Client has been started successfully on host %s and port %s...";
		static const std::wstring FINISH = L"Client has been finished work!";
		static const std::wstring INPUT = L"Input command -> ";
	}
}