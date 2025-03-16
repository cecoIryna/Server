//#define WIN32_LEAN_AND_MEAN
//#include <iostream>
//#include <windows.h>
//#include <ws2tcpip.h>
//using namespace std;
//
//#pragma comment (lib, "Ws2_32.lib")
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015"
//#define PAUSE 0
//
//int main()
//{
//    setlocale(0, "Ukrainian");
//    system("title SERVER SIDE");
//
//    WSADATA wsaData;
//    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//    if (iResult != 0) return 1;
//
//    struct addrinfo hints {};
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    hints.ai_flags = AI_PASSIVE;
//
//    struct addrinfo* result = NULL;
//    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//    if (iResult != 0) {
//        WSACleanup();
//        return 2;
//    }
//
//    SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//    if (ListenSocket == -1) {
//        freeaddrinfo(result);
//        WSACleanup();
//        return 3;
//    }
//
//    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//    if (iResult == -1) {
//        freeaddrinfo(result);
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 4;
//    }
//
//    freeaddrinfo(result);
//
//    iResult = listen(ListenSocket, SOMAXCONN);
//    if (iResult == -1) {
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 5;
//    }
//    else {
//        cout << "починається прослуховування iнформацiї вiд клiєнта. будь ласка, запустiть клiєнтську програму! (client.exe)\n";
//    }
//
//    SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
//    if (ClientSocket == INVALID_SOCKET) {
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 6;
//    }
//
//    closesocket(ListenSocket);
//
//    char message[DEFAULT_BUFLEN];
//    char response[DEFAULT_BUFLEN];
//
//    /*while (true) {
//        ZeroMemory(message, DEFAULT_BUFLEN);
//        iResult = recv(ClientSocket, message, DEFAULT_BUFLEN, 0);
//
//        if (iResult > 0) {
//            message[iResult] = '\0';
//            cout << "Клієнт: " << message << "\n";
//
//            if (strcmp(message, "how are you doing") == 0) {
//                strcpy_s(response, "nice");
//            }
//            else if (strcmp(message, "your name") == 0) {
//                strcpy_s(response, "server");
//            }
//            else if (strcmp(message, "goodbye") == 0) {
//                cout << "Клієнт завершив роботу.\n";
//                break;
//            }
//            else {
//                strcpy_s(response, "Не зрозумів запит.");
//            }
//
//            send(ClientSocket, response, (int)strlen(response), 0);
//        }
//        else {
//            cout << "Помилка або розрив з'єднання.\n";
//            break;
//        }
//    }*/
//
//    while (true) {
//        ZeroMemory(message, DEFAULT_BUFLEN);
//        iResult = recv(ClientSocket, message, DEFAULT_BUFLEN, 0);
//
//        if (iResult > 0) {
//            message[iResult] = '\0';
//            cout << "Клієнт надіслав: " << message << "\n";
//
//            if (strcmp(message, "exit") == 0) {
//                cout << "Клієнт завершив роботу.\n";
//                break;
//            }
//
//       
//            int num = atoi(message);
//            num++; 
//
//            _itoa_s(num, response, 10);
//            send(ClientSocket, response, (int)strlen(response), 0);
//        }
//        else {
//            cout << "Помилка або розрив з'єднання.\n";
//            break;
//        }
//    }
//
//
//    closesocket(ClientSocket);
//    WSACleanup();
//    return 0;
//}

// !!! CLIENT SIDE: https://gist.github.com/sunmeat/068b8df3d7da02e6548ed53491989443

#define WIN32_LEAN_AND_MEAN // для пришвидшення процесу компіляції: https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly

#include <iostream>
#include <windows.h>
#include <ws2tcpip.h> // тип WSADATA; функції WSAStartup, WSACleanup та багато інших
using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015" // порт — це логічна конструкція, що ідентифікує конкретний процес або тип мережевої служби - https://en.wikipedia.org/wiki/Port_(computer_networking)

#define PAUSE 1

// прийом клієнтського сокета
SOCKET ClientSocket = INVALID_SOCKET;

DWORD WINAPI Sender(void* param)
{
	while (true) {
		// надаємо відповідь відправнику
		char* answer = new char[200];
		cout << "Будь ласка, введіть повідомлення для клієнта: ";
		cin.getline(answer, 199);

		cout << "процес сервера відправляє відповідь: " << answer << "\n";

		int iSendResult = send(ClientSocket, answer, strlen(answer), 0); // функція send відправляє дані по з'єднаному сокету: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send

		Sleep(PAUSE);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (iSendResult == SOCKET_ERROR) {
			cout << "відправка не вдалася з помилкою: " << WSAGetLastError() << "\n";
			cout << "упс, відправка (send) відповідного повідомлення не відбулася ((\n";
			closesocket(ClientSocket);
			WSACleanup();
			return 7;
		}
		else {
			//cout << "байтів відправлено: " << iSendResult << "\n";
			Sleep(PAUSE);
		}
	}

	return 0;
}

