#include "widget.h"
#include <QFormLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m = 3;
    t = BT::NewTree(NULL,m);

    pixmap = *new QPixmap("welcome.png");
    pixmap = pixmap.scaled(200,200,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    graphLabel = new QLabel;
    graphLabel->setAlignment(Qt::AlignCenter);
    graphLabel->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    graphLabel->setScaledContents(true);
    graphLabel->setPixmap(pixmap);

    insertButton = new QPushButton("插入");
    insertButton->setFixedWidth(100);
    connect(insertButton,SIGNAL(clicked()),this,SLOT(on_insertButton_clicked()));

    deleteButton = new QPushButton("删除");
    deleteButton->setFixedWidth(100);
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(on_deleteButton_clicked()));

    insertLine = new QLineEdit;
    insertLine->setFixedWidth(150);
    deleteLine = new QLineEdit;
    deleteLine->setFixedWidth(150);

    QFormLayout *formLayout = new QFormLayout;
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

void Widget::displayImage()
{
    GraphRes *G = Graph::InitGraph();
    Graph::CreateGraph(t, G->g, NULL);
    Graph::RenderGraph(G);
    Graph::FreeGraph(G);

    pixmap = *new QPixmap("output.png");

    graphLabel->setPixmap(pixmap);
}
