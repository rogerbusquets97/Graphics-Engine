#include "componentlightwidget.h"
#include "ui_componentlightwidget.h"
#include <QColorDialog>
#include <iostream>
ComponentLightWidget::ComponentLightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentLightWidget)
{
    ui->setupUi(this);
}

ComponentLightWidget::~ComponentLightWidget()
{
    delete ui;
}

void ComponentLightWidget::OnChangeLightColor()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    if(color.isValid())
    {
        ComponentLight->SetRGBColor(Color(color.red()/255.0, color.green()/255.0,color.blue()/255.0));
    }
}

void ComponentLightWidget::OnChangeLightType(LightType t)
{
    ComponentLight->SetLightType(t);
}

void ComponentLightWidget::OnChangeLightCutOff(float c)
{
    ComponentLight->setcutOff(c);
}

void ComponentLightWidget::OnChangeLightAmbient(float a)
{
    ComponentLight->setAmbient(a);
}

void ComponentLightWidget::OnChangeLightDiffuse(float d)
{
    ComponentLight->setDiffuse(d);
}

void ComponentLightWidget::OnChangeLightSpecular(float s)
{
    ComponentLight->setSpecular(s);
}

void ComponentLightWidget::OnChangeLightOutterCutOff(float c)
{
    ComponentLight->setOuterCutOff(c);
}
