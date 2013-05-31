HEADERS += \
	source/anna/sound/AudioDevice.h \
	source/anna/sound/OpenALAudioDevice.h \
	source/anna/sound/AudioDeviceCreator.h \
	source/anna/sound/OpenALAudioDeviceCreator.h \
	source/anna/sound/Listener.h \
	source/anna/sound/OpenALListener.h \
	source/anna/sound/version.h \
	source/anna/maths/version.h \
	source/anna/maths/Vector3D.h \
	source/anna/sound/Source.h \
	source/anna/sound/OpenALSource.h \
	source/anna/sound/Buffer.h \
	source/anna/sound/OpenALBuffer.h \
	source/anna/sound/PCMData.h \
	source/anna/sound/Loader.h \
	source/anna/sound/LoaderCreator.h \
	source/anna/sound/OGGLoader.h \
	source/anna/sound/OGGLoaderCreator.h \
	source/anna/utils/utils.h \
	source/anna/utils/allocation.h \
	source/anna/sound/PCMDataManager.h \
	source/anna/sound/Sound.h \
	source/anna/sound/SoundManager.h \
	source/anna/exceptions/SettingException.h \
	source/anna/exceptions/ReadingException.h \
	source/anna/exceptions/CreationException.h
SOURCES += \
	source/main.cpp \
	source/anna/sound/OpenALAudioDevice.cpp \
	source/anna/sound/OpenALAudioDeviceCreator.cpp \
	source/anna/sound/OpenALListener.cpp \
	source/anna/sound/OpenALSource.cpp \
	source/anna/sound/OpenALBuffer.cpp \
	source/anna/sound/OGGLoaderCreator.cpp \
	source/anna/sound/OGGLoader.cpp \
	source/anna/sound/PCMDataManager.cpp \
	source/anna/sound/SoundManager.cpp
OTHER_FILES += \
	docs/to_do.txt
unix {
	LIBS += -lopenal -lvorbisfile
}
