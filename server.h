#pragma once
#include <QTcpServer>
#include <string>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>

#include "chat.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();



    void setChatroom(const std::shared_ptr<Chat> chatroom);

private:
    QVector <QTcpSocket*> Clients;
    //QByteArray Data;

    void sendToAll(std::string str);
    void sendToClient(QTcpSocket* client, std::string str);
    std::shared_ptr<Chat> m_chatroom;
    QTcpSocket *socket;

public slots:
    void incomingConnection(qintptr handle) override; // обработчик новых подключений
    void slotDisconnected();
    void slotReadyRead();// обработчик полученных сообщений

};
