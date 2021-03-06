QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/customerwidget.cpp \
    src/httprequest.cpp \
    src/loginwidget.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/salewidget.cpp \
    src/storessecity.cpp \
    src/storessecountry.cpp \
    src/storessecustomer.cpp \
    src/storesseentity.cpp \
    src/storesseproduct.cpp \
    src/storessesale.cpp \
    src/storessestate.cpp \
    src/storessewindow.cpp \

HEADERS += \
    src/customerwidget.h \
    src/httprequest.h \
    src/loginwidget.h \
    src/mainwindow.h \
    src/salewidget.h \
    src/storessecity.h \
    src/storessecountry.h \
    src/storessecustomer.h \
    src/storesseentity.h \
    src/storesseproduct.h \
    src/storessesale.h \
    src/storessestate.h \
    src/storessewindow.h \
    src/noteditableitemdelegate.h

FORMS += \
    src/customerwidget.ui \
    src/loginwidget.ui \
    src/mainwindow.ui \
    src/salewidget.ui

TRANSLATIONS += \
    i18n/Storesse_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
