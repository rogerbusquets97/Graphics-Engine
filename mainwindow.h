#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
class Rendering;
}

class Inspector;
class Hierarchy_Widget;
class Scene;
class GameObject;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void OnAddObject(GameObject* obj);
    Scene* GetCurrScene()const;

private:
    Ui::MainWindow *uiMainWindow;
    Ui::Rendering *uiRendering;
    Inspector *inspector;
    Hierarchy_Widget* hierarchy;
    Scene* currScene;

public slots:
    void openProject();
    void saveProject();
    void exitProject();
};
extern MainWindow* w;

#endif // MAINWINDOW_H
