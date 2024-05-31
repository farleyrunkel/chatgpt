#include "mainwindow.h"

#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QStandardItemModel>
#include <QJsonObject>
#include <QGraphicsDropShadowEffect>

#include "ioverlaybutton.h"
#include "ichatwidget.h"
#include "itestwidget.h"
#include "imarketpage.h"
#include "iwelcomepage.h"
#include "irightwindow.h"
#include "ileftwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , chatbot (new ollama::Client(this))
    , test(new ITestWidget(this))
{
    setupUi();

    //sendButton->setDisabled(true);
   // sendButton->setStatusTip("Nothing");

    setWindowIcon(QIcon("://icon/qollama.png"));

    chats = new IChatsPage;
    pages->addWidget(chats);

    welcome = new IWelcomePage;
    pages->addWidget(welcome);
    pages->setCurrentWidget(welcome);

    statusBar->setStatusTip("AI can make mistakes. Check important info.");

    market = new IMarketPage(this);
    pages->addWidget(market);

    auto userWidget = new QDialog;
    //connect(userButton, &QPushButton::clicked, userWidget, &QDialog::show);
    //connect(exploreButton, &QPushButton::clicked, market, &IMarketPage::show);
   // connect(chatPage, &IWidget::shown, comboBox, &QComboBox::setVisible);
    //connect(marketStackWidget, &IWidget::shown, exploreLabel, &QComboBox::setVisible);

   // connect(newChatButton, &QPushButton::pressed, [&](){pages->setCurrentWidget(welcome);});
   // connect(exploreButton, &QPushButton::pressed, [&](){pages->setCurrentWidget(market);});
    //connect(expandButton, &QPushButton::pressed, this, &MainWindow::expandSideWidget);
   // connect(newChatBtn, &QPushButton::pressed, [&](){pages->setCurrentWidget(welcome);});

    connect(chatbot, &ollama::Client::replyReceived, this, &MainWindow::appendWordToActiveChat);
    connect(chatbot, &ollama::Client::finished, this,  &MainWindow::on_chatbot_finish);

    // connect(sendButton, &QPushButton::clicked,[&](){
    //     if (sendButton->statusTip() == "Pending") {
    //         chatbot->abort();
    //         sendButton->statusTip() = "Nothing";
    //         return ;
    //     }
    //     else if (sendButton->statusTip() == "Waiting") {
    //         on_inputLine_returnPressed();
    //     }
    // });

   // connect(inputLine, &QLineEdit::returnPressed, sendButton, &QPushButton::pressed);

   // connect(historyList, &IHistoryList::itemClicked, this, &MainWindow::on_historyListItem_clicked);
    // connect(historyList, &IHistoryList::itemDeleted, [&](int row){
    //     pages->removeWidget(pages->widget(row));
    //     chatbot->abort();
    //     pages->setCurrentIndex(1);
    // });

    //connect(settingButton, &QPushButton::pressed,  [&](){pages->setCurrentWidget(chats);});

    connect(&ISignalHub::instance(), &ISignalHub::on_IVPushCard_clicked, [&](const QString&){pages->setCurrentWidget(chats);});

}


MainWindow::~MainWindow()
{
}

void MainWindow::on_chatbot_finish() {
   // sendButton->setStatusTip("Nothing");
   // on_inputLine_textChanged(inputLine->text());
    auto *chatListView = chats->currentChat();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageWidget* curr = chatListView->getLatestMessageWidget();
    curr->finish();

}
void MainWindow::expandSideWidget()
{
    left->setVisible(!left->isVisible());
   // expandButton->setVisible(!left->isVisible());

    pages->updateGeometry();

    QApplication::processEvents();
}

void MainWindow::appendWordToActiveChat(QString text)
{
    auto chatListView = chats->currentChat();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageWidget* curr = chatListView->getLatestMessageWidget();
    curr->appendMessage(text);

    chatListView->scrollToBottom();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    //expandButton->hide();
   // comboBox->hide();
    test->hide();
}

