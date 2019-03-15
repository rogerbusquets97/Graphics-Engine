#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspector.h"
#include "hierarchy_widget.h"
#include "scene.h"
#include "gameobject.h"

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

    inspector = new Inspector();
    uiMainWindow->InspectorDock->setWidget(inspector);

    hierarchy = new Hierarchy_Widget();
    uiMainWindow->HierachyDock->setWidget(hierarchy);

    tabifyDockWidget(uiMainWindow->RenderingDock, uiMainWindow->InspectorDock);

    // Connect Actions' triggered() signals to some slots
    connect(uiMainWindow->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), this, SLOT(exitProject()));

    scene.push_back(5);
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiRendering;
    delete inspector;
    delete hierarchy;
    delete currScene;
}

void MainWindow::OnAddObject(GameObject* obj)
{
    currScene->OnAddObject(obj);
}

void MainWindow::openProject()
{
    std::cout<< "Save Project" << std::endl;

    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", "", tr("Scene Name (*.txt);; All Files (*)"));
    QSettings settings(fileName, QSettings::IniFormat);
}
void MainWindow::saveProject()
{
    std::cout<< "Save Project" << std::endl;

    QString fileName = QFileDialog::getSaveFileName(this, "Save Scene");

    QSettings settings(fileName, QSettings::IniFormat);

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
