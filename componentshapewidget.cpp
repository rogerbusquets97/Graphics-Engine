#include "componentshapewidget.h"

#include "QBoxLayout"

ComponentShapeWidget::ComponentShapeWidget(QWidget *parent) : QWidget(parent)
{
    combobox = new QComboBox();
    combobox->addItem(QString("Circle"));
    combobox->addItem(QString("Rectangle"));

    QBoxLayout* votavox = new QBoxLayout(QBoxLayout::TopToBottom);
    votavox->addWidget(combobox);

    setLayout(votavox);
}

ComponentShapeWidget::~ComponentShapeWidget()
{
    delete combobox;
}
