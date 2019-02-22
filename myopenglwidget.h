#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>

class myopenglwidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit myopenglwidget(QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:

public slots:
};

#endif // MYOPENGLWIDGET_H
