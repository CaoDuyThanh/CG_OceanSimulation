#include <QtGui/QMouseEvent>
#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setMouseTracking(true);
    ocean = new OceanHandler(16, 0.003, 32, 9.8, Vector2s(32.0, 32.0));
    t = 0.0;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

GLWidget::~GLWidget() {
    if (ocean) {
        delete ocean;
    }
}

void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    QColor black = QColor(255, 0, 0, 255);
    qglClearColor(black);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 3.0 / 4.0, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 10, 10,
              0, 0, 0,
              0, 1, 0);

    qglClearColor(QColor(0,0,0,128));
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    t += 1.0 / 30;

    ocean->evaluateWavesFFT(t);
    ocean->Render();
    QGLWidget::swapBuffers();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
    printf("%d, %d\n", event->x(), event->y());
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}

void GLWidget::update() {
    this->paintGL();
}
