QT += core gui widgets network

TEMPLATE = lib

CONFIG += c++17 console

DESTDIR = ../bin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../include
INCLUDEPATH += ../../PetAPI/include

DEPENDPATH += ../../PetAPI/include

CONFIG(debug, debug|release) {
	contains(QMAKE_HOST.arch, x86_64) {
		TARGET = PetGUI_x64d
		LIBS += -L$$PWD/../../PetAPI/bin -llibPetAPI_x64d
	} else {
		TARGET = PetGUI_x86d
		LIBS += -L$$PWD/../../PetAPI/bin -llibPetAPI_x86d
	}
} else:CONFIG(release, debug|release) {
	contains(QMAKE_HOST.arch, x86_64) {
		TARGET = PetGUI_x64
		LIBS += -L$$PWD/../../PetAPI/bin -llibPetAPI_x64
	} else {
		TARGET = PetGUI_x86
		LIBS += -L$$PWD/../../PetAPI/bin -llibPetAPI_x86
	}
}

SOURCES += ../src/Forms/MessengerWidget.cpp
SOURCES += ../src/Forms/PetClientWindow.cpp
SOURCES += ../src/Starter/FormStarter.cpp

HEADERS += ../include/Forms/MessengerWidget.h
HEADERS += ../include/Forms/PetClientWindow.h
HEADERS += ../include/Starter/FormStarter.h

FORMS += ../ui/PetClientWindow.ui
FORMS += ../ui/MessengerWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
