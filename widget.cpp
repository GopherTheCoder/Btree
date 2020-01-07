#include "widget.h"
#include <QFormLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pixmap = *new QPixmap("logo.png");
    graphLabel = new QLabel;
    graphLabel->setAlignment(Qt::AlignCenter);
    graphLabel->setMinimumSize(pixmap.size());
    graphLabel->setPixmap(pixmap);

    MButton = new QPushButton("设置M");
    MButton->setFixedWidth(100);
    connect(MButton,SIGNAL(clicked()),this,SLOT(on_MButton_clicked()));
    MLine = new QLineEdit;
    MLine->setFixedWidth(150);

    insertButton = new QPushButton("插入");
    insertButton->setFixedWidth(100);
    connect(insertButton,SIGNAL(clicked()),this,SLOT(on_insertButton_clicked()));
    insertButton->setEnabled(false);
    insertLine = new QLineEdit;
    insertLine->setFixedWidth(150);
    insertLine->setEnabled(false);

    deleteButton = new QPushButton("删除");
    deleteButton->setFixedWidth(100);
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(on_deleteButton_clicked()));
    deleteButton->setEnabled(false);
    deleteLine = new QLineEdit;
    deleteLine->setFixedWidth(150);
    deleteLine->setEnabled(false);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(MLine,MButton);
    formLayout->addRow(insertLine,insertButton);
    formLayout->addRow(deleteLine,deleteButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(graphLabel,1);
    mainLayout->addLayout(formLayout);
    setLayout(mainLayout);
}

void Widget::on_insertButton_clicked()
{
    BT::Insert(t,insertLine->text().toInt(),m);
    insertLine->clear();
    displayImage();
}

void Widget::on_deleteButton_clicked()
{
    BT::Delete(t,deleteLine->text().toInt(),m);
    deleteLine->clear();
    displayImage();
}

void Widget::on_MButton_clicked()
{
    m = MLine->text().toInt();
    t = BT::NewTree(NULL,m);

    MButton->setEnabled(false);
    MLine->setEnabled(false);
    insertButton->setEnabled(true);
    insertLine->setEnabled(true);
    deleteButton->setEnabled(true);
    deleteLine->setEnabled(true);
}

void Widget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    graphLabel->setPixmap(pixmap.scaled(graphLabel->size(),Qt::KeepAspectRatio));
}

void Widget::displayImage()
{
    GraphRes *G = Graph::InitGraph();
    Graph::CreateGraph(t, G->g, NULL);
    Graph::RenderGraph(G);
    Graph::FreeGraph(G);

    pixmap = *new QPixmap("output.png");

    graphLabel->setMinimumSize(pixmap.size());
    graphLabel->setPixmap(pixmap.scaled(graphLabel->size(),Qt::KeepAspectRatio));
}
