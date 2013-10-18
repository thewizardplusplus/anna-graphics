#!/bin/bash

# Copyright (c) thewizardplusplus 2013 All rights reserved
# Email: thewizardplusplus@yandex.ru.
# Site: http://thewizardplusplus.ru/.

if [[ -z $1 || -z $2 ]]
then
	echo "Using:"
	echo -e "\texceptions_class_generator.sh <namespaces_separated_by_::> <exception_class> [<base_class>]"

	exit 1
fi

namespaces=$(sed "s/::/ {\nnamespace /g" <<< $1)
number_of_namespaces=$(( $(tr -dc ':' <<< $1 | wc -c) / 2 + 1 ))
closing_namespaces_braces=$(perl -e "print \"}\n\" x $number_of_namespaces")

exception_class="$2Exception"
protecting_define=$(tr '[:lower:]' '[:upper:]' <<< $exception_class)"_H"

if [ ! -z $3 ]
then
	base_class="$3Exception"
	include="\"$base_class.h\""
else
	base_class="std::runtime_error"
	include="<stdexcept>"
fi

echo "#ifndef $protecting_define
#define $protecting_define

#include $include

namespace $namespaces {

class $exception_class : public $base_class {
public:
	$exception_class(...);
};

$closing_namespaces_braces
#endif" > "$exception_class.h"

echo "#include \"$exception_class.h\"

using namespace $1;

$exception_class::$exception_class(...) :
	$base_class(...)
{}" > "$exception_class.cpp"
