QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH+= $$PWD/external/glm/

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp\
    camera.cpp\
    camerathird.cpp\
    utils.cpp\
    matrix.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h\
    camera.h\
    camerathird.h\
    utils.h\
    matrix.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target
