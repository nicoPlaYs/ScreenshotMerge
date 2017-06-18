TARGET = ScreenshotMerge

win32{
    QMAKE_TARGET_PRODUCT = "Screenshot Merge"
    QMAKE_TARGET_DESCRIPTION = "Screenshot Merge"
    QMAKE_TARGET_COMPANY = "Nicolas Fostier"
    QMAKE_TARGET_COPYRIGHT = "Nicolas Fostier"
    RC_ICONS += res/images/app.ico
}

macx{
    QMAKE_FRAMEWORK_BUNDLE_NAME = "Screenshot Merge"
    ICON = res/images/app.icns
}

TEMPLATE = app

VERSION = 1.7.1



QT +=   core gui \
        widgets \
        network

win32::LIBS += -luser32

SOURCES +=  src/screenshot.cpp \
            src/main.cpp \
            src/windows/mainwindow.cpp \
            src/windows/cropwindow.cpp \
            src/windows/settingswindow.cpp \
            src/windows/editwindow.cpp \
            src/windows/uploadwindow.cpp \
            src/shapes/polyline.cpp \
            src/shapes/straightline.cpp \
            src/shapes/frame.cpp \
            src/upload.cpp \
            src/save.cpp \
    src/shapes/shape.cpp \
    src/updatechecker.cpp

HEADERS  += include/screenshot.h \
            include/windows/mainwindow.h \
            include/windows/cropwindow.h \
            include/windows/settingswindow.h \
            include/windows/editwindow.h \
            include/windows/uploadwindow.h \
            include/shapes/polyline.h \
            include/shapes/straightline.h \
            include/shapes/frame.h \
            include/upload.h \
            include/save.h \
            include/apikeys.h \
    include/shapes/shape.h \
    include/updatechecker.h

RESOURCES += res/images.qrc \
             res/lang.qrc

TRANSLATIONS = res/lang/screenshotmerge_fr.ts



DEFINES += QT_DEPRECATED_WARNINGS
