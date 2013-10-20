#!/bin/bash

# Copyright (c) thewizardplusplus 2013 All rights reserved
# Email: thewizardplusplus@yandex.ru.
# Site: http://thewizardplusplus.ru/.
#
# Лицензия MIT
#
# Данная лицензия разрешает лицам, получившим копию данного программного
# обеспечения и сопутствующей документации (в дальнейшем именуемыми «Программное
# Обеспечение»), безвозмездно использовать Программное Обеспечение без
# ограничений, включая неограниченное право на использование, копирование,
# изменение, добавление, публикацию, распространение, сублицензирование и/или
# продажу копий Программного Обеспечения, также как и лицам, которым
# предоставляется данное Программное Обеспечение, при соблюдении следующих
# условий:
#
# Указанное выше уведомление об авторском праве и данные условия должны быть
# включены во все копии или значимые части данного Программного Обеспечения.
#
# ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
# ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ
# ГАРАНТИЯМИ ТОВАРНОЙ ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И
# ОТСУТСТВИЯ НАРУШЕНИЙ ПРАВ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ
# НЕСУТ ОТВЕТСТВЕННОСТИ ПО ИСКАМ О ВОЗМЕЩЕНИИ УЩЕРБА, УБЫТКОВ ИЛИ ДРУГИХ
# ТРЕБОВАНИЙ ПО ДЕЙСТВУЮЩИМ КОНТРАКТАМ, ДЕЛИКТАМ ИЛИ ИНОМУ, ВОЗНИКШИМ ИЗ,
# ИМЕЮЩИМ ПРИЧИНОЙ ИЛИ СВЯЗАННЫМ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ ИЛИ ИСПОЛЬЗОВАНИЕМ
# ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ ИЛИ ИНЫМИ ДЕЙСТВИЯМИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
#
# MIT license
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
