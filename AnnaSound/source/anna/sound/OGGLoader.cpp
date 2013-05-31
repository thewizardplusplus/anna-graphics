#include "OGGLoader.h"
#include "../utils/allocation.h"
#include <vorbis/vorbisfile.h>

using namespace anna::sound;

size_t read(void* data, size_t size, size_t number_bytes, void* data_source) {
	std::istream* stream = reinterpret_cast<std::istream*>(data_source);
	stream->read(static_cast<char*>(data), size * number_bytes);
	return stream->gcount();
}

int seek(void* data_source, ogg_int64_t offset, int whence) {
	std::istream* stream = reinterpret_cast<std::istream*>(data_source);
	std::ios_base::seekdir position;
	switch (whence) {
	case SEEK_SET:
		position = std::ios::beg;
		break;
	case SEEK_CUR:
		position = std::ios::cur;
		break;
	case SEEK_END:
		position = std::ios::end;
		break;
	default:
		return -1;
	}
	stream->clear();
	stream->seekg(static_cast<std::streamoff>(offset), position);
	if (!stream->fail()) {
		return 0;
	} else {
		return -1;
	}
}

long tell(void* data_source) {
	std::istream* stream = reinterpret_cast<std::istream*>(data_source);
	return stream->tellg();
}

int close(void* data_source) {
	(void)data_source;
	return 0;
}

std::list<std::string> OGGLoader::getSupportedFormats(void) const {
	std::list<std::string> formats;
	try {
		formats.push_back("OGG");
	} catch (std::bad_alloc&) {}
	return formats;
}

PCMData OGGLoader::load(std::istream& source)
	throw(exceptions::ReadingException)
{
	OggVorbis_File vorbis_file;
	ov_callbacks callbacks;
	callbacks.read_func = read;
	callbacks.seek_func = seek;
	callbacks.tell_func = tell;
	callbacks.close_func = close;
	int result = ov_open_callbacks(&source, &vorbis_file, NULL, 0, callbacks);
	if (result < 0) {
		throw exceptions::ReadingException("anna::sound: unable to load sound "
			"data - it's not OGG stream.");
	}

	vorbis_info* vorbis_info = ov_info(&vorbis_file, -1);
	int size = ov_pcm_total(&vorbis_file, -1) * 2 * vorbis_info->channels;
	if (size < 0) {
		throw exceptions::ReadingException("anna::sound: unable to load sound "
			"data - size of OGG data isn't correct.");
	}
	PCMData::TYPE type = PCMData::MONO;
	if (vorbis_info->channels > 1) {
		type = PCMData::STEREO;
	}
	int frequency = vorbis_info->rate;

	char* data = NULL;
	ARRAY_ALLOCATION(char, data, size);

	long shift = 0;
	int section = 0;
	while (shift < size) {
		long number_bytes = ov_read(&vorbis_file, data + shift, size - shift, 0,
			2, 1, &section);
		if (number_bytes > 0) {
			shift += number_bytes;
		} else if (number_bytes == 0) {
			break;
		} else {
			throw exceptions::ReadingException("anna::sound: unable to load "
				"sound data - error reading from the OGG stream.");
		}
	}

	ov_clear(&vorbis_file);

	return PCMData(data, shift, type, PCMData::BIT_16, frequency);
}

void OGGLoader::unload(const PCMData& data) {
	const char* byte_data = static_cast<const char*>(data.getData());
	delete[] byte_data;
	byte_data = NULL;
}
