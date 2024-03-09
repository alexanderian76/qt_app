#include "mainwindow.h"
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QtWidgets>
#include <QUrlQuery>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), txtField(new QTextEdit), tableWidget(new QTableWidget), mainLayout(new QHBoxLayout)
{
    networkManager = new QNetworkAccessManager;
    pSocket = new QTcpSocket;
    setLayout();
}



void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(getRequestAct);
    menu.addAction(postRequestAct);
    QTableWidgetItem *item1(tableWidget->item(0,0));
    if(item1 && tableWidget->itemAt(0, 0)->text().length() > 0)
        menu.actions().at(1)->setEnabled(false);
    else
        menu.actions().at(1)->setEnabled(true);
    menu.exec(event->globalPos());
}


void MainWindow::getPdfFromHttp()
{
    
    QNetworkRequest request;
    
    request.setUrl(QUrl("http://localhost:5067/Home/GetPdfFromHtml"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
      
    reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, [this]()
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            qDebug() << "Data: " << data.toStdString().c_str();
            QFileDialog::saveFileContent(data);
        }
            //emit sgProcImage(reply->readAll());
        else
            qDebug() << "Fail to get request!";
           // procNetworkFinishedReplyError(reply);
        delete reply;
        //reply->deleteLater();
    });
    connect(reply, &QNetworkReply::errorOccurred, this, &MainWindow::replyGetRequestErrorHandler);
}

void MainWindow::replyGetRequest()
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        txtField->setText(QString(data));
        qDebug() << "Data: " << data.toStdString().c_str();
        tableWidget->setItem(1, 1, new QTableWidgetItem(QString(data)));
    }
        //emit sgProcImage(reply->readAll());
    else
        qDebug() << "Fail to get request!";
       // procNetworkFinishedReplyError(reply);

    delete reply;
}


void MainWindow::replyGetRequestErrorHandler(QNetworkReply::NetworkError error)
{
    QMessageBox *msg = new QMessageBox;
    msg->setAttribute(Qt::WA_DeleteOnClose, true);
    msg->setText(reply->errorString().toCaseFolded());
    msg->show();
    qDebug() << "Error handler error: " << error;
    delete reply;
}


void MainWindow::getRequest()
{
    
    QNetworkRequest request;
    
    request.setUrl(QUrl("http://localhost:5067/Home/GetPhoneById?id=" + txtField->toPlainText()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
      
    reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, this, &MainWindow::replyGetRequest);
    connect(reply, &QNetworkReply::errorOccurred, this, &MainWindow::replyGetRequestErrorHandler);
    
}


void MainWindow::postRequest()
{
    
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:5067/Home/CreateRandomPhone"));
    
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("title", QString::number(55));
       
    
    reply = networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    
    connect(reply, &QNetworkReply::finished, [this]()
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            txtField->setText(QString(data));
            qDebug() << "Data: " << data.toStdString().c_str();
            tableWidget->setItem(1, 1, new QTableWidgetItem(QString(data)));
            
        }
            //emit sgProcImage(reply->readAll());
        else
            qDebug() << "Fail to get request!";
        delete reply;
        //reply->deleteLater();
    });
    connect(reply, &QNetworkReply::errorOccurred, this, &MainWindow::replyGetRequestErrorHandler);
}

void MainWindow::connectTcp()
{
    QByteArray data = this->txtField->toPlainText().toUtf8();
    
    //pSocket = new QTcpSocket; // <-- needs to be a member variable: QTcpSocket * _pSocket;
    connect( pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );

    pSocket->connectToHost("127.0.0.1", 1234);
    if( pSocket->waitForConnected() ) {
        pSocket->write( data );
    }
}

void MainWindow::readTcpData()
{
    QByteArray data = pSocket->readAll();
    txtField->setText(QString(data));
    qDebug() << "Data: " << data.toStdString().c_str();
}

void MainWindow::handleButton()
{
    char *c = "123";
    int n = 1;
    int *t = &n;
    char **q = &c;
    n++;
    unsigned long r = (unsigned long)&c;
    qDebug() << "*r" << *reinterpret_cast<char **>(r);

    qDebug() << "q" << q;
    qDebug() << "*q" << *q;
    qDebug() << "&c" << &c;
    qDebug() << "c" << c;
    qDebug() << "*c" << *c;
    c = c + 1;

    qDebug() << "c" << c;
    qDebug() << "c+1" << *c;
    *c++;
    qDebug() << "c" << c;
    qDebug() << "*c++" << *c;
    qDebug() << "&c" << &c;
    qDebug() << "*t" << *t;
    *c++;
    c = c - 3;
    qDebug() << "*q" << *q;
    qDebug() << "c" << c;
};

MainWindow::~MainWindow()
{
   // pSocket->~QTcpSocket();
   // networkManager->~QNetworkAccessManager();
    delete pSocket;
    delete networkManager;
    delete txtField;
    delete tableWidget;
    delete mainLayout;
}
