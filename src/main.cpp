#include <iostream>
#include "../include/configuration.h"
#include "../include/functionality.h"
#include "../include/client.h"

// Если под windows
#ifdef WIN32

    #include <io.h>
    #include <fcntl.h>

// Выставляем работу с любыми символами
void setConsoleMode()
{
    if (_setmode(_fileno(stdout), _O_U16TEXT) == -1 ||
        _setmode(_fileno(stdin), _O_U16TEXT) == -1 ||
        _setmode(_fileno(stderr), _O_U16TEXT) == -1)
    {
        std::wcout << "Cannot to setConsoleMode!" << std::endl;
    }
}

#endif // WIN32

int main(int argc, char** argv)
{
#ifdef WIN32

    setConsoleMode();

#endif // WIN32

    std::wcout << configuration::COPYRIGHT << std::endl;

    std::wstring host;
    std::wstring port;

    // Разбиваем полученный кортеж
    std::tie(host, port) = Functionality::input();

    // Вызываем объект и инициализируем его
    Client::instance(host, port).initialize();

    system("pause");

    return 0;
}