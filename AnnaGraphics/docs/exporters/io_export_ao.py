# -*- coding: utf-8 -*-

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
import mathutils
from bpy_extras.io_utils import ExportHelper
from bpy.props import *
import time
import platform
import math

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
	selected_only =    BoolProperty(name = "Selected only", description = \
		"Export only selected objects", default = False)
	export_animation = BoolProperty(name = "Export animation", description = \
		"Export animation data", default = True)

	def execute(self, context):
		print("\nStart exported the active object to Anna Object (*.ao)...")
		start_time = time.time()
		filepath = bpy.path.ensure_ext(self.filepath, self.filename_ext)
		exported = self._export(context, filepath)
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

	def _export(self, context, filepath):
		description = ""
		try:
			scene = context.scene
			current_frame = scene.frame_current
			scene.frame_set(scene.frame_start)

			animation_keys = []
			number_of_object = 0
			objects = []
			if not self.properties.selected_only:
				objects = bpy.data.objects;
			else:
				objects = context.selected_objects;
			for object in [object for object in objects if object.type == \
				"MESH"]:
				object_description, object_animation_keys = self. \
					_getObjectData(context, object, number_of_object)
				description += object_description
				animation_keys.extend(object_animation_keys)
				number_of_object += 1

			scene.frame_set(current_frame)

			begin_of_description = "object:\n"
			begin_of_description += "\tmeshes:\n"
			begin_of_description += "\t\tnumber: " + str(number_of_object) \
				+ "\n"
			description = begin_of_description + description

			end_of_description = "\tanimation_keys:\n"
			end_of_description += "\t\tnumber: " + str(len(animation_keys)) \
				+ "\n"
			for key in animation_keys:
				end_of_description += "\t\tkey:\n"
				end_of_description += "\t\t\tindex_of_mesh: " + str(key. \
					index_of_mesh) + "\n"
				end_of_description += "\t\t\tframe: " + str(key.frame) + "\n"
				end_of_description += "\t\t\ttype: " + str(key.type) + "\n"
				end_of_description += "\t\t\ttransformation: " + str(key. \
					transformation.x) + " " + str(key.transformation.y) + \
					" " + str(key.transformation.z) + "\n"
			description += end_of_description
		except InvalidObjectDataError as exception:
			message = str(exception)
			print(message)

			message = message.replace("\tError: ", "")
			message = message.capitalize()
			bpy.ops.error.dialog("INVOKE_DEFAULT", message = message)

			return False

		file = open(filepath, "w")
		file.write(description)
		file.close()

		return True

	def _getObjectData(self, context, object, number_of_object):
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

		object_transformations = object.matrix_world
		description = ""
		description += "\t\tmesh:\n"
		position = object_transformations.to_translation()
		description += "\t\t\tposition: " + str(position.x) + " " + str( \
			position.y) + " " + str(position.z) + "\n"
		rotation = mathutils.Vector((0.0, 0.0, 0.0))
		euler_angles = object_transformations.to_euler("XYZ")
		rotation.x = math.degrees(euler_angles.x)
		rotation.y = math.degrees(euler_angles.y)
		rotation.z = math.degrees(euler_angles.z)
		description += "\t\t\trotation: " + str(rotation.x) + " " + str( \
			rotation.y) + " " + str(rotation.z) + "\n"
		scale = object_transformations.to_scale()
		description += "\t\t\tscale: " + str(scale.x) + " " + str(scale.y) + \
			" " + str(scale.z) + "\n"

		texture_slots = material.texture_slots
		image_textures = [texture_slots[key].texture for key in texture_slots. \
			keys() if texture_slots[key].texture.type == "IMAGE"]
		image_files = [texture.image.filepath for texture in image_textures if \
			getattr(texture.image, "source", "") == "FILE"]
		if not image_files:
			raise InvalidObjectDataError("\tError: the object \"" + name + \
				"\" hasn't image texture.")
		texture = image_files[0].replace("//", "")

		description += "\t\t\tmaterial:\n"
		description += "\t\t\t\ttexture: " + texture + "\n"
		description += "\t\t\t\ttransparency_type: " + ("NONE" if not \
			use_transparency else "ALPHA_TEST" if transparency_method == \
			"MASK" else "BLENDING") + "\n"
		description += "\t\t\t\tallow_ambient_light: " + str(material.ambient \
			== 1.0).lower() + "\n"
		description += "\t\t\t\tallow_fog: " + str(material.use_mist).lower() \
			+ "\n"

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

		description += "\t\t\tvertices:\n"
		description += "\t\t\t\tnumber: " + str(len(vertices)) + "\n"
		for vertex in vertices:
			description += "\t\t\t\tvertex:\n"
			description += "\t\t\t\t\tposition: " + str(vertex[0].x) + " " + \
				str(vertex[0].y) + " " + str(vertex[0].z) + "\n"
			description += "\t\t\t\t\tuv: " + str(vertex[1].x) + " " + str( \
				vertex[1].y) + "\n"

		animation_keys = []
		if self.properties.export_animation and not object.animation_data is \
			None:
			scene = context.scene
			for frame in range(scene.frame_start, scene.frame_end):
				scene.frame_set(frame)

				object_transformations = object.matrix_world
				key = Key(number_of_object, frame, "POSITION", \
					object_transformations.to_translation())
				animation_keys.append(key)

				rotation = mathutils.Vector((0.0, 0.0, 0.0))
				euler_angles = object_transformations.to_euler("XYZ")
				rotation.x = math.degrees(euler_angles.x)
				rotation.y = math.degrees(euler_angles.y)
				rotation.z = math.degrees(euler_angles.z)
				key = Key(number_of_object, frame, "ROTATION", rotation)
				animation_keys.append(key)

				key = Key(number_of_object, frame, "SCALE", \
					object_transformations.to_scale())
				animation_keys.append(key)

		return description, animation_keys

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
