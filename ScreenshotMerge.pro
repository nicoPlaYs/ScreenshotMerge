QT += widgets

SOURCES += src/main.cpp \
        src/mainwindow.cpp \
        src/screenshot.cpp \
        src/cropwindow.cpp \
        src/viewerwindow.cpp \
    src/settingswindow.cpp

HEADERS  += include/mainwindow.h \
        include/screenshot.h \
        include/cropwindow.h \
        include/viewerwindow.h \
    include/settingswindow.h

RESOURCES += res/images.qrc \
        res/lang.qrc

TRANSLATIONS = res/lang/screenshotmerge_fr.ts

VERSION = 1.1

RC_ICONS += res/images/app.ico
QMAKE_TARGET_PRODUCT = "Screenshot Merge"
QMAKE_TARGET_COMPANY = "Nicolas Fostier"
QMAKE_TARGET_COPYRIGHT = "Nicolas Fostier"
QMAKE_TARGET_DESCRIPTION = "Take screenshots, crop them and merge them"
