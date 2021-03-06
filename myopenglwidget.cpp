
#include "myopenglwidget.h"
#include "vertex.h"
#include "submesh.h"
#include "mesh.h"
#include "scene.h"
#include "meshcomponent.h"

#include <iostream>
#include <QOpenGLDebugLogger>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>

#include "mainwindow.h"
#include "transform.h"
#include <QQuaternion>

#define PI 3.14159265359

#pragma comment( lib, "OpenGL32.lib" )

QOpenGLFunctions_3_3_Core *gl = nullptr;

myopenglwidget::myopenglwidget(QWidget *parent)
    : QOpenGLWidget (parent)
{
   // setMinimumSize(QSize(256, 256));
    setMouseTracking(true);

    connect(&timer, SIGNAL(timeout()),this,SLOT(Frame()));
    if(format().swapInterval() == -1)
    {
        qDebug("Swap Buffers at v_blank not available: refresh at approx 60fps.");
        timer.setInterval(17);
    }
    else
    {
        qInfo("V_blank synchronization available");
        timer.setInterval(0);
    }

    input = new Input();
    camera = new Camera();

    interaction = new Interaction();
    interaction->input = input;
    interaction->camera = camera;

    timer.start();
}

void myopenglwidget::Frame()
{
    interaction->Update();
    update();
    input->postUpdate();

}

void myopenglwidget::keyPressEvent(QKeyEvent *event)
{
    input->keyPressedEvent(event);
}

void myopenglwidget::keyReleaseEvent(QKeyEvent *event)
{
    input->keyReleasedEvent(event);
}

void myopenglwidget::mousePressEvent(QMouseEvent *event)
{
    input->mousePressedEvent(event);
}

void myopenglwidget::mouseMoveEvent(QMouseEvent *event)
{
    input->mouseMoveEvent(event);
}

void myopenglwidget::mouseReleaseEvent(QMouseEvent *event)
{
    input->mouseReleaseEvent(event);
}

void myopenglwidget::enterEvent(QEvent *)
{
    grabKeyboard();
}

void myopenglwidget::leaveEvent(QEvent *)
{
    releaseKeyboard();
}

void myopenglwidget::wheelEvent(QWheelEvent* event)
{
    input->mouseWheelEvent(event);
}

myopenglwidget::~myopenglwidget()
{
    makeCurrent();
    finalizeGL();
    delete input;
    delete camera;
    delete interaction;
}

void myopenglwidget::InitGBuffer()
{
    gl->glGenFramebuffers(1, &gBuffer);
    gl->glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    //Position
    gl->glGenTextures(1, &gPosition);
    gl->glBindTexture(GL_TEXTURE_2D, gPosition);
    gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    //Nomal
    gl->glGenTextures(1, &gNormal);
    gl->glBindTexture(GL_TEXTURE_2D, gNormal);
    gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    //Color
    gl->glGenTextures(1, &gAlbedo);
   gl->glBindTexture(GL_TEXTURE_2D, gAlbedo);
   gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width(), this->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
   gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);


    unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    gl->glDrawBuffers(3, attachments);

    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->width(), this->height());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    program.bind();
    gl->glUniform1i(glGetUniformLocation(program.programId(),"gPosition"),0);
    gl->glUniform1i(glGetUniformLocation(program.programId(),"gNormal"),1);
    gl->glUniform1i(glGetUniformLocation(program.programId(),"gAlbedo"),2);

}

void myopenglwidget::initializeGL()
{
    gl = this;
    initializeOpenGLFunctions();

    //Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()),
            this, SLOT(finalizeGL()));

    if(context()->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
    {
        QOpenGLDebugLogger* logger = new QOpenGLDebugLogger(this);
        logger->initialize();

        connect(logger, SIGNAL(messageLogged(const QOpenGLDebugMessage &)),
                this, SLOT(handleLoggedMessage(const QOpenGLDebugMessage &)));
        logger->startLogging();
    }

    gl->glEnable(GL_DEPTH_TEST);

    //Shaders
    //Lightning shaders
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/lightning.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/lightning.frag");
    program.link();

    // Geometry shaders
    geometryProgram.create();
    geometryProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/geometry.vert");
    geometryProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/geometry.frag");
    program.link();

    InitGBuffer();
}

void myopenglwidget::handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    std::cout << debugMessage.severity() << "!!: "
              << debugMessage.message().toStdString() << std::endl;
}

void myopenglwidget::resizeGL(int w, int h)
{
    this->resize(w, h);
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    //GBuffer
    gl->glDeleteTextures(1,&gPosition);
    gl->glDeleteTextures(1, &gNormal);
    gl->glDeleteTextures(1, &gAlbedo);
   InitGBuffer();
}

