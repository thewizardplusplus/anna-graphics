# Copyright (c) 2013 thewizardplusplus, http://thewizardplusplus.ru/
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
#
# Copyright (c) 2013 thewizardplusplus, http://thewizardplusplus.ru/
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

bl_info = {
	"name": "Export to Anna Object (*.ao)",
	"author": "thewizardplusplus",
	"version": (1, 0),
	"blender": (2, 67, 0),
	"location": "File > Export > Anna Object (*.ao)",
	"description": "Export the active object to Anna Object (*.ao)",
	"warning": "",
	"wiki_url": "",
	"tracker_url": "",
	"category": "Import-Export"}

import bpy
import time
from bpy_extras.io_utils import ExportHelper

# export operator
class AnnaObjectExport(bpy.types.Operator, ExportHelper):
	""" Export the active object to Anna Object (*.ao). """

	bl_idname =    "export_mesh.ao"
	bl_label =     "Anna Object (*.ao)"
	filename_ext = ".ao"

	@classmethod
	def poll(cls, context):
		return context.active_object.type in { "MESH" }

	def execute(self, context):
		print("Start exported the active object to Anna Object (*.ao)...")
		start_time = time.time()
		filepath = bpy.path.ensure_ext(self.filepath, self.filename_ext)
		exported = self._export(context, filepath)
		if exported:
			print("Finished export in {0} seconds to \"{1}\".".format( time. \
				time() - start_time, filepath))
		else:
			print("Export failed.")

		return { "FINISHED" }

	def invoke(self, context, event):
		wm = context.window_manager
		if True:
			# file selector (will run self.execute())
			wm.fileselect_add(self)
			return { "RUNNING_MODAL" }
		elif True:
			# search the enum
			wm.invoke_search_popup(self)
			return { "RUNNING_MODAL" }
		elif False:
			# redo popup
			return wm.invoke_props_popup(self, event)
		elif False:
			return self.execute(context)

	def _export(self, context, filepath):
		object = bpy.context.active_object
		if not object:
			print("\tNo active object.")
			return False

		data = self._getObjectData(object)
		if not data:
			return False

		file = open(filepath, "w")
		file.write(data)
		file.close()
		return True

	def _getObjectData(self, object, data = ""):
		data = "Test."
		return data

# registration
def menu_func(self, context):
	self.layout.operator(AnnaObjectExport.bl_idname, text = "Anna Object " + \
		"(*.ao)")

def register():
	bpy.utils.register_module(__name__)
	bpy.types.INFO_MT_file_export.append(menu_func)

def unregister():
	bpy.utils.unregister_module(__name__)
	bpy.types.INFO_MT_file_export.remove(menu_func)

if __name__ == "__main__":
	register()
