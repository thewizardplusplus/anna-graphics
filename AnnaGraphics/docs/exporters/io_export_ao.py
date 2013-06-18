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
from bpy_extras.io_utils import ExportHelper
from bpy.props import *
import time
import platform

class InvalidObjectDataError(Exception):
	pass

class ErrorDialogOperator(bpy.types.Operator):
	bl_idname = "error.dialog"
	bl_label =  "Error!"
	message =   StringProperty()

	def execute(self, context):
		self.report({ "INFO" }, self.message)
		return { "FINISHED" }

	def invoke(self, context, event):
		return context.window_manager.invoke_popup(self, width = 320, height = \
			240)

	def draw(self, context):
		layout = self.layout
		layout.label(text = "Error!", icon = "ERROR")
		layout.label(self.message)

class Key:
	index_of_mesh =  None
	frame =          None
	type =           None
	transformation = None

	def __init__(self, index_of_mesh, frame, type, transformation):
		self.index_of_mesh =  index_of_mesh
		self.frame =          frame
		self.type =           type
		self.transformation = transformation

class AnnaObjectExport(bpy.types.Operator, ExportHelper):
	""" Export the active object to Anna Object (*.ao). """

	bl_idname =        "export_mesh.ao"
	bl_label =         "Anna Object (*.ao)"
	filename_ext =     ".ao"
	export_animation = BoolProperty(name = "Export animation", description = \
		"Export animation data", default = True)

	@classmethod
	def poll(cls, context):
		return context.active_object.type in { "MESH" }

	def execute(self, context):
		print("\nStart exported the active object to Anna Object (*.ao)...")
		start_time = time.time()
		filepath = bpy.path.ensure_ext(self.filepath, self.filename_ext)
		exported = self._export(filepath, self.properties.export_animation)
		if exported:
			print("Finished export in {0} seconds to \"{1}\".\n".format(time. \
				time() - start_time, filepath))
		else:
			print("Export failed.\n")

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

	def _export(self, filepath, export_animation):
		object = bpy.context.active_object
		if not object:
			print("\tNo active object.")
			return False

		data = ""
		try:
			data = self._getObjectData(object, export_animation)
		except InvalidObjectDataError as exception:
			message = str(exception)

			message_for_dialog = message.replace("\tError: ", "")
			message_for_dialog = message_for_dialog.capitalize()
			bpy.ops.error.dialog("INVOKE_DEFAULT", message = message_for_dialog)

			print(message)
			return False

		file = open(filepath, "w")
		file.write(data)
		file.close()

		return True

	def _getObjectData(self, object, export_animation, data = "", number = 0, \
		animation = []):
		is_main_parent = data == "" and number == 0 and animation == []

		data, animation = self._getMeshData(object, export_animation, data, \
			number, animation)
		for child in object.children:
			data, number, animation = self._getObjectData(child, \
				export_animation, data, number + 1, animation)

		if not is_main_parent:
			return data, number, animation
		else:
			begin_of_data = "object:\n"
			begin_of_data += "\tmeshes:\n"
			begin_of_data += "\t\tnumber: " + str(number + 1) + "\n"

			end_of_data = "\tanimation_keys:\n"
			end_of_data += "\t\tnumber: " + str(len(animation)) + "\n"
			for key in animation:
				end_of_data += "\t\tkey:\n"
				end_of_data += "\t\t\tindex_of_mesh: " + str(key. \
					index_of_mesh) + "\n"
				end_of_data += "\t\t\tframe: " + str(key.frame) + "\n"
				end_of_data += "\t\t\ttype: " + str(key.type) + "\n"
				end_of_data += "\t\t\ttransformation: " + str(key. \
					transformation[0]) + " " + str(key.transformation[1]) + \
					" " + str(key.transformation[2]) + "\n"

			data = begin_of_data + data + end_of_data
			return data

	def _getMeshData(self, object, export_animation, data, number, animation):
		name = object.name
		if object.rotation_euler.order != "XYZ":
			raise InvalidObjectDataError("\tError: invalid rotation order of " \
				+ "the object \"" + name + "\" (must be \"XYZ\").")
		material = object.active_material
		if not material:
			raise InvalidObjectDataError("\tError: the object \"" + name + \
				"\" hasn't material.")
		use_transparency = material.use_transparency
		transparency_method = material.transparency_method
		if use_transparency and (transparency_method != "MASK" and \
			transparency_method != "Z_TRANSPARENCY"):
			raise InvalidObjectDataError("\tError: the object \"" + name + \
				"\" has invalid transparency type (must by \"Mask\" or \"Z " + \
				"Transparency\").")
		mesh = object.data
		if not mesh.uv_textures:
			raise InvalidObjectDataError("\tError: the object \"" + name + \
				"\" hasn't uv-data.")

		data += "\t\tmesh:\n"
		data += "\t\t\tposition: " + str(object.location.x) + " " + str(object \
			.location.y) + " " + str(object.location.z) + "\n"
		data += "\t\t\trotation: " + str(object.rotation_euler.x) + " " + str( \
			object.rotation_euler.y) + " " + str(object.rotation_euler.z) + "\n"
		data += "\t\t\tscale: " + str(object.scale.x) + " " + str(object.scale \
			.y) + " " + str(object.scale.z) + "\n"

		texture_slots = material.texture_slots
		image_textures = [texture_slots[key].texture for key in texture_slots. \
			keys() if texture_slots[key].texture.type == "IMAGE"]
		image_files = [texture.image.filepath for texture in image_textures if \
			getattr(texture.image, "source", "") == "FILE"]
		if not image_files:
			raise InvalidObjectDataError("\tError: the object \"" + name + \
				"\" hasn't image texture.")
		texture = image_files[0].replace("//", "./" if platform.system() == \
			"Linux" else ".\\")

		data += "\t\t\tmaterial:\n"
		data += "\t\t\t\ttexture: " + texture + "\n"
		data += "\t\t\t\ttransparency_type: " + ("NONE" if not \
			use_transparency else "ALPHA_TEST" if transparency_method == \
			"MASK" else "BLENDING") + "\n"
		data += "\t\t\t\tallow_ambient_light: " + str(material.ambient == 1.0) \
			.lower() + "\n"
		data += "\t\t\t\tallow_fog: " + str(material.use_mist).lower() + "\n"

		vertices = []
		for polygon in mesh.polygons:
			positions = []
			for position in [mesh.vertices[index] for index in polygon. \
				vertices]:
				positions.append(position.co)

			uvs = []
			for uv in [mesh.uv_layers.active.data[index] for index in polygon. \
				loop_indices]:
				uvs.append(uv.uv)

			zipped = list(zip(positions, uvs))
			if len(zipped) == 4:
				zipped = [zipped[0], zipped[1], zipped[2], zipped[2], zipped[ \
					3], zipped[0]]
			vertices.extend(zipped)

		data += "\t\t\tvertices:\n"
		data += "\t\t\t\tnumber: " + str(len(vertices)) + "\n"
		for vertex in vertices:
			data += "\t\t\t\tvertex:\n"
			data += "\t\t\t\t\tposition: " + str(vertex[0].x) + " " + str( \
				vertex[0].y) + " " + str(vertex[0].z) + "\n"
			data += "\t\t\t\t\tuv: " + str(vertex[1].x) + " " + str(vertex[1]. \
				y) + "\n"

		if export_animation and not object.animation_data is None:
			keys = { "location": {}, "rotation_euler": {}, "scale": {} }
			for curve in object.animation_data.action.fcurves:
				curve_type = curve.data_path
				if curve_type in keys:
					for key in curve.keyframe_points:
						frame =   key.co[0]
						key_map = keys[curve_type]

						if not frame in key_map:
							key_map[frame] = [0.0, 0.0, 0.0]
						key_map[frame][curve.array_index] = key.co[1]

			for key in keys.items():
				type =     key[0]
				key_list = key[1]

				if type == "location":
					type = "POSITION"
				elif type == "rotation_euler":
					type = "ROTATION"
				elif type == "scale":
					type = "SCALE"
				else:
					continue

				for key in key_list.items():
					frame =          key[0]
					transformation = key[1]

					key = Key(number, int(round(frame)), type, transformation)
					animation.append(key)

		return data, animation

def menu_func(self, context):
	self.layout.operator(AnnaObjectExport.bl_idname, text = "Anna Object " + \
		"(*.ao)")

def register():
	bpy.utils.register_class(ErrorDialogOperator)
	bpy.utils.register_module(__name__)
	bpy.types.INFO_MT_file_export.append(menu_func)

def unregister():
	bpy.types.INFO_MT_file_export.remove(menu_func)
	bpy.utils.unregister_module(__name__)
	bpy.utils.unregister_class(ErrorDialogOperator)

if __name__ == "__main__":
	register()
