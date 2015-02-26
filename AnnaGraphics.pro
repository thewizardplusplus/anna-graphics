# общие настройки
TARGET = AnnaGraphics
#TEMPLATE = lib
#CONFIG += staticlib
CONFIG += console
CONFIG += warn_on
CONFIG -= qt

# файлы проекта
HEADERS += \
	source/thewizardplusplus/utils/os.h \
	source/thewizardplusplus/utils/ConsoleMessageType.h \
	source/thewizardplusplus/utils/Console.h \
	source/thewizardplusplus/utils/ByteOrderTesterHelper.h \
	source/thewizardplusplus/utils/ByteOrderTester.h \
	source/thewizardplusplus/utils/ByteOrder.h \
	source/thewizardplusplus/utils/Converter.h \
	source/thewizardplusplus/utils/Path.h \
	source/thewizardplusplus/anna/maths/Vector4D.h \
	source/thewizardplusplus/anna/maths/Vector3D.h \
	source/thewizardplusplus/anna/maths/Vector2D.h \
	source/thewizardplusplus/anna/maths/Maths.h \
	source/thewizardplusplus/anna/graphics/exceptions/GraphicsException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToOpenObjectFileException.h \
	source/thewizardplusplus/anna/graphics/exceptions/InvalidFormatOfObjectFileException.h \
	source/thewizardplusplus/anna/graphics/exceptions/ConnectWithXServerException.h \
	source/thewizardplusplus/anna/graphics/exceptions/FailedToChoosePixelFormatException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToRegisterWindowClassException.h \
	source/thewizardplusplus/anna/graphics/exceptions/CannotRunInFullscreenModeException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToCreateWindowException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToCreateDeviceContextException.h \
	source/thewizardplusplus/anna/graphics/exceptions/CannotFindAppropriatePixelFormatException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToSetPixelFormatException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToCreateOpenGlRenderingContextException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToActivateOpenGlRenderingContextException.h \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToRegisterRawInputDeviceException.h \
	source/thewizardplusplus/anna/graphics/Vertex.h \
	source/thewizardplusplus/anna/graphics/TransparentType.h \
	source/thewizardplusplus/anna/graphics/Texture.h \
	source/thewizardplusplus/anna/graphics/Material.h \
	source/thewizardplusplus/anna/graphics/Mesh.h \
	source/thewizardplusplus/anna/graphics/Object.h \
	source/thewizardplusplus/anna/graphics/CubeMesh.h \
	source/thewizardplusplus/anna/graphics/PlaneMesh.h \
	source/thewizardplusplus/anna/graphics/Skybox.h \
	source/thewizardplusplus/anna/graphics/CameraType.h \
	source/thewizardplusplus/anna/graphics/Camera.h \
	source/thewizardplusplus/anna/graphics/DistanceToMeshComparator.h \
	source/thewizardplusplus/anna/graphics/AnimateState.h \
	source/thewizardplusplus/anna/graphics/AnimateKey.h \
	source/thewizardplusplus/anna/graphics/AnimateKeyType.h \
	source/thewizardplusplus/anna/graphics/AnimateTrack.h \
	source/thewizardplusplus/anna/graphics/AnimateObject.h \
	source/thewizardplusplus/anna/graphics/Window.h \
	source/thewizardplusplus/anna/graphics/KeyCode.h \
	source/thewizardplusplus/anna/graphics/ButtonCode.h \
	source/thewizardplusplus/anna/graphics/FogType.h \
	source/thewizardplusplus/anna/graphics/FogParameters.h \
	source/thewizardplusplus/anna/graphics/TextureData.h \
	source/thewizardplusplus/anna/graphics/TextureLoader.h \
	source/thewizardplusplus/anna/graphics/GraphicApi.h \
	source/thewizardplusplus/anna/graphics/OpenGlWindow.h \
	source/thewizardplusplus/anna/graphics/OpenGlGraphicApi.h \
	source/thewizardplusplus/anna/graphics/World.h \
	source/thewizardplusplus/anna/graphics/BmpTextureLoader.h
SOURCES += \
	source/thewizardplusplus/main.cpp \
	source/thewizardplusplus/utils/Console.cpp \
	source/thewizardplusplus/utils/ByteOrderTester.cpp \
	source/thewizardplusplus/utils/Path.cpp \
	source/thewizardplusplus/anna/maths/Maths.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/GraphicsException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToOpenObjectFileException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/InvalidFormatOfObjectFileException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/ConnectWithXServerException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/FailedToChoosePixelFormatException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToRegisterWindowClassException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/CannotRunInFullscreenModeException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToCreateWindowException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToCreateDeviceContextException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/CannotFindAppropriatePixelFormatException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToSetPixelFormatException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToCreateOpenGlRenderingContextException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToActivateOpenGlRenderingContextException.cpp \
	source/thewizardplusplus/anna/graphics/exceptions/UnableToRegisterRawInputDeviceException.cpp \
	source/thewizardplusplus/anna/graphics/Vertex.cpp \
	source/thewizardplusplus/anna/graphics/Texture.cpp \
	source/thewizardplusplus/anna/graphics/Material.cpp \
	source/thewizardplusplus/anna/graphics/Mesh.cpp \
	source/thewizardplusplus/anna/graphics/Object.cpp \
	source/thewizardplusplus/anna/graphics/CubeMesh.cpp \
	source/thewizardplusplus/anna/graphics/PlaneMesh.cpp \
	source/thewizardplusplus/anna/graphics/Skybox.cpp \
	source/thewizardplusplus/anna/graphics/Camera.cpp \
	source/thewizardplusplus/anna/graphics/DistanceToMeshComparator.cpp \
	source/thewizardplusplus/anna/graphics/AnimateKey.cpp \
	source/thewizardplusplus/anna/graphics/AnimateTrack.cpp \
	source/thewizardplusplus/anna/graphics/AnimateObject.cpp \
	source/thewizardplusplus/anna/graphics/Window.cpp \
	source/thewizardplusplus/anna/graphics/FogParameters.cpp \
	source/thewizardplusplus/anna/graphics/TextureData.cpp \
	source/thewizardplusplus/anna/graphics/TextureLoader.cpp \
	source/thewizardplusplus/anna/graphics/GraphicApi.cpp \
	source/thewizardplusplus/anna/graphics/OpenGlWindow.cpp \
	source/thewizardplusplus/anna/graphics/OpenGlGraphicApi.cpp \
	source/thewizardplusplus/anna/graphics/World.cpp \
	source/thewizardplusplus/anna/graphics/BmpTextureLoader.cpp

# флаги компилятора
unix | win32-g++ {
	QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
}
unix:LIBS += -lGL -lX11 -pthread
win32-g++ {
	DEFINES += RAW_INPUT

	LIBS += -lgdi32 -lopengl32
	QMAKE_CXXFLAGS += -U__STRICT_ANSI__
}
