#include "inspector.h"
#include "component.h"

#include "QVBoxLayout"
#include "shapecomponentwidget.h"
#include "QSpacerItem"
#include "transformcomponentwidget.h"
#include "componentshape.h"
#include <iostream>
#include "mainwindow.h"
#include "shapewidget.h"
#include "ui_transformcomponentwidget.h"
#include "ui_shapecomponentwidget.h"
#include "QString"


Inspector::Inspector(QWidget *parent) : QWidget(parent)
{

   //Subwidgets
   transformComponentWidget = new TransformComponentWidget();
   transformComponentWidget->setVisible(false);

   shapeCompoenentWidget = new ShapeComponentWidget();


   //Add them to a vertical layout
   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(transformComponentWidget);
   layout->addWidget(shapeCompoenentWidget);


   //Combo box for adding Components
   comboBox = new QComboBox();
   comboBox->addItem("Shape Component"); // Only shape for now
   layout->addWidget(comboBox);
   //Button to add Components
   button = new QPushButton();
   button->setText("Add Component");
   connect(button,SIGNAL(clicked()),this,SLOT(OnAddComponent()));
   ConnectEvents();
   layout->addWidget(button);
   //Spacer should be added last
   QSpacerItem* spacer = new QSpacerItem(1,0,QSizePolicy::Minimum, QSizePolicy::Minimum);
   layout->addItem(spacer);
   //Set layout to use
   setLayout(layout);

   SetAllInvisible();


}

void Inspector::ConnectEvents()
{
    connect(transformComponentWidget->ui->PositionX,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));
    connect(transformComponentWidget->ui->PositionY,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));
    connect(transformComponentWidget->ui->PositionZ,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));

    connect(transformComponentWidget->ui->RotationX,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));
    connect(transformComponentWidget->ui->RotationY,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));
    connect(transformComponentWidget->ui->RotationZ,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));

    connect(transformComponentWidget->ui->ScaleX,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));
    connect(transformComponentWidget->ui->ScaleY,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));
    connect(transformComponentWidget->ui->ScaleZ,SIGNAL(valueChanged(double)),this,SLOT(OnUpdateSelectedTransform()));

    connect(shapeCompoenentWidget->ui->comboBox, SIGNAL(currentTextChanged(QString)),this,SLOT(OnChangeShapeType(QString)));
    connect(shapeCompoenentWidget->ui->comboBox_2,SIGNAL(currentTextChanged(QString)),this,SLOT(OnChangeShapeColor(QString)));
    connect(shapeCompoenentWidget->ui->ShapeWidth,SIGNAL(valueChanged(double)),this,SLOT(OnChangeShapeParameter()));
    connect(shapeCompoenentWidget->ui->ShapeHeight,SIGNAL(valueChanged(double)),this,SLOT(OnChangeShapeParameter()));
    connect(shapeCompoenentWidget->ui->ShapeRadius,SIGNAL(valueChanged(double)),this,SLOT(OnChangeShapeParameter()));

}
void Inspector::OnAddComponent()
{
    if(selected!= nullptr)
    {
        if(comboBox->currentText() == "Shape Component")
        {
            ComponentShape* component = new ComponentShape(selected,ComponentType::Shape);
            selected->OnAddComponent(component);
            w->shape_widget->AddComponentShape(component);
            w->shape_widget->update();
        }
        //other components

        UpdateContent();

    }
}

void Inspector::OnChangeShapeColor(QString color)
{
    if(color == "Blue")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::BLUE);
    else if(color == "White")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::WHITE);
    else if(color == "Black")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::BLACK);
    else if(color == "Red")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::RED);
    else if(color == "Green")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::GREEN);
    else if(color == "Magenta")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::MAGENTA);
    else if(color == "Orange")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::ORANGE);
    else if(color == "Yellow")
        shapeCompoenentWidget->GetComponentShape()->SetColorType(ColorType::YELLOW);

    w->shape_widget->update();
    UpdateContent();
}

void Inspector::OnChangeShapeParameter()
{
    ComponentShape* c = shapeCompoenentWidget->GetComponentShape();
    if(c!= nullptr)
    {
        c->SetWidth(shapeCompoenentWidget->ui->ShapeWidth->value());
        c->SetHeight(shapeCompoenentWidget->ui->ShapeHeight->value());
        c->SetRadius(shapeCompoenentWidget->ui->ShapeRadius->value());
    }

    w->shape_widget->update();
    UpdateContent();
}

