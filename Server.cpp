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

//// !!! CLIENT SIDE: https://gist.github.com/sunmeat/068b8df3d7da02e6548ed53491989443
//
//#define WIN32_LEAN_AND_MEAN // для пришвидшення процесу компіляції: https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly
//
//#include <iostream>
//#include <windows.h>
//#include <ws2tcpip.h> // тип WSADATA; функції WSAStartup, WSACleanup та багато інших
//using namespace std;
//
//#pragma comment (lib, "Ws2_32.lib")
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015" // порт — це логічна конструкція, що ідентифікує конкретний процес або тип мережевої служби - https://en.wikipedia.org/wiki/Port_(computer_networking)
//
//#define PAUSE 1
//
//// прийом клієнтського сокета
//SOCKET ClientSocket = INVALID_SOCKET;
//
//DWORD WINAPI Sender(void* param)
//{
//	while (true) {
//		// надаємо відповідь відправнику
//		char* answer = new char[200];
//		cout << "Будь ласка, введіть повідомлення для клієнта: ";
//		cin.getline(answer, 199);
//
//		cout << "процес сервера відправляє відповідь: " << answer << "\n";
//
//		int iSendResult = send(ClientSocket, answer, strlen(answer), 0); // функція send відправляє дані по з'єднаному сокету: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send
//
//		Sleep(PAUSE);
//
//		//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		if (iSendResult == SOCKET_ERROR) {
//			cout << "відправка не вдалася з помилкою: " << WSAGetLastError() << "\n";
//			cout << "упс, відправка (send) відповідного повідомлення не відбулася ((\n";
//			closesocket(ClientSocket);
//			WSACleanup();
//			return 7;
//		}
//		else {
//			//cout << "байтів відправлено: " << iSendResult << "\n";
//			Sleep(PAUSE);
//		}
//	}
//
//	return 0;
//}
//
//DWORD WINAPI Receiver(void* param)
//{
//	while (true) {
//		char message[DEFAULT_BUFLEN];
//
//		int iResult = recv(ClientSocket, message, DEFAULT_BUFLEN, 0); // функція recv використовується для читання вхідних даних: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
//		message[iResult] = '\0';
//
//		if (iResult > 0) {
//			cout << "\nпроцес клієнта надіслав повідомлення: " << message << "\n";
//			Sleep(PAUSE);
//			//cout << "байтів отримано: " << iResult << "\n";
//			Sleep(PAUSE);
//		}
//	}
//	return 0;
//}
//
//int main()
//{
//	SetConsoleOutputCP(1251);
//	system("title SERVER SIDE");
//	// cout << "процес сервера запущено!\n";
//	Sleep(PAUSE);
//
//	///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// ініціалізація Winsock
//	WSADATA wsaData; // структура WSADATA містить інформацію про реалізацію Windows Sockets: https://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata
//	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); // функція WSAStartup ініціалізує використання DLL Winsock процесом: https://firststeps.ru/mfc/net/socket/r.php?2
//	if (iResult != 0) {
//		cout << "WSAStartup не вдалося з помилкою: " << iResult << "\n";
//		cout << "підключення Winsock.dll пройшло з помилкою!\n";
//		return 1;
//	}
//	else {
//		// cout << "підключення Winsock.dll пройшло успішно!\n";
//		Sleep(PAUSE);
//	}
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	struct addrinfo hints; // структура addrinfo використовується функцією getaddrinfo для зберігання інформації про хост-адресу: https://docs.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_INET; // сімейство адрес Інтернет-протоколу версії 4 (IPv4)
//	hints.ai_socktype = SOCK_STREAM; // забезпечує послідовні, надійні, двосторонні потоки з'єднань з механізмом передачі даних
//	hints.ai_protocol = IPPROTO_TCP; // протокол TCP (Transmission Control Protocol). Це можливе значення, коли член ai_family є AF_INET або AF_INET6 і член ai_socktype є SOCK_STREAM
//	hints.ai_flags = AI_PASSIVE; // адреса сокета буде використовуватися в виклику функції "bind"
//
//	// отримання адреси та порту сервера
//	struct addrinfo* result = NULL;
//	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		cout << "getaddrinfo не вдалося з помилкою: " << iResult << "\n";
//		cout << "отримання адреси та порту сервера пройшло з помилкою!\n";
//		WSACleanup(); // функція WSACleanup завершує використання DLL Winsock 2 (Ws2_32.dll): https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup
//		return 2;
//	}
//	else {
//		// cout << "отримання адреси та порту сервера пройшло успішно!\n";
//		Sleep(PAUSE);
//	}
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// створення SOCKET для підключення до сервера
//	SOCKET ListenSocket = INVALID_SOCKET;
//	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//	if (ListenSocket == INVALID_SOCKET) {
//		cout << "socket не вдалося створити з помилкою: " << WSAGetLastError() << "\n";
//		cout << "створення сокета пройшло з помилкою!\n";
//		freeaddrinfo(result);
//		WSACleanup();
//
//		return 3;
//	}
//	else {
//		// cout << "створення сокета на сервері пройшло успішно!\n";
//		Sleep(PAUSE);
//	}
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// налаштування сокета для прослуховування
//	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen); // функція bind асоціює локальну адресу з сокетом: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind
//	if (iResult == SOCKET_ERROR) {
//		cout << "bind не вдалося з помилкою: " << WSAGetLastError() << "\n";
//		cout << "внедрення сокета за IP-адресою пройшло з помилкою!\n";
//		freeaddrinfo(result);
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 4;
//	}
//	else {
//		// cout << "внедрення сокета за IP-адресою пройшло успішно!\n";
//		Sleep(PAUSE);
//	}
//
//	freeaddrinfo(result);
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	iResult = listen(ListenSocket, SOMAXCONN); // функція listen поміщає сокет у стан прослуховування для вхідного з'єднання: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
//	if (iResult == SOCKET_ERROR) {
//		cout << "listen не вдалося з помилкою: " << WSAGetLastError() << "\n";
//		cout << "прослуховування від клієнта не почалося. щось пішло не так!\n";
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 5;
//	}
//	else {
//		cout << "будь ласка, запустіть client.exe\n";
//		// тут можна було б запустити якийсь прелоадер в окремому потоці
//	}
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ClientSocket = accept(ListenSocket, NULL, NULL); // функція accept дозволяє підключити вхідне з'єднання до сокета: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
//	if (ClientSocket == INVALID_SOCKET) {
//		cout << "accept не вдалося з помилкою: " << WSAGetLastError() << "\n";
//		cout << "з'єднання з клієнтським додатком не встановлено! сумно!\n";
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 6;
//	}
//	else {
//		// cout << "з'єднання з клієнтським додатком встановлено успішно!\n";
//	}
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// більше не потрібен серверний сокет
//	// closesocket(ListenSocket);
//
//	CreateThread(0, 0, Receiver, 0, 0, 0);
//
//	CreateThread(0, 0, Sender, 0, 0, 0);
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// завершення з'єднання, оскільки робота завершена
//	/*
//	iResult = shutdown(ClientSocket, SD_SEND); // функція shutdown вимикає відправку або отримання на сокеті: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-shutdown
//	if (iResult == SOCKET_ERROR) {
//		cout << "shutdown не вдалося з помилкою: " << WSAGetLastError() << "\n";
//		cout << "упс, розрив з'єднання (shutdown) видав помилку ((\n";
//		closesocket(ClientSocket);
//		WSACleanup();
//		return 9;
//	}
//	else {
//		cout << "процес сервера припиняє свою роботу! до нових запусків! :)\n";
//	} */
//
//	// очищення
//	//closesocket(ClientSocket);
//	//WSACleanup();
//
//	Sleep(INFINITE);
//}


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <string>
#include <vector>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

