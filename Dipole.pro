QT       += core gui datavisualization

#LIBS += -LC:\Qt\6.1.3\gcc_64\lib\libQt6DataVisualization.prl -lopen132
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    interface.cpp \
    system.cpp \
    vector3D.cpp
    system.cpp

HEADERS += \
    interface.h \
    system.h \
    vector3D.h
    system.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
