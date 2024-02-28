#pragma mark "include"

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QContextMenuEvent>
#include <QMenu>
#include <QActionGroup>
#include <QAction>
#include <QSizePolicy>
#include <QMenuBar>

#include <QNetworkReply>
#include <QtCore>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
    
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFile>
#include <QNetworkRequest>
#include <QUrl>
#include <QString>
#include <QNetworkAccessManager>
    
    
#include <QGraphicsSceneResizeEvent>

#pragma mark end "include"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    
    ~MainWindow();
    
    
    void setLayout()
    {
        QVBoxLayout *layout = new QVBoxLayout;
        QVBoxLayout *txtLayout = new QVBoxLayout;
        buttonTest = new QPushButton;
        buttonTcp = new QPushButton;
        
        //txtField = new QTextEdit;
        
        txtField->setFixedWidth(500);
        txtField->setPlaceholderText("Test placeholder");
        txtField->setFixedHeight(150);
        txtField->setAlignment(Qt::AlignJustify);
        
        
       // tableWidget = new QTableWidget;
        tableWidget->setStyleSheet("QTableWidget {background-color: #fafafa; color: black;}");
        tableWidget->setRowCount(5);
        tableWidget->setColumnCount(3);
        
        
        
        QHBoxLayout *hLayout = new QHBoxLayout;
        
        buttonTest->setStyleSheet("QPushButton::pressed {background-color: red;} QPushButton {background-color: #fafafa; border-radius: 4px; color: green; max-width: 100px; height: 25px;}");
        buttonTest->setText("Test button");
        
        buttonTcp->setStyleSheet("QPushButton::pressed {background-color: red;} QPushButton {background-color: #fafafa; border-radius: 4px; color: green; max-width: 100px; height: 25px;}");
        buttonTcp->setText("Send http");
        
        
        
        getRequestAct = new QAction(tr("&Get request"), this);
        getRequestAct->setShortcuts(QKeySequence::New);
        getRequestAct->setStatusTip(tr("Create get request"));
        connect(getRequestAct, SIGNAL (triggered()), this, SLOT (getRequest()));
        
        postRequestAct = new QAction(tr("&Post request"), this);
        postRequestAct->setShortcuts(QKeySequence::Paste);
        postRequestAct->setStatusTip(tr("Create post request"));
        connect(postRequestAct, SIGNAL (triggered()), this, SLOT (postRequest()));
        
        getPdfRequestAct = new QAction(tr("&Get PDF"), this);
        getPdfRequestAct->setShortcuts(QKeySequence::Copy);
        getPdfRequestAct->setStatusTip(tr("Get PDF from request"));
        connect(getPdfRequestAct, SIGNAL (triggered()), this, SLOT (getPdfFromHttp()));
        
        QMenuBar *menu = new QMenuBar(centralWidget());
        helpMenu = new QMenu("&Requests");
        helpMenu->addAction(getRequestAct);
        helpMenu->addAction(getPdfRequestAct);
        helpMenu->addAction(postRequestAct);
        
        //helpMenu->exec(QPoint());
       
        
        menu->addMenu(helpMenu);
        
        
        connect(buttonTest, SIGNAL (released()), this, SLOT (handleButton()));
        connect(buttonTcp, SIGNAL (released()), this, SLOT (getRequest()));
        
        
        txtLayout->addWidget(txtField);
        txtLayout->addWidget(tableWidget);
        
        hLayout->addWidget(buttonTest);
        hLayout->addWidget(buttonTcp);
        
        layout->addLayout(txtLayout);
        layout->addLayout(hLayout);
        
        setCentralWidget(new QWidget);
        centralWidget()->setLayout(layout);
    }

private slots:
    void handleButton();
    void connectTcp();
    void readTcpData();
    void getRequest();
    void postRequest();
    void getPdfFromHttp();
public slots:
    void replyGetRequest();
    void replyGetRequestErrorHandler(QNetworkReply::NetworkError);
    
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

    
private:
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *getRequestAct;
    QAction *postRequestAct;
    QAction *getPdfRequestAct;
    
    QPushButton *buttonTest, *buttonTcp;
    QTextEdit *txtField;
    QTableWidget *tableWidget;
    MainWindow *ui;
    QHBoxLayout *mainLayout;
    QTcpSocket *pSocket;
    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
};
