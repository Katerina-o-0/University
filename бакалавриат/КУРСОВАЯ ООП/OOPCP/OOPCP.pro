QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actor.cpp \
    admin.cpp \
    billboard.cpp \
    buyticket.cpp \
    comment.cpp \
    concert.cpp \
    feedback.cpp \
    listforactor.cpp \
    listforconcert.cpp \
    listforfeedback.cpp \
    listforplay.cpp \
    listforticket.cpp \
    main.cpp \
    mainwindow.cpp \
    play.cpp \
    revenue.cpp \
    ticket.cpp

HEADERS += \
    actor.h \
    admin.h \
    billboard.h \
    buyticket.h \
    comment.h \
    concert.h \
    feedback.h \
    listforactor.h \
    listforconcert.h \
    listforfeedback.h \
    listforplay.h \
    listforticket.h \
    mainwindow.h \
    play.h \
    revenue.h \
    ticket.h

FORMS += \
    admin.ui \
    billboard.ui \
    buyticket.ui \
    comment.ui \
    mainwindow.ui \
    revenue.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
