#include "widget.h"
#include <QImageReader>
#include <QImage>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m=3;
    t=BT::NewTree(NULL,m);

    graphLabel = new QLabel;
    graphLabel->setText("Welcome!~");
    graphLabel->setAlignment(Qt::AlignCenter);
    graphLabel->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

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
    //formLayout->setFormAlignment(Qt::AlignRight);
    formLayout->addRow(insertLine,insertButton);
    formLayout->addRow(deleteLine,deleteButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->addWidget(graphLabel);
    mainLayout->addLayout(formLayout);
    setLayout(mainLayout);
}

Widget::~Widget()
{
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

    graphLabel->setPixmap(QPixmap::fromImageReader(new QImageReader("output.png")));
}