DWORD WINAPI Receiver(void* param)
{
	while (true) {
		char message[DEFAULT_BUFLEN];

		int iResult = recv(ClientSocket, message, DEFAULT_BUFLEN, 0); // функція recv використовується для читання вхідних даних: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
		message[iResult] = '\0';

		if (iResult > 0) {
			cout << "\nпроцес клієнта надіслав повідомлення: " << message << "\n";
			Sleep(PAUSE);
			//cout << "байтів отримано: " << iResult << "\n";
			Sleep(PAUSE);
		}
	}
	return 0;
}

int main()
{
	SetConsoleOutputCP(1251);
	system("title SERVER SIDE");
	// cout << "процес сервера запущено!\n";
	Sleep(PAUSE);

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	// ініціалізація Winsock
	WSADATA wsaData; // структура WSADATA містить інформацію про реалізацію Windows Sockets: https://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); // функція WSAStartup ініціалізує використання DLL Winsock процесом: https://firststeps.ru/mfc/net/socket/r.php?2
	if (iResult != 0) {
		cout << "WSAStartup не вдалося з помилкою: " << iResult << "\n";
		cout << "підключення Winsock.dll пройшло з помилкою!\n";
		return 1;
	}
	else {
		// cout << "підключення Winsock.dll пройшло успішно!\n";
		Sleep(PAUSE);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct addrinfo hints; // структура addrinfo використовується функцією getaddrinfo для зберігання інформації про хост-адресу: https://docs.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // сімейство адрес Інтернет-протоколу версії 4 (IPv4)
	hints.ai_socktype = SOCK_STREAM; // забезпечує послідовні, надійні, двосторонні потоки з'єднань з механізмом передачі даних
	hints.ai_protocol = IPPROTO_TCP; // протокол TCP (Transmission Control Protocol). Це можливе значення, коли член ai_family є AF_INET або AF_INET6 і член ai_socktype є SOCK_STREAM
	hints.ai_flags = AI_PASSIVE; // адреса сокета буде використовуватися в виклику функції "bind"

	// отримання адреси та порту сервера
	struct addrinfo* result = NULL;
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout << "getaddrinfo не вдалося з помилкою: " << iResult << "\n";
		cout << "отримання адреси та порту сервера пройшло з помилкою!\n";
		WSACleanup(); // функція WSACleanup завершує використання DLL Winsock 2 (Ws2_32.dll): https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup
		return 2;
	}
	else {
		// cout << "отримання адреси та порту сервера пройшло успішно!\n";
		Sleep(PAUSE);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// створення SOCKET для підключення до сервера
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		cout << "socket не вдалося створити з помилкою: " << WSAGetLastError() << "\n";
		cout << "створення сокета пройшло з помилкою!\n";
		freeaddrinfo(result);
		WSACleanup();

		return 3;
	}
	else {
		// cout << "створення сокета на сервері пройшло успішно!\n";
		Sleep(PAUSE);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// налаштування сокета для прослуховування
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen); // функція bind асоціює локальну адресу з сокетом: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind
	if (iResult == SOCKET_ERROR) {
		cout << "bind не вдалося з помилкою: " << WSAGetLastError() << "\n";
		cout << "внедрення сокета за IP-адресою пройшло з помилкою!\n";
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 4;
	}
	else {
		// cout << "внедрення сокета за IP-адресою пройшло успішно!\n";
		Sleep(PAUSE);
	}

	freeaddrinfo(result);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	iResult = listen(ListenSocket, SOMAXCONN); // функція listen поміщає сокет у стан прослуховування для вхідного з'єднання: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
	if (iResult == SOCKET_ERROR) {
		cout << "listen не вдалося з помилкою: " << WSAGetLastError() << "\n";
		cout << "прослуховування від клієнта не почалося. щось пішло не так!\n";
		closesocket(ListenSocket);
		WSACleanup();
		return 5;
	}
	else {
		cout << "будь ласка, запустіть client.exe\n";
		// тут можна було б запустити якийсь прелоадер в окремому потоці
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	ClientSocket = accept(ListenSocket, NULL, NULL); // функція accept дозволяє підключити вхідне з'єднання до сокета: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
	if (ClientSocket == INVALID_SOCKET) {
		cout << "accept не вдалося з помилкою: " << WSAGetLastError() << "\n";
		cout << "з'єднання з клієнтським додатком не встановлено! сумно!\n";
		closesocket(ListenSocket);
		WSACleanup();
		return 6;
	}
	else {
		// cout << "з'єднання з клієнтським додатком встановлено успішно!\n";
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// більше не потрібен серверний сокет
	// closesocket(ListenSocket);

	CreateThread(0, 0, Receiver, 0, 0, 0);

	CreateThread(0, 0, Sender, 0, 0, 0);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// завершення з'єднання, оскільки робота завершена
	/*
	iResult = shutdown(ClientSocket, SD_SEND); // функція shutdown вимикає відправку або отримання на сокеті: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-shutdown
	if (iResult == SOCKET_ERROR) {
		cout << "shutdown не вдалося з помилкою: " << WSAGetLastError() << "\n";
		cout << "упс, розрив з'єднання (shutdown) видав помилку ((\n";
		closesocket(ClientSocket);
		WSACleanup();
		return 9;
	}
	else {
		cout << "процес сервера припиняє свою роботу! до нових запусків! :)\n";
	} */

	// очищення
	//closesocket(ClientSocket);
	//WSACleanup();

	Sleep(INFINITE);
}