struct User {
    string login;
    string password;
};

vector<User> users;

void loadUsers() {
    ifstream in("users.txt");
    string login, password;
    while (in >> login >> password) {
        users.push_back({ login, password });
    }
    in.close();
}

void saveUsers() {
    ofstream out("users.txt");
    for (const auto& user : users) {
        out << user.login << " " << user.password << endl;
    }
    out.close();
}

bool checkUser(const string& login, const string& password) {
    for (const auto& user : users) {
        if (user.login == login && user.password == password) {
            return true;
        }
    }
    return false;
}

bool registerUser(const string& login, const string& password) {
    for (const auto& user : users) {
        if (user.login == login) return false;
    }
    users.push_back({ login, password });
    saveUsers(); // сохраняем сразу после регистрации
    return true;
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    loadUsers(); // загружаем пользователей из файла при старте

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);
    cout << "Server started and listening...\n";

    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) continue;

        char buffer[1024] = {};
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            closesocket(clientSocket);
            continue;
        }

        buffer[bytesReceived] = '\0';
        string request(buffer);
        string command = request.substr(0, request.find(' '));
        string data = request.substr(request.find(' ') + 1);

        string login = data.substr(0, data.find(' '));
        string password = data.substr(data.find(' ') + 1);

        string response;
        if (command == "REGISTER") {
            if (registerUser(login, password))
                response = "Registration successful!";
            else
                response = "User with this login already exists!";
        }
        else if (command == "LOGIN") {
            if (checkUser(login, password))
                response = "Login successful!";
            else
                response = "Incorrect login or password!";
        }
        else {
            response = "Unknown command!";
        }

        send(clientSocket, response.c_str(), response.length(), 0);
        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

