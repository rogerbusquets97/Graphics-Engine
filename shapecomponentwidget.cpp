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
        else if(shape->GetColorType()==ColorType::RED)
            ui->comboBox_2->setCurrentText("Red");
        else if(shape->GetColorType()==ColorType::GREEN)
            ui->comboBox_2->setCurrentText("Green");
        else if(shape->GetColorType()==ColorType::MAGENTA)
            ui->comboBox_2->setCurrentText("Magenta");
        else if(shape->GetColorType()==ColorType::ORANGE)
            ui->comboBox_2->setCurrentText("Orange");
        else if(shape->GetColorType()==ColorType::YELLOW)
            ui->comboBox_2->setCurrentText("Yellow");

        if(shape->GetStrokeType() == StrokeType::SOLID)
            ui->comboBox_3->setCurrentText("Solid");
        else if(shape->GetStrokeType() == StrokeType::DASH)
            ui->comboBox_3->setCurrentText("Dash");
        else if(shape->GetStrokeType() == StrokeType::DOT)
            ui->comboBox_3->setCurrentText("Dot");
        else if(shape->GetStrokeType() == StrokeType::DASHDOT)
            ui->comboBox_3->setCurrentText("DashDot");
        else if(shape->GetStrokeType() == StrokeType::DASHDOTDOT)
            ui->comboBox_3->setCurrentText("DashDotDot");

        ui->ShapeWidth->setValue(shape->GetWidth());
        ui->ShapeHeight->setValue(shape->GetHeight());
        ui->ShapeRadius->setValue(shape->GetRadius());
        ui->StrokeWidth->setValue(shape->GetPenWidth());

        ui->comboBox->blockSignals(false);
        ui->ShapeWidth->blockSignals(false);
        ui->ShapeHeight->blockSignals(false);
        ui->ShapeRadius->blockSignals(false);
        ui->comboBox_2->blockSignals(false);

    }

    update();
}
