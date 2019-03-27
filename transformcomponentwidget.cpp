#include "transformcomponentwidget.h"
#include "ui_transformcomponentwidget.h"

TransformComponentWidget::TransformComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformComponentWidget)
{
    ui->setupUi(this);
}

TransformComponentWidget::~TransformComponentWidget()
{
    delete ui;
}
