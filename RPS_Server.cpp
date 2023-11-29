#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <winsock2.h>

#include "protocol.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 9000

GameType determineGameType() {
    // ������������ ������ ����
    srand(static_cast<unsigned>(time(nullptr)));
    return (rand() % 2 == 0) ? GameType::ROCK_PAPER_SCISSORS : GameType::MUK_CHI_PPA;
}

void playRPS(SOCKET clientSocket, GameData& gameData) {
    // ���������� ���� ����
    // ...

    // ���������� ����� ���� �����ڸ� ����
    if (/* ���� �� */) {
        gameData.attack = 0;
    }
    else {
        gameData.attack = 1;
    }

    // �������� Ŭ���̾�Ʈ�� ���� ��� ����
    send(clientSocket, &gameData, sizeof(GameData), 0);
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return -1;
    }

    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;

    // ���� ����
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating server socket" << std::endl;
        WSACleanup();
        return -1;
    }

    // ���� �ּ� ����
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // ���� ���ε�
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error binding server socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // ���� ���� ���
    listen(serverSocket, 1);
    int clientAddrLen = sizeof(clientAddr);

    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    // Ŭ���̾�Ʈ ���� ����
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error accepting client connection" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Client connected" << std::endl;

    // ���� �÷���
    GameData gameData;
    gameData.gameType = determineGameType();
    if (gameData.gameType == GameType::ROCK_PAPER_SCISSORS) {
        playRPS(clientSocket, gameData);
    }
    else {
        // ����� ���� ����
        // ...
    }

    // ���� �ݱ�
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
