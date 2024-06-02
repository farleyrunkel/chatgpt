#ifndef IPUSHCARD_H
#define IPUSHCARD_H

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

class IHPushCard : public QFrame
{
    Q_OBJECT

public:
    IHPushCard(QWidget* parent = nullptr);
    IHPushCard(int num, QWidget* parent = nullptr) : IHPushCard(parent) {
        setNumber(num);
    };

    void setNumber(int num);


    void setText(const QString& text);

    void setNumberUnused();

    void setIcon(const QIcon &icon);

protected:
    // 事件过滤器
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    void setupUI();

private:
    QLabel* itemNumberLabel;
    QLabel* itemIconLabel;
    QLabel* itemTextLabel;
};

#endif // IPUSHCARD_H