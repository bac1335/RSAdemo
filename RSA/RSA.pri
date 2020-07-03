

# @projectName   RSAdemo
# @brief         本模块适用于MinGw编译器，msvc编译器需更新库

INCLUDEPATH += $$PWD/encrypt $$PWD/extra/gmp/include
LIBS += $$PWD/extra/gmp/lib/libgmp.a
LIBS += $$PWD/extra/gmp/lib/libgmpxx.a

win32: QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS -= -Zc:strictStrings
win32: QMAKE_CXXFLAGS -= -Zc:strictStrings

HEADERS += \
    $$PWD/encrypt/rsa.h \
    $$PWD/encrypt/rsa_simple.h \
    $$PWD/extra/gmp/include/gmp.h \
    $$PWD/extra/gmp/include/gmpxx.h

SOURCES += \
    $$PWD/encrypt/rsa.cpp \
    $$PWD/encrypt/rsa_simple.cpp

