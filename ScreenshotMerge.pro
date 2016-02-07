QT += widgets

SOURCES += src/main.cpp \
        src/mainwindow.cpp \
    src/screenshot.cpp \
    src/cropwindow.cpp \
    src/viewerwindow.cpp

HEADERS  += include/mainwindow.h \
    include/screenshot.h \
    include/cropwindow.h \
    include/viewerwindow.h

RESOURCES += \
    res/images.qrc

RC_ICONS += res/images/app.ico
