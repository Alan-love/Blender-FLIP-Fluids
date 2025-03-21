# Blender FLIP Fluids Add-on
# Copyright (C) 2025 Ryan L. Guy & Dennis Fassbaender
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

if "bpy" in locals():
    import importlib
    reloadable_modules = [
        'preferences_properties',
        'custom_properties',
        'preset_properties',
        'flip_fluid_properties',
        'object_properties',
        'material_properties',
        'helper_properties'
    ]
    for module_name in reloadable_modules:
        if module_name in locals():
            importlib.reload(locals()[module_name])

import bpy

from . import (
    preferences_properties,
    custom_properties,
    preset_properties,
    flip_fluid_properties,
    object_properties,
    material_properties,
    helper_properties
    )


def scene_update_post(scene):
    object_properties.scene_update_post(scene)
    helper_properties.scene_update_post(scene)


def frame_change_post(scene, depsgraph=None):
    object_properties.frame_change_post(scene, depsgraph)
    helper_properties.frame_change_post(scene, depsgraph)


def load_pre():
    object_properties.load_pre()


def load_post():
    flip_fluid_properties.load_post()
    preferences_properties.load_post()
    object_properties.load_post()
    helper_properties.load_post()


def save_pre():
    object_properties.save_pre()


def save_post():
    object_properties.save_post()
    helper_properties.save_post()


def register():
    preferences_properties.register()
    custom_properties.register()
    preset_properties.register()
    flip_fluid_properties.register()
    object_properties.register()
    material_properties.register()
    helper_properties.register()


def unregister():
    preferences_properties.unregister()
    custom_properties.unregister()
    preset_properties.unregister()
    flip_fluid_properties.unregister()
    object_properties.unregister()
    material_properties.unregister()
    helper_properties.unregister()