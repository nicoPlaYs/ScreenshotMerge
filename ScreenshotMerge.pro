QT += widgets \
    network

SOURCES +=  src/screenshot.cpp \
        src/main.cpp \
        src/windows/mainwindow.cpp \
        src/windows/cropwindow.cpp \
        src/windows/settingswindow.cpp \
        src/windows/editwindow.cpp \
        src/windows/uploadwindow.cpp \
        src/drawings/drawing.cpp \
        src/drawings/polyline.cpp \
        src/drawings/straightline.cpp \
        src/drawings/frame.cpp \
    src/upload.cpp \
    src/save.cpp

HEADERS  += include/screenshot.h \
        include/windows/mainwindow.h \
        include/windows/cropwindow.h \
        include/windows/settingswindow.h \
        include/windows/editwindow.h \
        include/windows/uploadwindow.h \
        include/drawings/drawing.h \
        include/drawings/polyline.h \
        include/drawings/straightline.h \
        include/drawings/frame.h \
    include/upload.h \
    include/save.h \
    include/apikeys.h

RESOURCES += res/images.qrc \
        res/lang.qrc

TRANSLATIONS = res/lang/screenshotmerge_fr.ts

VERSION = 1.5.1

RC_ICONS += res/images/app.ico
QMAKE_TARGET_PRODUCT = "Screenshot Merge"
QMAKE_TARGET_COMPANY = "Nicolas Fostier"
QMAKE_TARGET_COPYRIGHT = "Nicolas Fostier"
QMAKE_TARGET_DESCRIPTION = "Take screenshots, crop them and merge them"

win32:LIBS += -luser32
