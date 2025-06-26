QT -= gui
QT += core sql
TEMPLATE = lib
DEFINES += ENTITIES_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entities.cpp \
    Repository.cpp

HEADERS += \
    BaseEntity.h \
    Entities_global.h \
    Entities.h \
    Repository.h \
    machineSetting.h \
    sample.h \
    statistics.h \
    user.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