void Inspector::OnChangeShapeType(QString type)
{
     if(type == "Circle")
         shapeCompoenentWidget->GetComponentShape()->SetShapeType(ShapeType::CIRCLE);
     else if(type == "Rectangle")
         shapeCompoenentWidget->GetComponentShape()->SetShapeType(ShapeType::RECTANGLE);

     w->shape_widget->update();
     UpdateContent();
}
void Inspector::SetAllInvisible()
{
    transformComponentWidget->setVisible(false);
    shapeCompoenentWidget->setVisible(false);
    comboBox->setVisible(false);
    button->setVisible(false);

}
void Inspector::SetObject(GameObject* obj)
{
    selected = obj;
    UpdateContent();
}

GameObject* Inspector::GetObject()const
{
    return selected;
}
void Inspector::UpdateTransform()
{
    BlockSignals(true);
    transformComponentWidget->ui->PositionX->setValue(selected->transform->GetPosition().x);
    transformComponentWidget->ui->PositionY->setValue(selected->transform->GetPosition().y);
    transformComponentWidget->ui->PositionZ->setValue(selected->transform->GetPosition().z);

    transformComponentWidget->ui->RotationX->setValue(selected->transform->GetRotation().x);
    transformComponentWidget->ui->RotationY->setValue(selected->transform->GetRotation().y);
    transformComponentWidget->ui->RotationZ->setValue(selected->transform->GetRotation().z);

    transformComponentWidget->ui->ScaleX->setValue(selected->transform->GetScale().x);
    transformComponentWidget->ui->ScaleY->setValue(selected->transform->GetScale().y);
    transformComponentWidget->ui->ScaleZ->setValue(selected->transform->GetScale().z);

    BlockSignals(false);
    transformComponentWidget->update();
}
void Inspector::BlockSignals(bool b)
{
    transformComponentWidget->ui->PositionX->blockSignals(b);
    transformComponentWidget->ui->PositionY->blockSignals(b);
    transformComponentWidget->ui->PositionZ->blockSignals(b);
    transformComponentWidget->ui->RotationX->blockSignals(b);
    transformComponentWidget->ui->RotationY->blockSignals(b);
    transformComponentWidget->ui->RotationZ->blockSignals(b);

    transformComponentWidget->ui->ScaleX->blockSignals(b);
    transformComponentWidget->ui->ScaleY->blockSignals(b);
    transformComponentWidget->ui->ScaleZ->blockSignals(b);
}
void Inspector::UpdateContent()
{
    //Set all invisible before checking for available components
    shapeCompoenentWidget->setVisible(false);
    transformComponentWidget->setVisible(false);

    if(selected!=nullptr)
    {
        transformComponentWidget->setVisible(true);
        UpdateTransform();
        button->setVisible(true);
        comboBox->setVisible(true);
        for(QList<Component*>::iterator it = selected->components.begin(); it!= selected->components.end(); ++it)
        {
            switch ((*it)->GetType()) {
            case ComponentType::Shape:
                //Set visible shape component
                shapeCompoenentWidget->setVisible(true);
                shapeCompoenentWidget->SetComponentShape((ComponentShape*)(*it));
                shapeCompoenentWidget->Update();
                break;
            default:
                break;
            }
        }
    }
    else
    {
        SetAllInvisible();
    }
}

void Inspector::OnUpdateSelectedTransform()
{
    std::cout<< "OnUpdateSelectedTransf " << std::endl;
    selected->transform->SetPosition((float)transformComponentWidget->ui->PositionX->value(),(float)transformComponentWidget->ui->PositionY->value(),(float)transformComponentWidget->ui->PositionZ->value());
    selected->transform->SetRotation((float)transformComponentWidget->ui->RotationX->value(),(float)transformComponentWidget->ui->RotationY->value(),(float)transformComponentWidget->ui->RotationZ->value());
    selected->transform->SetScale((float)transformComponentWidget->ui->ScaleX->value(),(float)transformComponentWidget->ui->ScaleY->value(),(float)transformComponentWidget->ui->ScaleZ->value());

    w->shape_widget->update();
}
