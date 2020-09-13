#include "../include/client.h"
#include "../include/functionality.h"
#include "../include/configuration.h"

Client::Client(const std::wstring& host, const std::wstring& port) :
	clientSocket(host, port)
{
}

Client& Client::instance(const std::wstring& host, const std::wstring& port)
{
	// Создаём единственного клиента (синглтон)
	static Client client(host, port);
	return client;
}

void Client::initialize()
{
	// Инициализируем сокет подключения к серверу
	if (this->clientSocket.start())
	{
		// Уведомляем о том, что смогли подключиться 
		Functionality::notify(
			Functionality::s2ws(
				Functionality::string_format(
					Functionality::ws2s(configuration::status::START), 
					Functionality::ws2s(this->clientSocket.get_host()).c_str(),
					Functionality::ws2s(this->clientSocket.get_port()).c_str()
				)
			)
		);

		// Запускаем основную функцию работы с клиентом
		this->client_listen();
	}
	else
	{
		// В случае неудачи, завершаем работу клиента
		this->client_close();
	}
}

void Client::client_listen()
{
	for (;;)
	{
		std::wstring response;

		// Ждём ответа сервера
		if (!this->recv_response(response))
		{
			Functionality::notify(configuration::error::SERVER_RESPONSE_TIMEOUT, 2);
			this->client_close();
			return;
		}

		// Выводим ответ сервера
		Functionality::notify(response, 1);

		std::wstring command;

		// Просим ввести команду 
		std::wcout << configuration::status::INPUT;
		std::wcin >> command;

		// Отправляем команду серверу
		this->send_command(command);
	}
}

void Client::send_command(const std::wstring& command)
{
	// Говорим сокету отправить команду серверу
	this->clientSocket << command + L"\r\n";
}

void Client::client_close()
{
	// Выводим информацию о завершении работы клиента
	Functionality::notify(configuration::status::FINISH);
}

bool Client::recv_response(std::wstring& response)
{
	// Если сокет готов слушать сервер
	if (!this->clientSocket.isReadyRead())
	{
		return false;
	}

	// Говорим сокету получить ответ от сервера
	this->clientSocket >> response;

	return true;
}