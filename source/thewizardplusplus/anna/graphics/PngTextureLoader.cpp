#include "PngTextureLoader.h"
#include "../../utils/Console.h"
#include <png.h>
#include <fstream>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

static void ReadPngData(png_struct* png, unsigned char* data, size_t length) {
	std::istream* stream = static_cast<std::istream*>(png_get_io_ptr(png));
	stream->read(reinterpret_cast<char*>(data), length);
}

TextureLoader::StringList PngTextureLoader::getSupportedFormats(void) const {
	StringList formats;
	formats.push_back("PNG");

	return formats;
}

TextureData PngTextureLoader::load(const std::string& filename) {
	std::ifstream file;
	file.open(filename.c_str());
	if (!file.is_open()) {
		Console::error() << "Error: unable to open texture file \"" << filename
			<< "\".";
		return TextureData();
	}

	unsigned char header[PNG_HEADER_SIZE];
	file.read(reinterpret_cast<char*>(header), PNG_HEADER_SIZE);
	if (!file.good()) {
		Console::error() << "Error: unable to read header of texture.";
		return TextureData();
	}
	int not_png = png_sig_cmp(header, 0, PNG_HEADER_SIZE);
	if (not_png) {
		Console::error() << "Error: texture is not PNG.";
		return TextureData();
	}

	png_struct* png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
		NULL);
	if (png == NULL) {
		Console::error() << "Error: unable to load texture.";
		return TextureData();
	}

	png_infop info = png_create_info_struct(png);
	if (info == NULL) {
		Console::error() << "Error: unable to load texture.";
		png_destroy_read_struct(&png, NULL, NULL);
		return TextureData();
	}

	png_infop end_info = png_create_info_struct(png);
	if (end_info == NULL) {
		Console::error() << "Error: unable to load texture.";
		png_destroy_read_struct(&png, &info, NULL);
		return TextureData();
	}

	char*           data = NULL;
	unsigned char** rows = NULL;

	if (setjmp(png_jmpbuf(png))) {
		Console::error() << "Error: unable to load texture.";
		delete[] data;
		delete[] rows;
		png_destroy_read_struct(&png, &info, &end_info);
		return TextureData();
	}

	png_set_read_fn(png, static_cast<void*>(&file), ReadPngData);

	png_set_sig_bytes(png, PNG_HEADER_SIZE);

	png_read_info(png, info);

	unsigned long width =              png_get_image_width(png, info);
	unsigned long height =             png_get_image_height(png, info);
	unsigned long bit_depth =          png_get_bit_depth(png, info);
	unsigned long number_of_channels = png_get_channels(png, info);
	unsigned long color_type =         png_get_color_type(png, info);
	bool transparent =                 false;

	switch (color_type) {
		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(png);
			number_of_channels = 3;
			break;
		case PNG_COLOR_TYPE_GRAY:
			if (bit_depth < 8) {
				png_set_expand_gray_1_2_4_to_8(png);
			}
			bit_depth = 8;
			break;
		case PNG_COLOR_TYPE_RGBA:
			transparent = true;
			break;
		default:
			break;
	}

	if (png_get_valid(png, info, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png);
		number_of_channels += 1;
	}

	if (bit_depth == 16) {
		png_set_strip_16(png);
	}

	rows = new unsigned char*[height];
	const unsigned int stride = width * bit_depth * number_of_channels / 8;
	data = new char[stride * height];

	for (size_t i = 0; i < height; i++) {
		unsigned long row = (height - i - 1) * stride;
		rows[i] = reinterpret_cast<unsigned char*>(data) + row;
	}

	png_read_image(png, rows);

	return TextureData(data, Vector2D<size_t>(width, height), transparent);
}

void PngTextureLoader::free(const TextureData& data) {
	const char* byte_data = static_cast<const char*>(data.getData());
	delete[] byte_data;
	byte_data = NULL;
}
