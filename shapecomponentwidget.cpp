#include "shapecomponentwidget.h"
#include "ui_shapecomponentwidget.h"
#include "iostream"

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
        ui->comboBox->blockSignals(true);
        ui->ShapeWidth->blockSignals(true);

        if(shape->GetShapeType() == ShapeType::CIRCLE)
            ui->comboBox->setCurrentText("Circle");
        if(shape->GetShapeType() == ShapeType::RECTANGLE)
            ui->comboBox->setCurrentText("Rectangle");

        ui->ShapeWidth->setValue(shape->GetWidth());


        ui->comboBox->blockSignals(false);
        ui->ShapeWidth->blockSignals(false);
    }

    update();
}