//#include <iostream>
//#include <winsock2.h>
//using namespace std;
//
//#pragma comment(lib,"ws2_32.lib") // библиотека winsock
//#pragma warning(disable:4996) 
//
//#define BUFLEN 512 // размер буфера
//#define PORT 8888 // порт сервера
//
//class UDPServer {
//public:
//    UDPServer() {
//        // инициализация winsock
//        cout << "инициализация winsock...\n";
//        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//            cout << "ошибка инициализации: " << WSAGetLastError() << "\n";
//            exit(0);
//        }
//        cout << "инициализация завершена.\n";
//
//        // создание сокета
//        if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
//            cout << "не удалось создать сокет: " << WSAGetLastError() << "\n";
//            exit(EXIT_FAILURE);
//        }
//        cout << "сокет создан.\n";
//
//        // настройка структуры sockaddr_in
//        server.sin_family = AF_INET;
//        server.sin_addr.s_addr = INADDR_ANY;
//        server.sin_port = htons(PORT);
//
//        // привязка сокета
//        if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
//            cout << "ошибка привязки: " << WSAGetLastError() << "\n";
//            exit(EXIT_FAILURE);
//        }
//        cout << "привязка выполнена.\n";
//    }
//
//    ~UDPServer() {
//        closesocket(server_socket);
//        WSACleanup();
//    }
//
//    void start() {
//        while (!exitRequested) {
//            cout << "ожидайте данные от клиента...\n";
//            char message[BUFLEN] = {};
//
//            // получение данных (блокирующий вызов)
//            int message_len;
//            int slen = sizeof(sockaddr_in);
//            if ((message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen)) == SOCKET_ERROR) {
//                cout << "ошибка recvfrom(): " << WSAGetLastError() << "\n";
//                exit(0);
//            }
//
//            // вывод информации о клиенте и полученных данных
//            cout << "получен пакет от " << inet_ntoa(client.sin_addr) << " " << ntohs(client.sin_port) << "\n";
//            cout << "данные: " << message << "\n";
//
//            cout << "введите ответ (exit для выхода): ";
//            cin.getline(message, BUFLEN);
//
//            // отправка ответа клиенту
//            if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
//                cout << "ошибка sendto(): " << WSAGetLastError() << "\n";
//                exit(EXIT_FAILURE);
//            }
//
//            if (strcmp(message, "exit") == 0) {
//                cout << "завершение работы сервера...\n";
//                exitRequested = true;
//                break;
//            }
//        }
//    }
//
//private:
//    WSADATA wsa{};
//    SOCKET server_socket = 0;
//    sockaddr_in server{}, client{};
//    bool exitRequested = false;
//};
//
//int main() {
//    system("title UDP SERVER SIDE");
//    setlocale(0, "");
//
//    UDPServer udpServer;
//    udpServer.start();
//}

