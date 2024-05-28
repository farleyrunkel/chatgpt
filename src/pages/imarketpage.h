#ifndef IMARKETPAGE_H
#define IMARKETPAGE_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QSizePolicy>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QFrame>
#include <QScrollBar>
#include <QDebug>
#include <QEvent>

class IMarketPage : public QScrollArea
{
    Q_OBJECT

public:
    IMarketPage(QWidget* parent = nullptr);

private:
    void setupTopSearchArea();

    void setupTitle();

    void setupSearchLine();

    void setupNavigator();

    void addKind(const QString& text);

    void setupKinds();

protected:
    void scrollContentsBy(int dx, int dy) override;

private:
    QVBoxLayout* contentLayout;
    QVBoxLayout* mainLayout;
    QWidget* containerWidget;
    QWidget* topSearchArea;
    QWidget* titleWidget;
    QWidget* searchLineFrame;
    QWidget* navigatorWidget;

    QVector<QPair<QPushButton*, QWidget*>> kindButtons;
};

#endif // IMARKETPAGE_H