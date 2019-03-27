#include "shapecomponentwidget.h"
#include "ui_shapecomponentwidget.h"

ShapeComponentWidget::ShapeComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeComponentWidget)
{
    ui->setupUi(this);
}

ShapeComponentWidget::~ShapeComponentWidget()
{
    delete ui;
}
