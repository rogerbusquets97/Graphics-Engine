#include "componentshapewidget.h"

#include "QBoxLayout"

ComponentShapeWidget::ComponentShapeWidget(QWidget *parent) : QWidget(parent)
{
    colorbox = new QComboBox();
    colorbox->addItem(QString("Blue"));
    colorbox->addItem(QString("White"));
    colorbox->addItem(QString("Black"));
    colorbox->addItem(QString("Red"));
    colorbox->addItem(QString("Green"));
    colorbox->addItem(QString("Magenta"));
    colorbox->addItem(QString("Orange"));
    colorbox->addItem(QString("Yellow"));



    combobox = new QComboBox();
    combobox->addItem(QString("Circle"));
    combobox->addItem(QString("Rectangle"));

    strokebox = new QComboBox();
    strokebox->addItem(QString("Solid"));
    strokebox->addItem(QString("Dash"));
    strokebox->addItem(QString("Dot"));
    strokebox->addItem(QString("DashDot"));
    strokebox->addItem(QString("DashDotDot"));

    QBoxLayout* votavox = new QBoxLayout(QBoxLayout::TopToBottom);
    votavox->addWidget(combobox);
    votavox->addWidget(colorbox);
    votavox->addWidget(strokebox);

    setLayout(votavox);
}

ComponentShapeWidget::~ComponentShapeWidget()
{
    delete combobox;
}
