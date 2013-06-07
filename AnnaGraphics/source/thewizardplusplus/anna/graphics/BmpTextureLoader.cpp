#include "BmpTextureLoader.h"
#include "../../utils/Console.h"
#include "../maths/Vector4D.h"
#include "../../utils/ByteOrderTester.h"
#include <fstream>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

TextureLoader::StringList BmpTextureLoader::getSupportedFormats(void) const {
	StringList formats;
	formats.push_back("BMP");

	return formats;
}

TextureData BmpTextureLoader::load(const std::string& filename) {
	std::ifstream file;
	file.open(filename.c_str(), std::ios_base::in | std::ios_base::binary);
	if (!file.is_open()) {
		Console::error() << "Error: unable to open texture file \"" << filename
			<< "\".";
		return TextureData();
	}

	file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::
		ifstream::badbit);
	try {
		size_t mark = readWord(file);
		if (mark != 0x4d42) {
			Console::error() << "Error: texture file \"" << filename << "\" "
				"has not BMP format.";
			return TextureData();
		}

		file.seekg(4 + 2 + 2, std::ios_base::cur);
		size_t data_offset = readDoubleWord(file);

		file.seekg(4, std::ios_base::cur);
		size_t width = readLong(file);
		size_t height = readLong(file);

		file.seekg(2, std::ios_base::cur);
		size_t bits = readWord(file);
		if (bits != 24 && bits != 32) {
			Console::error() << "Error: texture file \"" << filename << "\" "
				"has not supported value of bits on pixel.";
			return TextureData();
		}
		bool transparent = bits == 32;

		if (readDoubleWord(file) != 0) {
			Console::error() << "Error: texture file \"" << filename << "\" "
				"has not supported compression.";
			return TextureData();
		}

		size_t data_size = readDoubleWord(file);
		if (data_size == 0) {
			data_size = (width * (!transparent ? 3 : 4) + width % 4 ) * height;
		}

		file.seekg(data_offset, std::ios_base::beg);
		char* data = new char[data_size];
		for (size_t i = 0; i < data_size; !transparent ? i += 3 : i += 4) {
			data[i + 2] = readByte(file);
			data[i + 1] = readByte(file);
			data[i] = readByte(file);
			if (transparent) {
				data[i + 3] = readByte(file);
			}
		}

		return TextureData(data, Vector2D<size_t>(width, height), transparent);
	} catch (const std::ifstream::failure& exception) {
		Console::error() << "Error: unable to read texture file \"" << filename
			<< "\".";
		return TextureData();
	}
}

void BmpTextureLoader::free(TextureData &data) {
	delete[] static_cast<const char*>(data.getData());
	data.reset();
}

unsigned char BmpTextureLoader::readByte(std::ifstream& in) const {
	char byte = 0;
	in.get(byte);

	return byte;
}

unsigned int BmpTextureLoader::readWord(std::ifstream& in) const {
	char buffer[WORD_SIZE] = {0};
	in.read(buffer, WORD_SIZE);

	ByteOrder::Types byte_order = ByteOrderTester::test();
	switch (byte_order) {
		case ByteOrder::LITTLE_ENDIAN:
			return buffer[0] | buffer[1] << 8;
		case ByteOrder::BIG_ENDIAN: {
			return buffer[1] << 8 | buffer[0];
		}
		default:
			return 0;
	}
}

unsigned long BmpTextureLoader::readDoubleWord(std::ifstream& in) const {
	char buffer[DOUBLE_WORD_SIZE] = {0};
	in.read(buffer, DOUBLE_WORD_SIZE);

	ByteOrder::Types byte_order = ByteOrderTester::test();
	switch (byte_order) {
		case ByteOrder::LITTLE_ENDIAN:
			return buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] <<
				24;
		case ByteOrder::BIG_ENDIAN: {
			return buffer[3] << 24 | buffer[2] << 16 | buffer[1] << 8 | buffer[
				0];
		}
		default:
			return 0;
	}
}

long BmpTextureLoader::readLong(std::ifstream& in) const {
	char buffer[LONG_SIZE] = {0};
	in.read(buffer, LONG_SIZE);

	ByteOrder::Types byte_order = ByteOrderTester::test();
	switch (byte_order) {
		case ByteOrder::LITTLE_ENDIAN:
			return buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] <<
				24;
		case ByteOrder::BIG_ENDIAN: {
			return buffer[3] << 24 | buffer[2] << 16 | buffer[1] << 8 | buffer[
				0];
		}
		default:
			return 0;
	}
}
