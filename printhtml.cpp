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

#include "printhtml.h"
#include <QDebug>

/*
 * Constructor for the HTML printing class
 */
PrintHtml::PrintHtml(bool testMode, QStringList urls, QString selectedPrinter, double leftMargin, double topMargin, double rightMargin, double bottomMargin, QString paper)
{
    // Get the instance of the main application
    app = QCoreApplication::instance();

    // Create our printer and set the defaults
    printer = new QPrinter(QPrinter::HighResolution);
    if (selectedPrinter != "Default") {
        printer->setPrinterName(selectedPrinter);
    }
    printer->setOrientation(QPrinter::Portrait);
    if (paper == "A4") {
        printer->setPaperSize(QPrinter::A4);
    } else if(paper == "A5") {
        printer->setPaperSize(QPrinter::A5);
    } else {
        printer->setPaperSize(QPrinter::Letter);
    }
    printer->setPageMargins(leftMargin, topMargin, rightMargin, bottomMargin, QPrinter::Inch);

    // Create our web page
    webPage = new QWebPage();

    // Save the URL
    this->urls = urls;

    // Save test mode
    this->testMode = testMode;
}

/*
 * 10ms after the application starts this method will run
 * all QT messaging is running at this point so threads, signals and slots
 * will all work as expected.
 */
void PrintHtml::run()
{
    loadNextUrl();
}

/*
 * Function to quit the application
 */
void PrintHtml::quit()
{
    emit finished();
}

/*
 * 10ms after the application starts this method will run
 * all QT messaging is running at this point so threads, signals and slots
 * will all work as expected.
 */
bool PrintHtml::loadNextUrl()
{
    // Grab the URL to print. If there are none left, return false
    if (this->urls.isEmpty()) {
        return false;
    }
    this->url = this->urls.takeFirst();

    // Load the HTML into the web page
    webPage->mainFrame()->load(this->url);
    webPage->disconnect();
    connect(webPage, SIGNAL(loadFinished(bool)), this, SLOT(htmlLoaded(bool)));

    // Return true indicating we loaded it
    return true;
}

/*
 * Function called when the web page for the HTML has finished loading
 */
void PrintHtml::htmlLoaded(
    bool ok)
{
    if (ok) {
        // Print the page if not in test mode
        if (!this->testMode) {
            webPage->mainFrame()->setZoomFactor(1.2);
            webPage->mainFrame()->print(printer);
        }
        printed << this->url;
        if (!loadNextUrl()) {
            // Bail if that was the last one
            if (this->testMode){
                QMessageBox msgBox;
                msgBox.setWindowTitle("Successly loaded URLs");
                msgBox.setText(printed.join("\n"));
                msgBox.exec();
            }
            QCoreApplication::exit(0);
        }
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fatal Error");
        msgBox.setText("HTML page failed to load!");
        msgBox.exec();
        QCoreApplication::exit(-1);
    }
}

/*
 * Shortly after quit is called the CoreApplication will signal this routine
 * this is a good place to delete any objects that were created in the
 * constructor and/or to stop any threads
 */
void PrintHtml::aboutToQuitApp()
{
    delete printer;
    delete webPage;
}
