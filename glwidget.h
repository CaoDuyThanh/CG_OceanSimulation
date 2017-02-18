#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <GL/glu.h>
#include "oceanhandler.h"

class GLWidget : public QGLWidget {
    Q_OBJECT
private:
    OceanHandler* ocean;
    double t;
    int count = 0;

public:
    GLWidget(QWidget* parent = NULL);
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

protected slots:
    void update();
};

#endif // GLWIDGET_H
