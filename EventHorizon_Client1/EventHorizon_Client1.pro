TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"

SOURCES += \
        abstract.cpp \
        asteroid1.cpp \
        background.cpp \
        bonus.cpp \
        laser.cpp \
        main.cpp \
        spaceship_new.cpp

LIBS += -L"C:/SFML-2.5.1/lib"

CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    abstract.h \
    asteroid1.h \
    background.h \
    bonus.h \
    laser.h \
    spaceship_new.hpp
