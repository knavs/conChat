#include "server.h"
#include <QTextStream>
#include <sstream>
Server::Server()
{
    if (this->listen(QHostAddress::LocalHost, 2323)) {
        qInfo() << "[OK] ChatServer start";
        //waitForNewConnection(10000);
        this->waitForNewConnection();
    } else {
        qInfo() << "[OK] ChatServer start";
    }

}

Server::~Server()
{
    qDeleteAll(Clients);
    Clients.clear();
}

void Server::setChatroom(const std::shared_ptr<Chat> chatroom)
{
    m_chatroom = chatroom;

}

void Server::sendToAll(std::string str)
{
    for (auto client_socket : Clients) {
        client_socket->write(str.c_str());
        client_socket->flush();

    }

    //socket->waitForReadyRead();

}

void Server::sendToClient(QTcpSocket* client, std::string str)
{
    client->write(str.c_str());
    client->flush();
    //socket->waitForReadyRead();

}

void Server::incomingConnection(qintptr handle)
{
    socket = new QTcpSocket;

    socket->setSocketDescriptor(handle);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::slotDisconnected);

    // добавляем в список участников чата

    Clients.append(socket);




    qDebug() << "Incoming connection from sd:" << handle;// << socket.

    sendToClient(socket, m_chatroom->welcome());

}

void Server::slotDisconnected()
{
    qDebug() << QString("Client with sd:%1 disconnected.").arg(socket->socketDescriptor());
    m_chatroom->ChangeCurrentState<StrangerState>();
    socket->deleteLater();
    return;
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*) sender();
    auto data =  QString(socket->readAll()).trimmed();

    //m_chatroom->getCurrentUser()
    // По идее тут можно сделать привязку по handle id r пользователю, но пока и так сойдет


    std::string result;


    std::stringstream tempout;
    m_chatroom->interact(data.toStdString(), tempout);
    result = tempout.str();


    auto [cmd, rest] = Chat::parseCommand(data.toStdString());



    qDebug() << QString("SD: %1 CMD:%2 ARGS:%3 RET:%%").arg(socket->socketDescriptor())
                                                       .arg(cmd.c_str())
                                                       .arg(rest.c_str());
                                                       //.arg(result.c_str());

    if (!result.empty()) sendToClient(socket, result + "\r\n");
}


