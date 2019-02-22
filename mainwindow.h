#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
class Rendering;
}

class Inspector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *uiMainWindow;
    Ui::Rendering *uiRendering;
    Inspector *inspector;

public slots:
    void openProject();
    void saveProject();
    void exitProject();
};

#endif // MAINWINDOW_H
