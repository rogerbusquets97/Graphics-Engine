#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy_widget.h"
#include "scene.h"
#include "gameobject.h"
#include "inspector.h"

#include <Qlist>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include "transform.h"
#include "mesh.h"
#include "meshcomponent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("Antimonored Engine");

    uiMainWindow->setupUi(this);

    currScene = new Scene();
    //uiMainWindow->openGLWidget->scene = currScene;
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    uiMainWindow->RenderingDock_2->setFloating(false);

    hierarchy = new Hierarchy_Widget();
    uiMainWindow->HierarchyDock->setWidget(hierarchy);

    inspector = new Inspector();
    uiMainWindow->InspectorDock_2->setWidget(inspector);

    // Connect Actions' triggered() signals to some slots
    connect(uiMainWindow->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), this, SLOT(exitProject()));



    running = true;

}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete hierarchy;
    delete currScene;
    delete inspector;
}

void MainWindow::OnAddObject(GameObject* obj)
{
    if (obj != nullptr)
    {
        // Estoy hay que arreglarlo
        currScene->OnAddObject(obj);
    }
}

void MainWindow::openProject()
{
    std::cout<< "Load Project" << std::endl;

    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", "", tr(""));

    QSettings settings(fileName, QSettings::IniFormat);

    int gos_size = settings.beginReadArray("GameObjects");

    if (gos_size > 0)
    {
        DeleteMainWindowScene();

        uint objcount = 0;

        for(int obj_i = 0; obj_i < gos_size; ++obj_i, ++objcount)
        {
          settings.setArrayIndex(obj_i);
          GameObject* go = new GameObject(nullptr, settings.value("name").toString());

          go->transform->SetPosition(settings.value("positionX").toFloat(),settings.value("positionY").toFloat(),settings.value("positionZ").toFloat());
          go->transform->SetScale(settings.value("scaleX").toFloat(),settings.value("scaleY").toFloat(),settings.value("scaleZ").toFloat());
          go->transform->SetRotation(settings.value("rotationX").toFloat(),settings.value("rotationY").toFloat(),settings.value("rotationZ").toFloat());

          int comps_size = settings.beginReadArray("Components");

          if(comps_size > 0)
          {
              for (int comp_i = 0; comp_i < comps_size; ++comp_i)
              {
                  settings.setArrayIndex(comp_i);
                  uint comp_sorter = settings.value("ComponentType").toUInt();
                  switch (comp_sorter)
                  {
                        case (uint)Shape:
                        {
                            break;
                        }
                        case (uint) Trans:
                        {
                            Transform* trans = new Transform(go, Trans);
                            trans->SetPosition(settings.value("positionX").toFloat(),settings.value("positionY").toFloat(),settings.value("positionZ").toFloat());
                            trans->SetScale(settings.value("scaleX").toFloat(),settings.value("scaleY").toFloat(),settings.value("scaleZ").toFloat());
                            trans->SetRotation(settings.value("rotationX").toFloat(),settings.value("rotationY").toFloat(),settings.value("rotationZ").toFloat());

                            go->OnAddComponent(trans);

                            break;
                        }
                        case (uint) Component_Unknow:
                        {
                            break;
                        }
                  }
              }
              settings.endArray();
          }
          else {
               std::cout<< "WARNING, RECEIVED OBJECT WITH NO COMPONENTS" << std::endl;
          }

          currScene->OnAddObject(go);
          hierarchy->AddGameObject(go);
        }
        settings.endArray();

        std::cout<< "Loaded " << objcount <<  " objects." << std::endl;
      }
    else
    {
        std::cout<< "File was empty. Unable to load objects." << std::endl;
    }

}
void MainWindow::saveProject()
{
    std::cout<< "Save Project" << std::endl;

    QString fileName = QFileDialog::getSaveFileName(this, "Save Scene");

    QSettings settings(fileName, QSettings::IniFormat);

    uint objcount = 0;

    settings.beginWriteArray("GameObjects", currScene->GetGameObjects().size());

    for(int i = 0; i < currScene->GetGameObjects().size(); ++i, ++objcount)
    {
        settings.setArrayIndex(i);
        settings.setValue(QString("name"), currScene->GetGameObjects()[i]->GetName());


        // Main Parent Transform
         Transform* trans = (Transform*) currScene->GetGameObjects()[i]->transform;
         settings.setValue("positionX", (int)trans->GetPosition().x);
         settings.setValue("positionY", (int)trans->GetPosition().y);
         settings.setValue("positionZ", (int)trans->GetPosition().z);

         settings.setValue("scaleX",  (int)trans->GetScale().x);
         settings.setValue("scaleY", (int) trans->GetScale().y);
         settings.setValue("scaleZ",  (int)trans->GetScale().z);

         settings.setValue("rotationX",  (int)trans->GetRotation().x);
         settings.setValue("rotationY",  (int)trans->GetRotation().y);
         settings.setValue("rotationZ", (int) trans->GetRotation().z);

         settings.beginWriteArray("Components", currScene->GetGameObjects()[i]->components.size());

        for(int c_i = 0; c_i < currScene->GetGameObjects()[i]->components.size(); ++c_i)
        {
            settings.setArrayIndex(c_i);


            switch (currScene->GetGameObjects()[i]->components[c_i]->GetType())
            {
                case Shape:
                {
                    break;
                }
                case Trans:
                {
                     settings.setValue("ComponentType", Trans);
                     Transform* trans = (Transform*) currScene->GetGameObjects()[i]->components[c_i];
                     settings.setValue("positionX", (int)trans->GetPosition().x);
                     settings.setValue("positionY", (int)trans->GetPosition().y);
                     settings.setValue("positionZ",(int) trans->GetPosition().z);

                     settings.setValue("scaleX",  (int)trans->GetScale().x);
                     settings.setValue("scaleY", (int) trans->GetScale().y);
                     settings.setValue("scaleZ", (int) trans->GetScale().z);

                     settings.setValue("rotationX",  (int)trans->GetRotation().x);
                     settings.setValue("rotationY",  (int)trans->GetRotation().y);
                     settings.setValue("rotationZ", (int) trans->GetRotation().z);
                    break;
                }
                default:
                {
                    settings.setValue("ComponentType", Component_Unknow);
                    break;
                }
            }
        }
        settings.endArray();

    }
    settings.endArray();

    std::cout<< "Saved " << objcount <<  " objects." << std::endl;

    settings.setValue("AntiMonoRed, all rights reserved", "Roger Busquets & Josep Huguet - 2019");
}

void MainWindow::exitProject()
{
    std::cout<< "Exit Project" << std::endl;
    QMessageBox::StandardButton button = QMessageBox::question(
                this, "ExtApplication", "Do you want to exit the application without saving the project?");
    if (button == QMessageBox::Yes)
    {
        std::cout << "Exit without saving changes" << std::endl;
        qApp->quit();
        running = false;
    }
    else
    {
        std::cout<<"Cancel exit"<<std::endl;
    }
}

Scene* MainWindow::GetCurrScene()const
{
    return currScene;
}

void MainWindow::DeleteMainWindowScene()
{
    hierarchy->ClearHierarchy();
    currScene->ClearScene();
    //shape_widget->ClearShapesToRender();
}
