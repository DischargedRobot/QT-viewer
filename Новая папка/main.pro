RESOURCES += images.qrc

HEADERS += main.h 
SOURCES += main.cpp


QT += widgets
QT += charts
qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/
INSTALLS += target

