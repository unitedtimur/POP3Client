#include "../include/socket.h"
#include "../include/configuration.h"
#include "../include/functionality.h"
#include "WS2tcpip.h"

Socket::Socket(const std::wstring& host, const std::wstring& port) :
	host(host),
	port(port),
	clientSocket(-1),
	addr(nullptr)
{
}

Socket::~Socket()
{
	// Закрываем сокет
	closesocket(this->clientSocket);
	// Очищаем информацию и WSACleanup
	freeaddrinfo(addr);
	WSACleanup();
}

bool Socket::start()
{
	// Инициализация WSADATA
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);

	// Производим инициализацию
	if (WSAStartup(version, &wsaData) != 0)
	{
		Functionality::notify(configuration::error::WSASTARTUP);
		return false;
	}

	addrinfo hints;

	// Производим инициализацию подключения
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Производим инициализацию по полученному хосту и порту
	if (getaddrinfo(Functionality::ws2s(host).c_str(), Functionality::ws2s(port).c_str(), &hints, &addr) != 0)
	{
		Functionality::notify(configuration::error::GETADDRINFO);
		return false;
	}

	// Создаём сокет по полученным данным
	if ((this->clientSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) == INVALID_SOCKET)
	{
		Functionality::notify(configuration::error::SOCKET);
		return false;
	}

	// Данная функция преобразует строку символов addr->ai_addr->sa_data в структуру сетевого адреса сетевого семейства адресов
	if (inet_pton(addr->ai_family, addr->ai_addr->sa_data, (PVOID)(addr->ai_addrlen)) == SOCKET_ERROR)
	{
		Functionality::notify(configuration::error::HOST);
		return false;
	}

	// Производим подключение к сокету сервера
	if (connect(this->clientSocket, addr->ai_addr, int(addr->ai_addrlen)) == SOCKET_ERROR)
	{
		Functionality::notify(configuration::error::CONNECT);
		return false;
	}

	return true;
}

std::wstring Socket::get_port() const
{
	// Возвращаем port
	return port;
}

std::wstring Socket::get_host() const
{
	// Возвращаем hostname
	return host;
}

bool Socket::isReadyRead()
{
	fd_set recieveFd;
	struct timeval timeout;
	int selectReturnValue;

	// Инициализируем нулём ответ сокета сервера
	FD_ZERO(&recieveFd);

	// Выставляем значение для ответа
	FD_SET(this->clientSocket, &recieveFd);

	// Устанавливаем таймаут ответа сервера в виде 10 секунд
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	// Получаем общее количество дескрипторов сокетов
	selectReturnValue = select(this->clientSocket, &recieveFd, 0, 0, &timeout);

	// Если всё ок
	if (selectReturnValue > 0)
	{
		return true;
	}

	return false;
}

bool Socket::sendAll(const std::wstring& message)
{
	// Преобразуем в std::string
	std::string msg = Functionality::ws2s(message);
	msg += '\r\n';

	char* ptr = (char*)(msg.c_str());
	int length = static_cast<int>(msg.length());

	// Отправляем всё до последнего байта
	while (length > 0)
	{
		int i = send(this->clientSocket, ptr, length, 0);

		if (i == SOCKET_ERROR)
			return false;

		ptr += i;
		length -= i;
	}

	return true;
}

bool Socket::recvAll(std::wstring& message)
{
	const int max_buffer_size = configuration::default::BUFFER_SIZE;

	char buffer[max_buffer_size];

	int size_recv;

	// Получаем все отправленные нам байты
	while (true)
	{
		memset(buffer, 0, max_buffer_size);

		if ((size_recv = recv(this->clientSocket, buffer, max_buffer_size, 0) == SOCKET_ERROR))
		{
			return false;
		}
		else
		{
			if (Functionality::ws2s(message)[message.size()] == '\0')
			{
				message += Functionality::s2ws(std::string(buffer));
				return true;
			}
		}
	}

	return true;
}

void Socket::operator<<(const std::wstring& message)
{
	// Отправляем сообщение
	this->sendAll(message);
}

void Socket::operator>>(std::wstring& message)
{
	// Получаем ответ
	this->recvAll(message);
}
