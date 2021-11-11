#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket* socket;

signals:
    void newMessage(const QByteArray &ba);

public slots:
    void sendMessage(const QString message);
    void connectToServer(QString ip, QString port);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
