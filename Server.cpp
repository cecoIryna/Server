#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define PAUSE 0

int main()
{
    setlocale(0, "Ukrainian");
    system("title SERVER SIDE");

    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) return 1;

    struct addrinfo hints {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo* result = NULL;
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        return 2;
    }

    SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == -1) {
        freeaddrinfo(result);
        WSACleanup();
        return 3;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == -1) {
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 4;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == -1) {
        closesocket(ListenSocket);
        WSACleanup();
        return 5;
    }
    else {
        cout << "починається прослуховування iнформацiї вiд клiєнта. будь ласка, запустiть клiєнтську програму! (client.exe)\n";
    }

    SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        closesocket(ListenSocket);
        WSACleanup();
        return 6;
    }

    closesocket(ListenSocket);

   /* char message[DEFAULT_BUFLEN];
    char response[DEFAULT_BUFLEN];

    while (true) {
        ZeroMemory(message, DEFAULT_BUFLEN);
        iResult = recv(ClientSocket, message, DEFAULT_BUFLEN, 0);

        if (iResult > 0) {
            message[iResult] = '\0';
            cout << "Клієнт: " << message << "\n";

            if (strcmp(message, "how are you doing") == 0) {
                strcpy_s(response, "nice");
            }
            else if (strcmp(message, "your name") == 0) {
                strcpy_s(response, "server");
            }
            else if (strcmp(message, "goodbye") == 0) {
                cout << "Клієнт завершив роботу.\n";
                break;
            }
            else {
                strcpy_s(response, "Не зрозумів запит.");
            }

            send(ClientSocket, response, (int)strlen(response), 0);
        }
        else {
            cout << "Помилка або розрив з'єднання.\n";
            break;
        }
    }*/

    char message[DEFAULT_BUFLEN];
    char response[DEFAULT_BUFLEN];

    while (true) {
        ZeroMemory(message, DEFAULT_BUFLEN);
        iResult = recv(ClientSocket, message, DEFAULT_BUFLEN, 0);

        if (iResult > 0) {
            message[iResult] = '\0';
            cout << "Клієнт надіслав: " << message << "\n";

            if (strcmp(message, "exit") == 0) {
                cout << "Клієнт завершив роботу.\n";
                break;
            }

       
            int num = atoi(message);
            num++; 

            _itoa_s(num, response, 10);
            send(ClientSocket, response, (int)strlen(response), 0);
        }
        else {
            cout << "Помилка або розрив з'єднання.\n";
            break;
        }
    }


    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}
