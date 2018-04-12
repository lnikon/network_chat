#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QTime>
#include <QTimerEvent>
#include <QTimer>

static const int MaxBufferSize = 1024000;

class Connection : public QTcpSocket
{
  Q_OBJECT
public:

  enum class ConnectionState
  {
    WaitingForGreeting,
    ReadingGreeting,
    ReadyForUse
  };

  enum class DataType
  {
    PlainText,
    Ping,
    Pong,
    Greeting,
    Undefined
  };

  explicit Connection(QObject *parent = nullptr);

  QString name() const;
  void setGreetingMessage(const QString &message);
  bool sendMessage(const QString &message);

signals:
  void readyForUse();
  void newMessage(const QString &from, const QString &message);

protected:
  void timerEvent(QTimerEvent *timerEvent) override;
private slots:
  void processReadyRead();
  void sendPing();
  void sendGreetingMessage();

private:
  int readDataIntoBuffer(int maxSize = MaxBufferSize);
  int dataLenghtForCurrentDataType();
  bool readProtocolHeader();
  bool hasEnoughData();
  void processData();

  QString greetingMessage;
  QString username;
  QTimer pingTimer;
  QTime pongTime;
  QByteArray buffer;
  ConnectionState state;
  DataType currentDataType;
  int numBytesForCurrentDataType;
  int transferTimerId;
  bool isGreetingMessageSent;
};

#endif // CONNECTION_H
