TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"

SOURCES += \
        ../EventHorizon_Client1/abstract.cpp \
        ../EventHorizon_Client1/asteroid1.cpp \
        ../EventHorizon_Client1/background.cpp \
        ../EventHorizon_Client1/bonus.cpp \
        ../EventHorizon_Client1/laser.cpp \
        ../EventHorizon_Client1/main.cpp \
        spaceship_new.cpp

LIBS += -L"C:/SFML-2.5.1/lib"

CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    ../EventHorizon_Client1/abstract.h \
    ../EventHorizon_Client1/asteroid1.h \
    ../EventHorizon_Client1/background.h \
    ../EventHorizon_Client1/bonus.h \
    ../EventHorizon_Client1/laser.h \
    spaceship_new.hpp
