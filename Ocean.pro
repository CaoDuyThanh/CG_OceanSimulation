TEMPLATE = app
TARGET = something
QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

LIBS += \
    -lglut \
    -lGL \
    -lGLU

SOURCES += \
    main.cpp \
    oceanhandler.cpp \
    complex.cpp \
    vector2s.cpp \
    vector3s.cpp \
    complexvectornormal.cpp \
    vertexocean.cpp \
    glwidget.cpp \
    ffthandler.cpp

HEADERS += \
    oceanhandler.h \
    complex.h \
    vector2s.h \
    vector3s.h \
    complexvectornormal.h \
    vertexocean.h \
    glwidget.h \
    ffthandler.h
