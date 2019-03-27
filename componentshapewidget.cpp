#include "componentshapewidget.h"

#include "QBoxLayout"

ComponentShapeWidget::ComponentShapeWidget(QWidget *parent) : QWidget(parent)
{
    colorbox = new QComboBox();
    colorbox->addItem(QString("Blue"));
    colorbox->addItem(QString("White"));
    colorbox->addItem(QString("Black"));

    combobox = new QComboBox();
    combobox->addItem(QString("Circle"));
    combobox->addItem(QString("Rectangle"));

    QBoxLayout* votavox = new QBoxLayout(QBoxLayout::TopToBottom);
    votavox->addWidget(combobox);
    votavox->addWidget(colorbox);

    setLayout(votavox);
}

ComponentShapeWidget::~ComponentShapeWidget()
{
    delete combobox;
}