void myopenglwidget::paintGL()
{
    //gl->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    UpdateMeshes();

    gl->glClearDepth(1.0f);
    gl->glEnable(GL_DEPTH_TEST);
    gl->glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gl->glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    UseGeometryShader();
    DrawMeshes();
    QOpenGLFramebufferObject::bindDefault();

    //Use lightning shader
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //gl->glEnable(GL_BLEND);
    //gl->glBlendFunc(GL_ONE,GL_ONE);
    //gl->glDepthMask(false);
    UseLightningShader();
    //Render quad
    RenderQuad();

    gl->glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
    gl->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    gl->glBlitFramebuffer(0,0, width(), height(), 0,0,width(), height(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void myopenglwidget::finalizeGL()
{
    std::cout << "finalize()" << std::endl;
}

void myopenglwidget::showInfo()
{
    std::cout << "OpenGL version:" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl << std::endl;

    std::cout << "OpenGL renderer:" << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl << std::endl;

    std::cout << "OpenGL vendor:" << std::endl;
    std::cout << glGetString(GL_VENDOR) << std::endl << std::endl;

    std::cout << "OpenGL GLSL version:" << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

    std::cout << "OpenGL extensions:" << std::endl;
    GLint num_extensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
    for (int i = 0; i < num_extensions; ++i)
    {
        const unsigned char *str = glGetStringi(GL_EXTENSIONS, GLuint(i));
        std::cout << str << " ";
    }
    std::cout << std::endl;

    //Information about the surface format
    std::cout << context()->format().redBufferSize() << std::endl;
    std::cout << context()->format().greenBufferSize() << std::endl;
    std::cout << context()->format().blueBufferSize() << std::endl;
    std::cout << context()->format().alphaBufferSize() << std::endl;
    std::cout << context()->format().depthBufferSize() << std::endl;
}

void myopenglwidget::UpdateMeshes()
{
    QList<Mesh*> Scenemeshes;
    w->GetCurrScene()->GetSceneMeshes(Scenemeshes);
    for(QList<Mesh*>::iterator it = Scenemeshes.begin(); it!= Scenemeshes.end(); ++it)
    {
        if((*it)->needsUpdate)
        {
            (*it)->update();
            (*it)->needsUpdate = false;
        }
    }
}

void myopenglwidget::ResizeTextures()
{

    gl->glDeleteTextures(1,&gPosition);
    gl->glDeleteTextures(1, &gNormal);
    gl->glDeleteTextures(1, &gAlbedo);


    gl->glGenTextures(1, &gPosition);
    gl->glBindTexture(GL_TEXTURE_2D, gPosition);
    gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    //Nomal
    gl->glGenTextures(1, &gNormal);
    gl->glBindTexture(GL_TEXTURE_2D, gNormal);
    gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    //Color
    gl->glGenTextures(1, &gAlbedo);
   gl->glBindTexture(GL_TEXTURE_2D, gAlbedo);
   gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width(), this->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
   gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);



}

void myopenglwidget::RenderQuad()
{
    if(quadVAO == 0)
    {
        float quadVertices[] = {
                    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                };

        gl->glGenVertexArrays(1,&quadVAO);
        gl->glGenBuffers(1, &quadVBO);
        gl->glBindVertexArray(quadVAO);
        gl->glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        gl->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        gl->glEnableVertexAttribArray(0);
        gl->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5 *sizeof(float), (void*)0);
        gl->glEnableVertexAttribArray(1);
        gl->glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5 *sizeof(float), (void*)(3 * sizeof (float)));
    }

    gl->glBindVertexArray(quadVAO);
    gl->glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
    gl->glBindVertexArray(0);
}
void myopenglwidget::DrawMeshes()
{
    QList<Mesh*> Scenemeshes;
    w->GetCurrScene()->GetSceneMeshes(Scenemeshes);

    for(QList<Mesh*>::iterator it = Scenemeshes.begin(); it!= Scenemeshes.end(); ++it)
    {
        if((*it)->GetMaterial()->IsDiffuseActive())
        {
            if((*it)->GetMaterial()->GetDiffuse()!= nullptr)
            {
                diffuse = gl->glGetUniformLocation(geometryProgram.programId(), "diffuseTexture");
                gl->glActiveTexture(GL_TEXTURE0);
                gl->glBindTexture(GL_TEXTURE_2D, (*it)->GetMaterial()->GetDiffuse()->textureId());
                gl->glUniform1i(diffuse, 0);

                diffuseEnabled = true;
            }
            else
            {
                diffuseEnabled = false;
            }
        }
        else
        {
            diffuseEnabled = false;
        }

        if((*it)->GetMaterial()->IsNormalActive())
        {
            if((*it)->GetMaterial()->GetNormalMap()!= nullptr)
            {
                normal = gl->glGetUniformLocation(geometryProgram.programId(), "normalMap");
                gl->glActiveTexture(GL_TEXTURE1);
                gl->glBindTexture(GL_TEXTURE_2D, (*it)->GetMaterial()->GetNormalMap()->textureId());
                gl->glUniform1i(normal, 1);

                normalEnabled = true;
            }
            else
            {
                normalEnabled = false;
            }
        }
        else
        {
            normalEnabled = false;
        }

        if((*it)->GetMaterial()->IsParallaxActive())
        {
            if((*it)->GetMaterial()->GetHeightMap() != nullptr)
            {
                GLuint parallax = gl->glGetUniformLocation(geometryProgram.programId(), "heightMap");
                gl->glActiveTexture(GL_TEXTURE2);
                gl->glBindTexture(GL_TEXTURE_2D, (*it)->GetMaterial()->GetHeightMap()->textureId());
                gl->glUniform1i(parallax, 2);

                parallaxEnabled = true;
            }
            else
            {
                parallaxEnabled = false;
            }
        }
        else
        {
            parallaxEnabled = false;
        }


        if(diffuseEnabled)
            gl->glUniform1i(gl->glGetUniformLocation(geometryProgram.programId(), "diffuseEnabled"), 1);
        else
            gl->glUniform1i(gl->glGetUniformLocation(geometryProgram.programId(), "diffuseEnabled"), 0);

        if(normalEnabled)
            gl->glUniform1i(gl->glGetUniformLocation(geometryProgram.programId(), "normalEnabled"), 1);
        else
            gl->glUniform1i(gl->glGetUniformLocation(geometryProgram.programId(), "normalEnabled"), 0);
        if(parallaxEnabled)
            gl->glUniform1i(gl->glGetUniformLocation(geometryProgram.programId(), "parallaxEnabled"), 1);
        else
            gl->glUniform1i(gl->glGetUniformLocation(geometryProgram.programId(), "parallaxEnabled"), 0);

        QMatrix4x4 worldMatrix;
        worldMatrix.setToIdentity();

        if((*it)->GetParent()->GetTransorm() != nullptr)
        {
            Transform* trans = (*it)->GetParent()->GetTransorm();
            worldMatrix.translate(trans->GetPosition().x, trans->GetPosition().y, trans->GetPosition().z);
            worldMatrix.scale(trans->GetScale().x, trans->GetScale().y, trans->GetScale().z);
            worldMatrix.rotate(trans->GetRotation().x, QVector3D(1,0,0));
            worldMatrix.rotate(trans->GetRotation().y, QVector3D(0,1,0));
            worldMatrix.rotate(trans->GetRotation().z, QVector3D(0,0,1));
            //worldMatrix = worldMatrix.rotate(quat.toRotationMatrix());
        }

         geometryProgram.setUniformValue("modelMatrix", worldMatrix);
         geometryProgram.setUniformValue("tilling", (*it)->GetMaterial()->GetTilling());
         geometryProgram.setUniformValue("heightscale", (*it)->GetMaterial()->GetHeightScale());
        (*it)->draw();
    }
}

