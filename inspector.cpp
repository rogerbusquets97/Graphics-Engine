#include "inspector.h"
#include "component.h"

#include "QVBoxLayout"
#include "QSpacerItem"
#include "transformcomponentwidget.h"
#include <iostream>
#include "mainwindow.h"
#include "ui_transformcomponentwidget.h"
#include "ui_componentlightwidget.h"
#include "ui_shapecomponentwidget.h"
#include "ui_meshcomponentwidget.h"
#include "QString"
#include "transform.h"
#include "componentlight.h"

#include <QWidget>
#include <QPainter>

#include <QObject>
#include <QWidget>
#include <QComboBox>

#include "myopenglwidget.h"

Inspector::Inspector(QWidget *parent) : QWidget(parent)
{

   //Subwidgets
   transformComponentWidget = new TransformComponentWidget();
   transformComponentWidget->setVisible(false);

   meshComponentWidget = new MeshComponentWidget();
   componentLightWidget = new ComponentLightWidget();
   componentLightWidget->setVisible(false);

   //Add them to a vertical layout
   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(transformComponentWidget);
   layout->addWidget(meshComponentWidget);
   layout->addWidget(componentLightWidget);


   //Combo box for adding Components
   comboBox = new QComboBox();
  // comboBox->addItem("Shape Component"); // Only shape for now
   comboBox->addItem("Mesh Component");
   comboBox->addItem("Light Component");

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

Inspector::~Inspector()
{
    delete transformComponentWidget;
    delete meshComponentWidget;
    delete componentLightWidget;
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

    connect(meshComponentWidget->ui->LoadMeshButton, SIGNAL(clicked()),this,SLOT(OnLoadMesh()));
    connect(meshComponentWidget->ui->DiffuseLoadButton, SIGNAL(clicked()),this, SLOT(OnLoadDiffuse()));
    connect(meshComponentWidget->ui->NormalLoadButton, SIGNAL(clicked()), this, SLOT(OnLoadNormal()));
    connect(meshComponentWidget->ui->HeightMapLoad, SIGNAL(clicked()), this, SLOT(OnLoadHeightMap()));

    connect(meshComponentWidget->ui->DiffuseMirroredCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnChangeDiffuseMirrored()));
    connect(meshComponentWidget->ui->NormalMirroredCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnChangeNormalMirrored()));
    connect(meshComponentWidget->ui->ParallaxMirroredCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnChangeParallaxMirrored()));

    connect(meshComponentWidget->ui->DiffuseEnabledCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnEnableDiffuse()));
    connect(meshComponentWidget->ui->NormalEnabledCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnEnableNormal()));

    connect(meshComponentWidget->ui->ParallaxEnabledCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnEnableParallax()));

    connect(meshComponentWidget->ui->DiffuseXTilling, SIGNAL(valueChanged(double)),this, SLOT(OnChangeDiffuseTilling()));
    connect(meshComponentWidget->ui->DiffuseYTilling, SIGNAL(valueChanged(double)),this, SLOT(OnChangeDiffuseTilling()));

    connect(meshComponentWidget->ui->HeightScale, SIGNAL(valueChanged(double)), this, SLOT(OnHeightScaleChanged()));

    //Light

    connect(componentLightWidget->ui->ColorPicker, SIGNAL(clicked()), this, SLOT(OnChangeLightColor()));
}

void Inspector::OnChangeNormalMirrored()
{
    meshComponentWidget->OnChangeNormalMirrored(meshComponentWidget->ui->NormalMirroredCheckBox->isChecked());
    w->update();
    UpdateContent();
}
void Inspector::OnEnableDiffuse()
{
    meshComponentWidget->OnEnableDiffuse(meshComponentWidget->ui->DiffuseEnabledCheckBox->isChecked());
    w->update();
    UpdateContent();
}

void Inspector::OnEnableNormal()
{
    meshComponentWidget->OnEnableNormal(meshComponentWidget->ui->NormalEnabledCheckBox->isChecked());
    UpdateContent();
}

void Inspector::OnEnableParallax()
{
    meshComponentWidget->OnEnableParallax(meshComponentWidget->ui->ParallaxEnabledCheckBox->isChecked());
    UpdateContent();
}