//#include <winsock2.h>
//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
//
//#define MAX_CLIENTS 10
//#define DEFAULT_BUFLEN 4096
//
//#pragma comment(lib, "ws2_32.lib") // Winsock library
//#pragma warning(disable:4996)
//
//SOCKET server_socket;
//
//vector<string> history;
//vector<string> client_names(MAX_CLIENTS, "Unknown");
//
//int main() {
//	system("title Server");
//
//	puts("Start server... DONE.");
//	WSADATA wsa;
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//		printf("Failed. Error Code: %d", WSAGetLastError());
//		return 1;
//	}
//
//	// create a socket
//	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
//		printf("Could not create socket: %d", WSAGetLastError());
//		return 2;
//	}
//	// puts("Create socket... DONE.");
//
//	// prepare the sockaddr_in structure
//	sockaddr_in server;
//	server.sin_family = AF_INET;
//	server.sin_addr.s_addr = INADDR_ANY;
//	server.sin_port = htons(8888);
//
//	// bind socket
//	if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
//		printf("Bind failed with error code: %d", WSAGetLastError());
//		return 3;
//	}
//
//	// puts("Bind socket... DONE.");
//
//	// listen to incoming connections
//	listen(server_socket, MAX_CLIENTS);
//
//	// accept and incoming connection
//	puts("Server is waiting for incoming connections...\nPlease, start one or more client-side app.");
//
//	// size of our receive buffer, this is string length
//	// set of socket descriptors
//	// fd means "file descriptors"
//	fd_set readfds; // https://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-fd_set
//	SOCKET client_socket[MAX_CLIENTS] = {};
//
//	while (true) {
//		// clear the socket fdset
//		FD_ZERO(&readfds);
//
//		// add master socket to fdset
//		FD_SET(server_socket, &readfds);
//
//		// add child sockets to fdset
//		for (int i = 0; i < MAX_CLIENTS; i++) {
//			SOCKET s = client_socket[i];
//			if (s > 0) {
//				FD_SET(s, &readfds);
//			}
//		}
//
//		// wait for an activity on any of the sockets, timeout is NULL, so wait indefinitely
//		if (select(0, &readfds, NULL, NULL, NULL) == SOCKET_ERROR) {
//			printf("select function call failed with error code : %d", WSAGetLastError());
//			return 4;
//		}
//
//		// if something happened on the master socket, then its an incoming connection
//		SOCKET new_socket; // new client socket
//		sockaddr_in address;
//		int addrlen = sizeof(sockaddr_in);
//		if (FD_ISSET(server_socket, &readfds)) {
//			if ((new_socket = accept(server_socket, (sockaddr*)&address, &addrlen)) < 0) {
//				perror("accept function error");
//				return 5;
//			}
//
//			for (int i = 0; i < history.size(); i++)
//			{
//				cout << history[i] << "\n";
//				send(new_socket, history[i].c_str(), history[i].size(), 0);
//			}
//
//			// inform server side of socket number - used in send and recv commands
//			//printf("New connection, socket fd is %d, ip is: %s, port: %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
//
//			// add new socket to array of sockets
//			for (int i = 0; i < MAX_CLIENTS; i++) {
//				if (client_socket[i] == 0) {
//					client_socket[i] = new_socket;
//					printf("Adding to list of sockets at index %d\n", i);
//					break;
//				}
//			}
//		}
//
//		// if some of client sockets sends something
//		for (int i = 0; i < MAX_CLIENTS; i++)
//		{
//			SOCKET s = client_socket[i];
//			// if client presend in read sockets
//			if (FD_ISSET(s, &readfds))
//			{
//				// get details of the client
//				getpeername(s, (sockaddr*)&address, (int*)&addrlen);
//
//				// check if it was for closing, and also read the incoming message
//				// recv does not place a null terminator at the end of the string (whilst printf %s assumes there is one)
//
//				char client_message[DEFAULT_BUFLEN];
//
//				int client_message_length = recv(s, client_message, DEFAULT_BUFLEN, 0);
//				client_message[client_message_length] = '\0';
//
//				string message = client_message;
//
//				// Якщо нікнейм ще не збережено — це перше повідомлення
//				if (client_names[i] == "Unknown") {
//					client_names[i] = message; // зберігаємо нік
//					string joinMsg = client_names[i] + " joined the chat";
//
//					cout << joinMsg << endl;
//					history.push_back(joinMsg);
//
//					for (int j = 0; j < MAX_CLIENTS; j++) {
//						if (client_socket[j] != 0)
//							send(client_socket[j], joinMsg.c_str(), joinMsg.size(), 0);
//					}
//					continue; // не обробляємо як звичайне повідомлення
//				}
//
//				if (message == "off") {
//					string leftMsg = client_names[i] + " left the chat";
//					cout << leftMsg << endl;
//					history.push_back(leftMsg);
//
//					for (int j = 0; j < MAX_CLIENTS; j++) {
//						if (client_socket[j] != 0)
//							send(client_socket[j], leftMsg.c_str(), leftMsg.size(), 0);
//					}
//					closesocket(client_socket[i]);
//					client_socket[i] = 0;
//					client_names[i] = "Unknown";
//					continue;
//				}
//
//				// Додати нікнейм до повідомлення
//				string finalMsg = client_names[i] + ": " + message;
//				history.push_back(finalMsg);
//				cout << finalMsg << endl;
//
//				for (int j = 0; j < MAX_CLIENTS; j++) {
//					if (client_socket[j] != 0)
//						send(client_socket[j], finalMsg.c_str(), finalMsg.size(), 0);
//				}
//
//			}
//		}
//	}
//
//	WSACleanup();
//}