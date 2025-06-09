#ifndef RESTSERVER_H
#define RESTSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "printhtml.h"

class RestServer : public QObject
{
    Q_OBJECT
public:
    explicit RestServer(QObject *parent = 0);
    bool listen(quint16 port);

private slots:
    void newConnection();
    void readClient();

private:
    QTcpServer server;
};

#endif // RESTSERVER_H
