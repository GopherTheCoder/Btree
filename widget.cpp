#include "widget.h"
#include <QFormLayout>
#include <QIntValidator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pixmap = *new QPixmap("logo.png");
    graphLabel = new QLabel;
    graphLabel->setAlignment(Qt::AlignCenter);
    graphLabel->setMinimumSize(pixmap.size());
    graphLabel->setPixmap(pixmap);

    // M
    MButton = new QPushButton(QStringLiteral("设置M"));
    MButton->setFixedWidth(100);
    connect(MButton,SIGNAL(clicked()),this,SLOT(on_MButton_clicked()));

    MLine = new QLineEdit;
    MLine->setFixedWidth(150);
    MLine->setValidator(new QIntValidator(MLine));
    connect(MLine,SIGNAL(returnPressed()),this,SLOT(on_MButton_clicked()));

    // insert
    insertButton = new QPushButton(QStringLiteral("插入"));
    insertButton->setFixedWidth(100);
    connect(insertButton,SIGNAL(clicked()),this,SLOT(on_insertButton_clicked()));
    insertButton->setEnabled(false);

    insertLine = new QLineEdit;
    insertLine->setFixedWidth(150);
    insertLine->setValidator(new QIntValidator(insertLine));
    connect(insertLine,SIGNAL(returnPressed()),this,SLOT(on_insertButton_clicked()));
    insertLine->setEnabled(false);

    //delete
    deleteButton = new QPushButton(QStringLiteral("删除"));
    deleteButton->setFixedWidth(100);
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(on_deleteButton_clicked()));
    deleteButton->setEnabled(false);

    deleteLine = new QLineEdit;
    deleteLine->setFixedWidth(150);
    deleteLine->setValidator(new QIntValidator(deleteLine));
    connect(deleteLine,SIGNAL(returnPressed()),this,SLOT(on_deleteButton_clicked()));
    deleteLine->setEnabled(false);

    actionLabel = new QLabel;
    resLabel = new QLabel;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(MLine,MButton);
    formLayout->addRow(insertLine,insertButton);
    formLayout->addRow(deleteLine,deleteButton);
    formLayout->addRow(actionLabel,resLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(graphLabel,1);
    mainLayout->addLayout(formLayout);
    setLayout(mainLayout);

    setTabOrder(insertLine,deleteLine);
}

void Widget::on_insertButton_clicked()
{
    QString text = insertLine->text();

    if (text.isEmpty()) {
        resLabel->setText("");
        actionLabel->setText(QStringLiteral("请输入数值"));
        actionLabel->setStyleSheet("color:red");
    } else {
        insertLine->clear();

        actionLabel->setStyleSheet("color:black");
        actionLabel->setText(QStringLiteral("插入 ") + text);

        if (BT::Insert(t,text.toInt(),m)) {
            resLabel->setStyleSheet("color:green");
            resLabel->setText(QStringLiteral("成功！"));
            displayImage();
        } else {
            resLabel->setStyleSheet("color:red");
            resLabel->setText(QStringLiteral("失败！"));
        }
    }
}

void Widget::on_deleteButton_clicked()
{
    QString text = deleteLine->text();

    if (text.isEmpty()) {
        resLabel->setText("");
        actionLabel->setText(QStringLiteral("请输入数值"));
        actionLabel->setStyleSheet("color:red");
    } else {
        deleteLine->clear();

        actionLabel->setStyleSheet("color:black");
        actionLabel->setText(QStringLiteral("删除 ") + text);

        if (BT::Delete(t,text.toInt(),m)) {
            resLabel->setStyleSheet("color:green");
            resLabel->setText(QStringLiteral("成功！"));

            if (BT::isEmpty(t))
                updatePixmep("logo.png");
            else
                displayImage();
        } else {
            resLabel->setStyleSheet("color:red");
            resLabel->setText(QStringLiteral("失败！"));
        }
    }
}

void Widget::on_MButton_clicked()
{
    if (MLine->text().isEmpty()) {
        actionLabel->setText(QStringLiteral("请输入数值"));
        actionLabel->setStyleSheet("color:red");
    }
    else
    {
        m = MLine->text().toInt();
        t = BT::NewTree(NULL,m);

        MButton->setEnabled(false);
        MLine->setEnabled(false);
        insertButton->setEnabled(true);
        insertLine->setEnabled(true);
        deleteButton->setEnabled(true);
        deleteLine->setEnabled(true);

        insertLine->setFocus();
    }
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

    updatePixmep("output.png");
}

void Widget::updatePixmep(const char *png)
{
    pixmap = *new QPixmap(png);
    graphLabel->setMinimumSize(pixmap.size());
    graphLabel->setPixmap(pixmap.scaled(graphLabel->size(),Qt::KeepAspectRatio));
}
