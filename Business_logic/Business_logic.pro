QT += core sql serialport serialbus
QT -= gui

TEMPLATE = lib
DEFINES += BUSINESS_LOGIC_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Business_logic.cpp

HEADERS += \
    Business_logic_global.h \
    Business_logic.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Connections/release/ -lConnections
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Connections/debug/ -lConnections

INCLUDEPATH += $$PWD/../Connections
DEPENDPATH += $$PWD/../Connections

# # win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Entities/release/ -lEntities
# # else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Entities/debug/ -lEntities

# # INCLUDEPATH += $$PWD/../Entities
# # DEPENDPATH += $$PWD/../Entities

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







