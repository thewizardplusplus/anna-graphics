SOURCE_BASE = source/thewizardplusplus/
UTILS_SOURCE = $(SOURCE_BASE)utils/
ANNA_SOURCE = $(SOURCE_BASE)anna/
ANNA_GRAPHICS_SOURCE = $(ANNA_SOURCE)graphics/
ANNA_GRAPHICS_EXCEPTIONS_SOURCE = $(ANNA_GRAPHICS_SOURCE)exceptions/
OBJECTS = \
	$(UTILS_SOURCE)Console.o \
	$(UTILS_SOURCE)ByteOrderTester.o \
	$(UTILS_SOURCE)Path.o \
	$(ANNA_SOURCE)maths/Maths.o \
	$(ANNA_GRAPHICS_SOURCE)Vertex.o \
	$(ANNA_GRAPHICS_SOURCE)Texture.o \
	$(ANNA_GRAPHICS_SOURCE)Material.o \
	$(ANNA_GRAPHICS_SOURCE)Mesh.o \
	$(ANNA_GRAPHICS_SOURCE)Object.o \
	$(ANNA_GRAPHICS_SOURCE)CubeMesh.o \
	$(ANNA_GRAPHICS_SOURCE)PlaneMesh.o \
	$(ANNA_GRAPHICS_SOURCE)Skybox.o \
	$(ANNA_GRAPHICS_SOURCE)Camera.o \
	$(ANNA_GRAPHICS_SOURCE)DistanceToMeshComparator.o \
	$(ANNA_GRAPHICS_SOURCE)AnimateKey.o \
	$(ANNA_GRAPHICS_SOURCE)AnimateTrack.o \
	$(ANNA_GRAPHICS_SOURCE)AnimateObject.o \
	$(ANNA_GRAPHICS_SOURCE)Window.o \
	$(ANNA_GRAPHICS_SOURCE)FogParameters.o \
	$(ANNA_GRAPHICS_SOURCE)TextureData.o \
	$(ANNA_GRAPHICS_SOURCE)TextureLoader.o \
	$(ANNA_GRAPHICS_SOURCE)GraphicApi.o \
	$(ANNA_GRAPHICS_SOURCE)OpenGlWindow.o \
	$(ANNA_GRAPHICS_SOURCE)OpenGlGraphicApi.o \
	$(ANNA_GRAPHICS_SOURCE)World.o \
	$(ANNA_GRAPHICS_SOURCE)BmpTextureLoader.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)GraphicsException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToOpenObjectFileException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)InvalidFormatOfObjectFileException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)ConnectWithXServerException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)FailedToChoosePixelFormatException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToRegisterWindowClassException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)CannotRunInFullscreenModeException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToCreateWindowException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToCreateDeviceContextException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)CannotFindAppropriatePixelFormatException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToSetPixelFormatException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToCreateOpenGlRenderingContextException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToActivateOpenGlRenderingContextException.o \
	$(ANNA_GRAPHICS_EXCEPTIONS_SOURCE)UnableToRegisterRawInputDeviceException.o
BUILD = build/
BUILD_HEADERS = $(BUILD)headers/
BUILD_LIBRARIES = $(BUILD)libraries/anna/graphics/
DOCS = docs/
CXXFLAGS += -std=c++03 -Wpedantic -Wall -Wextra -O2

.PHONY: docs clean

main: $(OBJECTS)
	mkdir -p $(BUILD_LIBRARIES)
	$(AR) crs $(BUILD_LIBRARIES)libAnnaGraphics.a $(OBJECTS)

	$(RM) -r $(BUILD_HEADERS)
	mkdir -p $(BUILD_HEADERS)
	rsync -r --include="*/" --include="*.h" --exclude="*" $(SOURCE_BASE) $(BUILD_HEADERS)

docs:
	$(RM) -r $(DOCS)/html/
	doxygen $(DOCS)Doxyfile

clean:
	find . -name "*.o" -type f -delete
