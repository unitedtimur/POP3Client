#include "../include/functionality.h"
#include "../include/configuration.h"
#include <iostream>
#include <codecvt>
#include <Windows.h>

std::tuple<std::wstring, std::wstring> Functionality::input()
{
	std::wstring host;
	std::wstring port;

	// Просим ввести hostname
	std::wcout << configuration::functionality::HOSTNAME << " ";
	std::wcin >> host;

	// Просим ввести port
	std::wcout << configuration::functionality::PORT << " ";
	std::wcin >> port;

	std::wcout << std::endl;

	// Формируем кортеж из хоста и порта
	return std::make_tuple(host, port);
}

void Functionality::notify(const std::wstring& message, const int& code)
{
	// Получаем handler консоли
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Выставляем цвет в зависимости от кода
	switch (code)
	{
	case 1:
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		break;

	case 2:
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		break;
	}
	// Выводим в консоль сообщение
	std::wcout << message << std::endl;

	// Возвращаем по умолчанию
	SetConsoleTextAttribute(hStdOut,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

std::wstring Functionality::s2ws(const std::string& str)
{
	// Конвертируем из std::string в std::wstring
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string Functionality::ws2s(const std::wstring& wstr)
{
	// Конвертируем из std::wstring в std::string
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}