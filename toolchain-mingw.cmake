# this one is important
SET(CMAKE_SYSTEM_NAME Windows)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   mingw32-gcc)
SET(CMAKE_CXX_COMPILER mingw32-g++)

set(QT_WIN32_PREFIX /opt/qt-win-opensource-src-4.5.2)

set(CMAKE_FIND_ROOT_PATH /usr/mingw32/usr/lib /usr/mingw32/usr/include ${QT_WIN32_PREFIX} )

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(QT_X11_DIR /usr/bin)
set(QT_LIBRARY_DIR ${QT_WIN32_PREFIX}/lib)
set(QT_INCLUDE_DIR ${QT_WIN32_PREFIX}/include)
set(QT_MKSPECS_DIR ${QT_WIN32_PREFIX}/mkspecs)
set(QT_MOC_EXECUTABLE ${QT_X11_DIR}/moc)
set(QT_QMAKE_EXECUTABLE ${QT_X11_DIR}/qmake)
set(QT_UIC_EXECUTABLE ${QT_X11_DIR}/uic)
set(QT_LRELEASE_EXECUTABLE ${QT_X11_DIR}/lrelease)

set(QT_QTCORE_LIBRARY ${QT_WIN32_PREFIX}/lib/libQtCore4.a)
set(QT_QTCORE_INCLUDE_DIR ${QT_WIN32_PREFIX}/include/QtCore)

set(QT_QTGUI_LIBRARY ${QT_WIN32_PREFIX}/lib/libQtGui4.a)
set(QT_QTGUI_INCLUDE_DIR ${QT_WIN32_PREFIX}/include/QtGui)

set(QT_QTNETWORK_LIBRARY ${QT_WIN32_PREFIX}/lib/libQtNetwork4.a)
set(QT_QTNETWORK_INCLUDE_DIR ${QT_WIN32_PREFIX}/include/QtNetwork)

set(QT_QTOPENGL_LIBRARY ${QT_WIN32_PREFIX}/lib/libQtOpenGL4.a)
set(QT_QTOPENGL_INCLUDE_DIR ${QT_WIN32_PREFIX}/include/QtOpenGL)

set(QT_QTSCRIPT_LIBRARY ${QT_WIN32_PREFIX}/lib/libQtScript4.a)
set(QT_QTSCRIPT_INCLUDE_DIR ${QT_WIN32_PREFIX}/include/QtScript)

set(QT_QTXML_LIBRARY ${QT_WIN32_PREFIX}/lib/libQtXml4.a)
set(QT_QTXML_INCLUDE_DIR ${QT_WIN32_PREFIX}/include/QtXml)
