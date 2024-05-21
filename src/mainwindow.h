#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "document.h"
#include "chatbot.h"
#include <QListWidgetItem>
#include "ichatList.h"
#include "iwelcomepage.h"
#include "iuserpage.h"
#include "ichatwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void onHistoryListItemClicked(QListWidgetItem *item);

    void expandSideWidget();

    void addMessage(QString text);

    IChatWidget *getCurrentChatList();
public slots:
    void appendWordToActiveChat(QString reply);
private slots:

    void addNewChat();
    void on_inputLine_returnPressed();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    //std::vector<Document*> m_docus;
    int curr;
    ChatBot* chatbot;

    IWelcomePage* welcome;

    IUserPage* user;
};
#endif // MAINWINDOW_H
