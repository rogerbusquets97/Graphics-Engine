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
        ui->ShapeHeight->blockSignals(true);
        ui->ShapeRadius->blockSignals(true);
        ui->comboBox_2->blockSignals(true);

        if(shape->GetShapeType() == ShapeType::CIRCLE)
            ui->comboBox->setCurrentText("Circle");
        else if(shape->GetShapeType() == ShapeType::RECTANGLE)
            ui->comboBox->setCurrentText("Rectangle");
        if(shape->GetColorType() == ColorType::BLUE)
            ui->comboBox_2->setCurrentText("Blue");
        else if(shape->GetColorType() == ColorType::WHITE)
            ui->comboBox_2->setCurrentText("White");
        else if(shape->GetColorType()==ColorType::BLACK)
            ui->comboBox_2->setCurrentText("Black");

        ui->ShapeWidth->setValue(shape->GetWidth());
        ui->ShapeHeight->setValue(shape->GetHeight());
        ui->ShapeRadius->setValue(shape->GetRadius());


        ui->comboBox->blockSignals(false);
        ui->ShapeWidth->blockSignals(false);
        ui->ShapeHeight->blockSignals(false);
        ui->ShapeRadius->blockSignals(false);
        ui->comboBox_2->blockSignals(false);

    }

    update();
}
