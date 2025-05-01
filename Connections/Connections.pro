QT -= gui
QT += core serialport serialbus
TEMPLATE = lib
DEFINES += CONNECTIONS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Camera_Classes/available_cameras.cpp \
    Camera_Classes/camera_capture.cpp \
    Camera_Classes/camera_live.cpp \
    Camera_Classes/camera_parameter.cpp \
    Camera_Classes/zds_camera_parameter.cpp \
    Plc_Classes/acmotor.cpp \
    Plc_Classes/jack.cpp \
    Plc_Classes/plcdelta.cpp \
    Plc_Classes/plcmodbusconnect.cpp \
    Plc_Classes/plcmodbusrw.cpp \
    Plc_Classes/steppermotor.cpp \
    clinspection.cpp \
    fl1fl2ai/BottomDiameter.cpp \
    fl1fl2ai/CircleDiameter.cpp \
    fl1fl2ai/HelperClass.cpp \
    fl1fl2ai/OvalityMeasures.cpp \
    fl1fl2ai/Point.cpp \
    fl1fl2ai/TopDiameter.cpp \
    flai.cpp \
    flcalibration.cpp \
    flinspection.cpp \
    machine.cpp \
    machinemanager.cpp \
    machinesetting.cpp\
     Connections.cpp

HEADERS += \
    Camera_Classes/available_cameras.h \
    Camera_Classes/camera_capture.h \
    Camera_Classes/camera_live.h \
    Camera_Classes/camera_parameter.h \
    Camera_Classes/zds_camera_parameter.h \
    Connections_global.h \
    Plc_Classes/acmotor.h \
    Plc_Classes/jack.h \
    Plc_Classes/plcdelta.h \
    Plc_Classes/plcmodbusconnect.h \
    Plc_Classes/plcmodbusrw.h \
    Plc_Classes/steppermotor.h \
    clinspection.h \
    fl1fl2ai/BottomDiameter.h \
    fl1fl2ai/CircleDiameter.h \
    fl1fl2ai/Constants.h \
    fl1fl2ai/HelperClass.h \
    fl1fl2ai/OvalityMeasures.h \
    fl1fl2ai/Point.h \
    fl1fl2ai/TopDiameter.h \
    flai.h \
    flcalibration.h \
    flinspection.h \
    machine.h \
    machinemanager.h \
    machinesetting.h\
    Connections.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH   += "$$(HALCONROOT)/include"
INCLUDEPATH   += "$$(HALCONROOT)/include/halconcpp"

#libs
QMAKE_LIBDIR  += "$$(HALCONROOT)/lib/$$(HALCONARCH)"
unix:LIBS     += -lhalconcpp -lhalcon -lXext -lX11 -ldl -lpthread
win32:LIBS    += "$$(HALCONROOT)/lib/$$(HALCONARCH)/halconcpp.lib" \
                 "$$(HALCONROOT)/lib/$$(HALCONARCH)/halcon.lib"\
                 "$$(HALCONROOT)/lib/$$(HALCONARCH)/hdevenginecpp.lib"

win32: LIBS += -LC:/libreries/carpool-lib/lib/ -lcarpool

INCLUDEPATH += C:/libreries/carpool-lib/include
DEPENDPATH += C:/libreries/carpool-lib/include
