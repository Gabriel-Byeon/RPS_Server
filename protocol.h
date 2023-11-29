#pragma once

enum class MessageType {
    CHOICE_REQUEST,  // ������ Ŭ���̾�Ʈ���� ���� ��û
    CHOICE_RESPONSE, // Ŭ���̾�Ʈ�� �������� ���� ����
    GAME_RESULT,     // ���� ���
    STATS_REQUEST,   // �������� �·��� ��û
    STATS_RESPONSE,  // ������ Ŭ���̾�Ʈ���� �·��� ����
    EXIT_REQUEST     // Ŭ���̾�Ʈ�� ���� ��û
};

struct MessageHeader {
    MessageType messageType;
    size_t messageSize;
    // �߰����� �ɼ�
    int option;
};

enum class GameType {
    ROCK_PAPER_SCISSORS,
    MUK_CHI_PPA
};

struct GameData {
    GameType gameType;
    int attack;  // 0: ���� ��, 1: Ŭ���̾�Ʈ ��
    int win;     // 0: ����� ���� ��, 1: ����� Ŭ���̾�Ʈ ��
    float winRate;
    int statsRequest; // 0: �⺻��, 1: �·� ��û
    int exitRequest;  // 0: �⺻��, 1: ���� ��û
};
