/*
 * MIT License
 *
 * Copyright (C) 2017 Kendall Bennett
 * Copyright (C) 2017 AMain.com, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PRINTHTML_H
#define PRINTHTML_H

#include <QObject>
#include <QCoreApplication>

class PrintHtml : public QObject
{
    Q_OBJECT
private:
    QCoreApplication *app;

public:
    PrintHtml(bool testMode, bool json, QStringList urls, QString selectedPrinter, double leftMargin, double topMargin, double rightMargin, double bottomMargin, QString paper);
    void quit();

private:
    bool loadNextUrl();

signals:
    void finished();

public slots:
    void run();
    void aboutToQuitApp();

private slots:
    void htmlLoaded(bool ok);

private:
    bool            testMode;   // True if we are running in test mode
    bool            json;       // True if we want the JSON stdout
    QStringList     urls;       // List of url to print
    QPrinter        *printer;   // Printer object that we print to
    QWebPage        *webPage;   // QWebPage class for printing
    QString         url;
    QStringList     printed;
    QStringList     error;
    QString succeeded;
    QString failed;

};

#endif // PRINTHTML_H
