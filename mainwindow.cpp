#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "hierarchy_widget.h"
#include "scene.h"
#include "gameobject.h"
#include "shapewidget.h"
#include "inspector.h"

#include <Qlist>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow),
    uiRendering(new Ui::Rendering)
{
    QCoreApplication::setApplicationName("Antimonored Engine");

    currScene = new Scene();
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    uiMainWindow->setupUi(this);

    QWidget *renderingWidget = new QWidget();
    uiRendering->setupUi(renderingWidget);
    renderingWidget->show();

    uiMainWindow->RenderingDock->setWidget(renderingWidget);

    uiMainWindow->RenderingDock->setFloating(false);

    hierarchy = new Hierarchy_Widget();
    uiMainWindow->HierachyDock->setWidget(hierarchy);

    inspector = new Inspector();
    uiMainWindow->InspectorDock->setWidget(inspector);

    shape_widget = new ShapeWidget();
    uiMainWindow->RenderingDock->setWidget(shape_widget);
    uiMainWindow->RenderingDock->setFloating(false);

    tabifyDockWidget(uiMainWindow->RenderingDock, uiMainWindow->InspectorDock);

    // Connect Actions' triggered() signals to some slots
    connect(uiMainWindow->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), this, SLOT(exitProject()));


}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiRendering;
    delete hierarchy;
    delete currScene;
    delete inspector;
    delete shape_widget;
}

void MainWindow::OnAddObject(GameObject* obj)
{
    if (obj != nullptr)
    {
        currScene->OnAddObject(obj);
        shape_widget->AddComponentShape(obj->GetComponentShape());
    }
}

void MainWindow::openProject()
{
    std::cout<< "Load Project" << std::endl;

    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", "", tr(""));
    QSettings settings(fileName, QSettings::IniFormat);

    int size = settings.beginReadArray("Game Objects");

    if (size > 0)
    {
        DeleteMainWindowScene();

        uint objcount = 0;

        for(int i = 0; i < size; ++i, ++objcount)
        {
          settings.setArrayIndex(i);
          GameObject* go = new GameObject(nullptr, settings.value("name").toString());
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

    settings.beginWriteArray("Game Objects", currScene->GetGameObjects().size());

    for(int i = 0; i < currScene->GetGameObjects().size(); ++i, ++objcount)
    {
        settings.setArrayIndex(i);
        settings.setValue(QString("name"), currScene->GetGameObjects()[i]->GetName());
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
}
