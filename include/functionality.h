#pragma once

#include <string>
#include <tuple>

class Functionality
{
public:
	static std::tuple<std::wstring, std::wstring> input();
	static void notify(const std::wstring& message, const int& code = 0);
	static std::wstring s2ws(const std::string& str);
	static std::string ws2s(const std::wstring& wstr);
	
	template<typename ... Args>
	static std::string string_format(const std::string& format, Args ... args);

protected:
	explicit Functionality() = default;
};

template<typename ...Args>
inline std::string Functionality::string_format(const std::string& format, Args ...args)
{
	// Получаем размер
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;

	if (size <= 0)
	{
		throw std::runtime_error("Error during formatting.");
	}

	// Умный указатель
	std::unique_ptr<char[]> buf(new char[size]);

	// Подставляем подстроки в строку
	snprintf(buf.get(), size, format.c_str(), args ...);

	// Возврвщаем новую строку
	return std::string(buf.get(), buf.get() + size - 1);
}
