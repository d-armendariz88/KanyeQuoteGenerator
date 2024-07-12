#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getQuote();


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GetQuoteButton_clicked()
{
    getQuote();
}

void MainWindow::getQuote(){
    QNetworkAccessManager Manager;

    QUrl APIUrl("https://api.kanye.rest");
    QNetworkRequest request(APIUrl);
    QNetworkReply *reply = Manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if(reply->error()==QNetworkReply::NoError){
        qDebug() << "Error: " << reply-> errorString();
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject object = document.object();
        QJsonValue quote_value = object.value(QString("quote"));
        QString quote_string = quote_value.toString();
        qDebug()<< "API Response: " << quote_string;

        ui->Quote->setText(quote_string);
    }
    else{
        qDebug() << "Error: " << reply-> errorString();
    }
}
