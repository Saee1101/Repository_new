QT       += core gui sql network
QT += charts serialport serialbus printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

SOURCES += \
    Button_TivanEX.cpp \
    Dialog_.cpp \
    Dialog_ChangePassWord.cpp \
    Dialog_EnterPassWord.cpp \
    Report.cpp \
    Warning_Dialog.cpp \
    halconqtwindow.cpp \
    main.cpp \
    MainWindow.cpp \
    newplotclass.cpp \
    pieview.cpp \
    qcustomplot.cpp \
    widget.cpp

HEADERS += \
    Button_TivanEX.h \
    Dialog_.h \
    Dialog_ChangePassWord.h \
    Dialog_EnterPassWord.h \
    MainWindow.h \
    Report.h \
    Warning_Dialog.h \
    halconqtwindow.h \
    newplotclass.h \
    pieview.h \
    qcustomplot.h \
    widget.h

FORMS += \
    Dialog_ChangePassWord.ui \
    Dialog_EnterPassWord.ui \
    MainWindow.ui \
    Report.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    PNG.qrc \
    Resource.qrc

# win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/BusinessLogic/release/ -lBusinessLogic
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/BusinessLogic/debug/ -lBusinessLogic
# INCLUDEPATH += $$PWD/../BusinessLogic
# DEPENDPATH += $$PWD/../BusinessLogic

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Business_logic/release/ -lBusiness_logic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Business_logic/debug/ -lBusiness_logic

INCLUDEPATH += $$PWD/../Business_logic
DEPENDPATH += $$PWD/../Business_logic


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Connections/release/ -lConnections
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Connections/debug/ -lConnections

INCLUDEPATH += $$PWD/../Connections
DEPENDPATH += $$PWD/../Connections

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Entities/release/ -lEntities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Entities/debug/ -lEntities

INCLUDEPATH += $$PWD/../Entities
DEPENDPATH += $$PWD/../Entities

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