void myopenglwidget::UseGeometryShader()
{
    if(geometryProgram.bind())
    {
        camera->PrepareMatrices();
        // Camera transformation
        QVector3D eyePosition(5.0, 5.0, 10.0);
        QVector3D center(0.0, 0.0, 0.0);
        QVector3D up(0.0, 1.0, 0.0);
        camera->viewMatrix.lookAt(eyePosition, center, up);

        // Object transformation

        QMatrix4x4 worldMatrix;
        worldMatrix.setToIdentity();

        geometryProgram.setUniformValue("projectionMatrix", camera->projectionMatrix);
        geometryProgram.setUniformValue("viewMatrix", camera->viewMatrix);
        geometryProgram.setUniformValue("viewPos", camera->position);
        geometryProgram.setUniformValue("lightPos", QVector3D(0,0,1));
    }
}

void myopenglwidget::UseLightningShader()
{
    if(program.bind())
    {
        gl->glActiveTexture(GL_TEXTURE0);
        gl->glBindTexture(GL_TEXTURE_2D, gPosition);
        gl->glActiveTexture(GL_TEXTURE1);
        gl->glBindTexture(GL_TEXTURE_2D, gNormal);
        gl->glActiveTexture(GL_TEXTURE2);
        gl->glBindTexture(GL_TEXTURE_2D, gAlbedo);

        QVector<componentlight*> lights;
        w->GetCurrScene()->GetSceneLights(lights);

        QVector<componentlight*> DirectionalLights, PointLights, SpotLights;

        uint dir_count = 0, point_count = 0, spot_count= 0;
        for(QVector<componentlight*>::iterator it = lights.begin(); it!= lights.end(); ++it)
        {
            switch((*it)->GetLightType())
            {
                case LightType::DIRECTIONAL_LIGHT:
                    DirectionalLights.push_back((*it));
                    dir_count++;
                break;
                case LightType::POINT_LIGHT:
                    PointLights.push_back((*it));
                    point_count++;
                break;
                case LightType::SPOT_LIGHT:
                    SpotLights.push_back((*it));
                    spot_count++;
                break;
            }
        }

        program.setUniformValue("viewPos", camera->position.x(), camera->position.y(), camera->position.z());
        std::string str, str2;
        // Directional Lights

        program.setUniformValue("Directionals", dir_count);
        for (uint i = 0; i < dir_count; ++i)
        {

            str = "dirLights[" + std::to_string(i) + "].";

            // Position
            Transform* transform = DirectionalLights[i]->GetParent()->GetTransorm();
            str2 = str +"position";
            program.setUniformValue(str2.c_str(), transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);

            str2 = str +"direction";
            QQuaternion quat = QQuaternion::fromEulerAngles(transform->GetRotation().x, transform->GetRotation().y, transform->GetRotation().z);
            QVector3D dir = quat * QVector3D(0,0,1);
            program.setUniformValue(str2.c_str(), dir);

            str2= str + "ambient";
            program.setUniformValue(str2.c_str(),DirectionalLights[i]->GetAmbient());

            str2= str + "diffuse";
            program.setUniformValue(str2.c_str(),DirectionalLights[i]->GetDiffuse());

            str2= str + "specular";
            program.setUniformValue(str2.c_str(),DirectionalLights[i]->GetSpecular());

            str2= str + "color";
            program.setUniformValue(str2.c_str(), DirectionalLights[i]->GetRGBColor().r, DirectionalLights[i]->GetRGBColor().g, DirectionalLights[i]->GetRGBColor().b);
        }

         program.setUniformValue("Points", point_count);
        // Point Lights
        for (uint j = 0; j < point_count; j++)
        {
            str = "pointLights[" + std::to_string(j) + "].";

            // Position
            Transform* transform = PointLights[j]->GetParent()->GetTransorm();
            str2 = str +"position";
            program.setUniformValue(str2.c_str(), transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);

            str2= str + "ambient";
            program.setUniformValue(str2.c_str(),PointLights[j]->GetAmbient());

            str2= str + "diffuse";
            program.setUniformValue(str2.c_str(),PointLights[j]->GetDiffuse());

            str2= str + "specular";
            program.setUniformValue(str2.c_str(),PointLights[j]->GetSpecular());

            str2= str + "color";
            program.setUniformValue(str2.c_str(), PointLights[j]->GetRGBColor().r, PointLights[j]->GetRGBColor().g, PointLights[j]->GetRGBColor().b);
        }

        program.setUniformValue("Spots", spot_count);
        // Spot Lights

        for (uint k = 0; k < spot_count; k++)
        {
            str = "spotLights[" + std::to_string(k) + "].";

            // Position
            Transform* transform = SpotLights[k]->GetParent()->GetTransorm();
            str2 = str +"position";
            program.setUniformValue(str2.c_str(), transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);

            str2 = str +"direction";
            QQuaternion quat = QQuaternion::fromEulerAngles(transform->GetRotation().x, transform->GetRotation().y, transform->GetRotation().z);
            QVector3D dir = quat * QVector3D(0,0,1);
            program.setUniformValue(str2.c_str(), dir);

            str2= str + "ambient";
            program.setUniformValue(str2.c_str(),SpotLights[k]->GetAmbient());

            str2= str + "diffuse";
            program.setUniformValue(str2.c_str(),SpotLights[k]->GetDiffuse());

            str2= str + "specular";
            program.setUniformValue(str2.c_str(),SpotLights[k]->GetSpecular());

            str2= str + "color";
            program.setUniformValue(str2.c_str(), SpotLights[k]->GetRGBColor().r, SpotLights[k]->GetRGBColor().g, SpotLights[k]->GetRGBColor().b);

            str2= str+ "cutOff";
            program.setUniformValue(str2.c_str(),SpotLights[k]->GetCutOff());

            str2= str+ "outerCutOff";
            program.setUniformValue(str2.c_str(),SpotLights[k]->GetOuterCutOff());

        }

    }
}

void myopenglwidget::EnableVertexAttribArray(GLuint index)
{
    gl->glEnableVertexAttribArray(index);
}

void myopenglwidget::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
{
    gl->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}


