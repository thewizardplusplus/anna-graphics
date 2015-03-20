#!/usr/bin/env bash

set -o errexit

readonly SKYBOX_SIZE="1024"
readonly PATH_TO_BSC_TOOL="/bsc/bsc.c"
readonly PATH_TO_TEST_TEXTURES_DIRECTORY="/../../data/textures"

readonly stars_data_archive_filename=`tempfile`".gz"
wget \
	-O $stars_data_archive_filename \
	http://tdc-www.harvard.edu/catalogs/bsc5.dat.gz

readonly stars_data_filename=`tempfile`".dat"
gzip -cd $stars_data_archive_filename > $stars_data_filename
rm $stars_data_archive_filename

readonly script_path=`dirname $0`
generator_code=`cat $script_path$PATH_TO_BSC_TOOL`
generator_code=`echo "$generator_code" | sed "s/^\(#define BOX_SIZE\) 2048$/\1 $SKYBOX_SIZE/"`
generator_code=`echo "$generator_code" | sed "s%^\(fp = fopen("'"'"\)\./bsc5\.dat\("'"'","'"'"r"'"'");\)$%\1$stars_data_filename\2%"`
generator_code=`echo "$generator_code" | sed "s%\([xyz]\)pos.pgm%$script_path$PATH_TO_TEST_TEXTURES_DIRECTORY/skybox_axis_\1_positive_direction.pgm%g"`
generator_code=`echo "$generator_code" | sed "s%\([xyz]\)neg.pgm%$script_path$PATH_TO_TEST_TEXTURES_DIRECTORY/skybox_axis_\1_negative_direction.pgm%g"`

readonly generator_code_filename=`tempfile`".c"
echo "$generator_code" > $generator_code_filename

readonly generator_filename=`tempfile`
gcc -o $generator_filename $generator_code_filename -lm
rm $generator_code_filename

$generator_filename
rm $stars_data_filename
rm $generator_filename

for texture_filename in `find $script_path$PATH_TO_TEST_TEXTURES_DIRECTORY -type f -name "*.pgm"`
do
	new_texture_filename=`echo $texture_filename | sed "s/\.pgm$/\.bmp/"`
	ppmtobmp -bpp 24 $texture_filename > $new_texture_filename

	rm $texture_filename
done
