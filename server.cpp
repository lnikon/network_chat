#include "server.h"
#include "connection.h"

#include <QtNetwork>

Server::Server(QObject *parent)
  : QTcpServer(parent)
{
  listen(QHostAddress::Any);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
  Connection *connection = new Connection();
  connection->setSocketDescriptor(socketDescriptor);
  emit newConnection(connection);
}
