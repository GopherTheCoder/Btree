#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include "BT.h"
#include "Graphviz.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();

private:
    void displayImage();

    QLabel *graphLabel;
    QPushButton *insertButton;
    QLineEdit *insertLine;
    QPushButton *deleteButton;
    QLineEdit *deleteLine;

    BTree t;
    int m;
};
#endif // WIDGET_H