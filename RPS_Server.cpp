#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <winsock2.h>

#include "protocol.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 9000

GameType determineGameType() {
    // 가위바위보로 선공을 정함
    srand(static_cast<unsigned>(time(nullptr)));
    return (rand() % 2 == 0) ? GameType::ROCK_PAPER_SCISSORS : GameType::MUK_CHI_PPA;
}

void playRPS(SOCKET clientSocket, GameData& gameData) {
    // 가위바위보 게임 로직
    // ...

    // 가위바위보 결과에 따라 공격자를 설정
    if (/* 서버 승 */) {
        gameData.attack = 0;
    }
    else {
        gameData.attack = 1;
    }

    // 서버에서 클라이언트로 게임 결과 전송
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

    // 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating server socket" << std::endl;
        WSACleanup();
        return -1;
    }

    // 서버 주소 설정
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // 소켓 바인딩
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error binding server socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // 소켓 수신 대기
    listen(serverSocket, 1);
    int clientAddrLen = sizeof(clientAddr);

    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    // 클라이언트 연결 수락
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error accepting client connection" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Client connected" << std::endl;

    // 게임 플레이
    GameData gameData;
    gameData.gameType = determineGameType();
    if (gameData.gameType == GameType::ROCK_PAPER_SCISSORS) {
        playRPS(clientSocket, gameData);
    }
    else {
        // 묵찌빠 게임 로직
        // ...
    }

    // 소켓 닫기
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
