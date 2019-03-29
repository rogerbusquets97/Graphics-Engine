#include "shapecomponentwidget.h"
#include "ui_shapecomponentwidget.h"

ShapeComponentWidget::ShapeComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeComponentWidget)
{
    ui->setupUi(this);
    shape = nullptr;
}

ShapeComponentWidget::~ShapeComponentWidget()
{
    delete ui;
}

void ShapeComponentWidget::Update()
{
    if(shape!= nullptr)
    {
        if(shape->GetShapeType() == ShapeType::CIRCLE)
            ui->comboBox->setCurrentText("Circle");
        if(shape->GetShapeType() == ShapeType::RECTANGLE)
            ui->comboBox->setCurrentText("Rectangle");
    }

    update();
}