void MainWindow::addMessage(QString text )
{
    if (chatbot->status() == ollama::Client::Receiving
        || chatbot->status() == ollama::Client::Requesting
    ) {return;}

    if (text.isEmpty()) {
        qDebug() << "Input text is empty.";
        return;
    }
    // pages->setCurrentIndex(0);
    // sendButton->setEnabled(true);
    // sendButton->setIcon(QIcon(":/icon/stop.svg"));
    // sendButton->setStatusTip("Pending");

    auto chatListView = chats->currentChat();
    auto hisItem = historyList->currentItem();

    if (!chatListView  || chatListView && !chatListView->isNew()) {
        qDebug() << "Create new chatList.";

        auto newChatList = new IChatWidget();

        // pages->addWidget(newChatList);
        // pages->setCurrentWidget(newChatList);

        chatListView = newChatList;

        auto item = new QListWidgetItem(historyList);
        historyList->addItem(item);
        historyList->setCurrentItem(item);

        hisItem = item;
    }

    chatListView->addMessage(text, "farley", QIcon("://icon/farley.jpg").pixmap(30));
    chatListView->addMessage("", "llama3", newChatButton->icon().pixmap(30));
    chatListView->scrollToBottom();

    if (hisItem) {
        hisItem->setToolTip(text);
    } else {
        qDebug() << "Current history list item is null.";
    }

    QJsonObject json ;
    json["prompt"] = text;
  //  json["model"] = comboBox->currentText();

    chatbot->generate(json);
}

void MainWindow::on_historyListItem_clicked(QListWidgetItem *item)
{
    // if (item) {
    //     pages->setCurrentIndex(0);
    //     qDebug() << "historyList->row(item)" << historyList->row(item);
    //     pages->setCurrentIndex(historyList->row(item));
    // } else {
    //     qDebug() << "Clicked history list item is null.";
    // }
}

void MainWindow::on_comboBox_activated(int index)
{
    auto text = "";//comboBox->currentText();
   // inputLine->setPlaceholderText(QString("Message ") + text + "...");
}

void MainWindow::on_inputLine_textChanged(const QString &arg1)
{
    // if ( sendButton->statusTip() == "Pending") {
    //     return;
    // }
    // sendButton->setIcon(QIcon(":/icon/arrow-up-circle.svg"));
    // if (arg1.isEmpty()) {
    //     sendButton->setDisabled(true);
    //     sendButton->setStatusTip("Nothing");
    // }
    // else {
    //     sendButton->setEnabled(true);
    //     sendButton->setStatusTip("Waiting");
    // }
}

void MainWindow::on_inputLine_returnPressed()
{
    // if (chatbot->status() == ollama::Client::Receiving
    //     || chatbot->status() == ollama::Client::Requesting
    //     ) {return;}

    // QString text = inputLine->text().trimmed();

    // if (text.isEmpty()) {
    //     qDebug() << "Input text is empty.";
    //     return;
    // }

    // addMessage(text);
    // inputLine->clear();
}


void MainWindow::on_expandSideBtn_clicked()
{
    expandSideWidget();
}


void MainWindow::setupUi()
{
    if (objectName().isEmpty())
        setObjectName("MainWindow");
    setWindowModality(Qt::WindowModal);
    resize(944, 592);
    QFont font;
    font.setPointSize(10);
    font.setBold(false);
    setFont(font);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/ollama.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);
    setWindowOpacity(1.000000000000000);
    setAutoFillBackground(true);
    setInputMethodHints(Qt::ImhExclusiveInputMask);
    setDocumentMode(false);

    centralwidget = new QWidget(this);
    centralwidget->setObjectName("centralwidget");
    QFont font1;
    font1.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
    font1.setPointSize(10);
    font1.setBold(false);
    centralwidget->setFont(font1);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(centralwidget);
    horizontalLayout->setSpacing(1);
    horizontalLayout->setObjectName("horizontalLayout");
    horizontalLayout->setContentsMargins(1, 1, 1, 1);

    splitter = new QSplitter(centralwidget);
    splitter->setObjectName("splitter");
    splitter->setOrientation(Qt::Horizontal);
    splitter->setOpaqueResize(false);
    splitter->setHandleWidth(0);
    splitter->setChildrenCollapsible(false);

    auto left =  new ILeftWindow;
    splitter->addWidget(left);

    auto right = new IRightWindow;
    splitter->addWidget(right);
    pages = right->pages();

    horizontalLayout->addWidget(splitter);

    setCentralWidget(centralwidget);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName("statusBar");
    setStatusBar(statusBar);

    retranslateUi();
}

void MainWindow::retranslateUi()
{
    setWindowTitle(QCoreApplication::translate("MainWindow", "Ollama", nullptr));

}
