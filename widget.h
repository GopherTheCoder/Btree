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

private slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    void on_MButton_clicked();

private:
    void resizeEvent(QResizeEvent *event) override;
    void displayImage();
    void updatePixmep(const char*);

    QLabel *graphLabel;

    QPushButton *MButton;
    QLineEdit *MLine;
    QPushButton *insertButton;
    QLineEdit *insertLine;
    QPushButton *deleteButton;
    QLineEdit *deleteLine;

    QLabel *actionLabel;
    QLabel *resLabel;

    QPixmap pixmap;

    BTree t;
    int m;
};
#endif // WIDGET_H
