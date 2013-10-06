# общие настройки
CONFIG += console
CONFIG += warn_on
CONFIG -= qt

# файлы внешних библиотек
win32 {
	INCLUDEPATH += ./../release/includes/
	LIBS += -L./../release/libs/ -lAnnaGraphics
}

# файлы проекта
SOURCES += \
	main.cpp

# флаги компилятора
unix | win32-g++ {
	QMAKE_CXXFLAGS += -std=c++98 -pedantic -Wall -W -O2
}
unix {
	LIBS += -lGL
}
win32-g++ {
	LIBS += -lgdi32 -lopengl32
	QMAKE_CXXFLAGS += -U__STRICT_ANSI__
}
