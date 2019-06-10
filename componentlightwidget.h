#ifndef COMPONENTLIGHTWIDGET_H
#define COMPONENTLIGHTWIDGET_H

#include <QWidget>
#include <componentlight.h>

namespace Ui {
class ComponentLightWidget;
}

class ComponentLightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentLightWidget(QWidget *parent = nullptr);
    ~ComponentLightWidget();
    Ui::ComponentLightWidget *ui;
    inline componentlight* GetComponent()const{return ComponentLight;}
    inline void SetComponent(componentlight* c){ComponentLight = c;}

    void OnChangeLightColor();
    void OnChangeLightType(LightType t);
    void OnChangeLightDiffuse(float d);
    void OnChangeLightAmbient(float a);
    void OnChangeLightSpecular(float s);
    void OnChangeLightCutOff(float c);
    void OnChangeLightOutterCutOff(float c);
private:
   componentlight* ComponentLight;
};

#endif // COMPONENTLIGHTWIDGET_H
