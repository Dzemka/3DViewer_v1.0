TEMPLATE = app
TARGET = 3DViewer1.0

QT += core gui openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CFLAGS += -Wall -Wextra -Werror

INCLUDEPATH += $$PWD/include $$PWD/src

SOURCES += \
    src/addValidators.cpp \
    src/buttons.cpp \
    src/changeSettings.cpp \
    src/imageview.cpp \
    src/initializeDataObject.cpp \
    src/initializeTransformation.cpp \
    src/keyboardEvents.cpp \
    src/loadUploadSettings.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mouseEvents.cpp \
    src/openFile.cpp \
    src/paint.cpp \
    src/parser/clean.c \
    src/parser/ft_split.c \
    src/parser/list_utils.c \
    src/parser/parse_value.c \
    src/parser/parser.c \
    src/parser/set_values.c \
    src/parser/utils.c \
    src/saveMedia.cpp \
    src/setElementsInterface.cpp \
    src/setLanguage.cpp \
    src/transformation.c

HEADERS += \
    include/imageview.h \
    include/mainwindow.h \
    include/viewer.h \
    include/gif.h \

FORMS += \
    mainwindow.ui

RESOURCES = resource/resource.qrc

TRANSLATIONS += \
    resource/3DViewer_ru_RU.ts

CONFIG += lrelease
CONFIG += embed_translations

OBJECTS_DIR = ./obj
DESTDIR = ../