void Inspector::OnChangeDiffuseTilling()
{
    QVector2D vec(meshComponentWidget->ui->DiffuseXTilling->value(), meshComponentWidget->ui->DiffuseYTilling->value());
    meshComponentWidget->OnChangeMaterialTilling(vec);
    std::cout<<"Change tilling"<<std::endl;
}

void Inspector::OnHeightScaleChanged()
{
    meshComponentWidget->OnChangeHeightScale(meshComponentWidget->ui->HeightScale->value());
}
void Inspector::OnChangeDiffuseMirrored()
{
    meshComponentWidget->OnChangeDiffuseMirrored(meshComponentWidget->ui->DiffuseMirroredCheckBox->isChecked());
    UpdateContent();
}

void Inspector::OnChangeParallaxMirrored()
{
    meshComponentWidget->OnChangeHeightMapMirrored(meshComponentWidget->ui->ParallaxMirroredCheckBox->isChecked());
    UpdateContent();
}

void Inspector::OnChangeLightColor()
{
    componentLightWidget->OnChangeLightColor();
}
void Inspector::OnLoadHeightMap()
{
    meshComponentWidget->OnLoadHeightMap();
    UpdateContent();
}
void Inspector::OnAddComponent()
{
    if(selected!= nullptr)
    {

        if(comboBox->currentText() == "Mesh Component")
        {
            Mesh* m = new Mesh(selected);
            MeshComponent* component = new MeshComponent(m, selected, ComponentType::mesh);
            selected->OnAddComponent(component);

        }
        else if(comboBox->currentText() == "Light Component")
        {
            componentlight* component = new componentlight(selected, ComponentType::Light);
            selected->OnAddComponent(component);
        }

        //other components

        UpdateContent();

    }
}

void Inspector::OnLoadNormal()
{
    meshComponentWidget->OnLoadNormal();
    UpdateContent();
}

void Inspector::OnLoadDiffuse()
{
    meshComponentWidget->OnLoadDiffuse();
    UpdateContent();
}

void Inspector::OnLoadMesh()
{
    meshComponentWidget->OnLoadMesh();
    UpdateContent();
}


void Inspector::SetAllInvisible()
{
    transformComponentWidget->setVisible(false);
    meshComponentWidget->setVisible(false);
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

void Inspector::UpdateMeshComponent()
{
    BlockSignals(true);
    meshComponentWidget->ui->DiffuseXTilling->setValue(meshComponentWidget->GetComponent()->mesh->GetMaterial()->GetTilling().x());
    meshComponentWidget->ui->DiffuseYTilling->setValue(meshComponentWidget->GetComponent()->mesh->GetMaterial()->GetTilling().y());
    meshComponentWidget->ui->HeightScale->setValue(meshComponentWidget->GetComponent()->mesh->GetMaterial()->GetHeightScale());
    BlockSignals(false);
}

void Inspector::UpdateLightComponent()
{
    BlockSignals(true);
    //Do stuff
    BlockSignals(false);
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

    meshComponentWidget->ui->DiffuseXTilling->blockSignals(b);
    meshComponentWidget->ui->DiffuseYTilling->blockSignals(b);
    meshComponentWidget->ui->HeightScale->blockSignals(b);

    componentLightWidget->ui->Ambient->blockSignals(b);
    componentLightWidget->ui->Diffuse->blockSignals(b);
    componentLightWidget->ui->Specular->blockSignals(b);
    componentLightWidget->ui->CutOff->blockSignals(b);
    componentLightWidget->ui->OuterCutOff->blockSignals(b);
    componentLightWidget->ui->LightType->blockSignals(b);
}
void Inspector::UpdateContent()
{
    //Set all invisible before checking for available components
    transformComponentWidget->setVisible(false);
    meshComponentWidget->setVisible(false);
    componentLightWidget->setVisible(false);

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
                break;
            case ComponentType::mesh:
                meshComponentWidget->setVisible(true);
                meshComponentWidget->SetMeshComponent(static_cast<MeshComponent*>(*it));
                meshComponentWidget->ui->PathText->setText(static_cast<MeshComponent*>(*it)->mesh->GetPath());
                meshComponentWidget->SetPreviewTextures();
                UpdateMeshComponent();
                meshComponentWidget->Update();
                break;
            case ComponentType::Light:
                componentLightWidget->setVisible(true);
                componentLightWidget->SetComponent(static_cast<componentlight*>(*it));
                UpdateLightComponent();
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

}
