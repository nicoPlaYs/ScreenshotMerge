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

VERSION = 1.7.1



QT +=   widgets \
        network

win32::LIBS += -luser32

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
            src/save.cpp \
            src/checkforupdate.cpp

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
            include/apikeys.h \
            include/checkforupdate.h

RESOURCES += res/images.qrc \
             res/lang.qrc

TRANSLATIONS = res/lang/screenshotmerge_fr.ts
