#include "restserver.h"
#include <QUrl>
#include <QTimer>

RestServer::RestServer(QObject *parent)
    : QObject(parent)
{
    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

bool RestServer::listen(quint16 port)
{
    return server.listen(QHostAddress::Any, port);
}

void RestServer::newConnection()
{
    QTcpSocket *client = server.nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
}

static QMap<QString, QString> parseQuery(const QString &query)
{
    QMap<QString, QString> params;
    foreach (const QString &pair, query.split('&', QString::SkipEmptyParts)) {
        int eq = pair.indexOf('=');
        if (eq > 0) {
            QString key = QUrl::fromPercentEncoding(pair.left(eq).toUtf8());
            QString val = QUrl::fromPercentEncoding(pair.mid(eq+1).toUtf8());
            params.insert(key, val);
        }
    }
    return params;
}

void RestServer::readClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client)
        return;
    if (!client->canReadLine())
        return;

    QString requestLine = QString::fromUtf8(client->readLine()).trimmed();
    if (!requestLine.startsWith("GET")) {
        client->write("HTTP/1.1 400 Bad Request\r\n\r\n");
        client->disconnectFromHost();
        return;
    }

    QString path = requestLine.section(' ', 1, 1);
    QString endpoint = path.section('?', 0, 0);
    QString query = path.section('?', 1);
    QMap<QString, QString> params = parseQuery(query);

    if (endpoint == "/print" && params.contains("url")) {
        QByteArray resp = "";

        QStringList urls; urls << params.value("url");
        QString printer = params.value("p", "Default");
        double l = params.value("l", "0.5").toDouble();
        double t = params.value("t", "0.5").toDouble();
        double r = params.value("r", "0.5").toDouble();
        double b = params.value("b", "0.5").toDouble();
        QString paper = params.value("a", "A4");
        QString orient = params.value("o", "portrait");
        int pageFrom = params.value("pagefrom", "0").toInt();
        int pageTo = params.value("pageto", "0").toInt();
        double width = params.value("width", "0").toDouble();
        double height = params.value("height", "0").toDouble();
        if (params.contains("a") && params.value("a").contains(',')) {
            QStringList dims = params.value("a").split(',');
            if (dims.size() == 2) {
                bool ok1, ok2;
                double w = dims[0].toDouble(&ok1);
                double h = dims[1].toDouble(&ok2);
                if (ok1 && ok2 && w > 0 && h > 0) {
                    width = w;
                    height = h;
                }
            }
        }
        // Prepare the response in json
        resp = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";
        resp += "[{\"status\":\"started\",\"printer\":\"" + QUrl::toPercentEncoding(printer) + "\",";
        resp += "\"urls\":[";
        for (int i = 0; i < urls.size(); ++i) {
            resp += "\"" + QUrl::toPercentEncoding(urls[i]) + "\"";
            if (i < urls.size() - 1) {
                resp += ",";
            }
        }
        resp += "],\"left\":" + QString::number(l) + ",\"top\":" + QString::number(t) +
                ",\"right\":" + QString::number(r) + ",\"bottom\":" + QString::number(b) +
                ",\"paper\":\"" + QUrl::toPercentEncoding(paper) + "\",\"orientation\":\"" +
                QUrl::toPercentEncoding(orient) + "\",\"pageFrom\":" + QString::number(pageFrom) +
                ",\"pageTo\":" + QString::number(pageTo);
        resp += ",\"width\":" + QString::number(width) + ",\"height\":" + QString::number(height) + "}\r\n";
        

        PrintHtml *job = new PrintHtml(false, true, urls, printer, l, t, r, b, paper, orient, pageFrom, pageTo, width, height, false, client, resp);
        connect(job, SIGNAL(finished()), job, SLOT(deleteLater()));
        QTimer::singleShot(0, job, SLOT(run()));

        
    } else {
        client->write("HTTP/1.1 404 Not Found\r\n\r\n");
        client->disconnectFromHost();
    }
}
