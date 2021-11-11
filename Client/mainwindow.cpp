#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    connectToServer(ui->lineEdit->text(),ui->lineEdit_2->text());
}
void MainWindow::connectToServer(QString ip, QString port)
{
    socket->connectToHost(ip,port.toInt());
}

void MainWindow::onConnected()
{
    ui->textBrowser->insertPlainText("Connecting to host...\n");
}
void MainWindow::onReadyRead()
{
    const auto message = socket->readAll();
    emit newMessage(message);
    ui->textBrowser->insertPlainText("[Server]: " + message + "\n");
}
void MainWindow::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}

void MainWindow::on_pushButton_2_clicked()
{
    sendMessage(ui->textEdit->toPlainText());
}
void MainWindow::sendMessage(const QString message)
{
    if(ui->textEdit->toPlainText()!="")
    {
        ui->textBrowser->insertPlainText("[Client]: " + message +"\n");
        socket->write(message.toUtf8());
    }

}
