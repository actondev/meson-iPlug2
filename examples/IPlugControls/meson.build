project('IPlugControls-meson', 'cpp', 'c',
	# the main.rc building appears as a build target
	# so specifying that the project of interest is the actual executable
       default_options: ['backend_startup_project=IPlugControls'])

message( meson.get_compiler('cpp').get_id())

# VS fix
# https://github.com/mesonbuild/meson/issues/4455
# https://github.com/mesonbuild/meson/issues/6314
extra_args = []
if meson.get_compiler('cpp').get_id() == 'msvc'
  message('visual studio')
  # '-std:c++17',
  # /showIncludes
  # extra_args = ['/P']
endif


add_project_arguments('-DAPP_API', language : 'cpp')
add_project_arguments('-DIPLUG_DSP=1', language : 'cpp')
add_project_arguments('-DIPLUG_EDITOR=1', language : 'cpp')
add_project_arguments('-DNOMINMAX', language : 'cpp')
# add_project_arguments('-DOS_WIN', language : 'cpp')
add_project_arguments('-DWIN32', language : 'cpp')
add_project_arguments('-D__WINDOWS_DS__', language : 'cpp')
# "__WINDOWS_MM__" /D "__WINDOWS_ASIO__"
add_project_arguments('-D__WINDOWS_MM__', language : 'cpp')
add_project_arguments('-D__WINDOWS_ASIO__', language : 'cpp')
# add_project_arguments('-fpermissive', language : 'c')
subdir('src')
# subdir('resources')

# can't this be in the subproject..?
# putting here cause maybe it's not working, let's see..
# add_project_arguments('-DIGRAPHICS_NANOVG', language : 'cpp')
# add_project_arguments('-DIGRAPHICS_GL2', language : 'cpp')
# IGRAPHICS_GL fix... ?
# add_project_arguments('-DIGRAPHICS_GL', language : 'cpp')

# uugh fucking IGRAPHICS_GL ...
# iplug2_proj = subproject('iplug2', default_options: ['IGRAPHICS=IGRAPHICS_NANOVG,IGRAPHICS_GL2,IGRAPHICS_GL'])
subdir('subprojects/iplug2')

# iplug2_dep = iplug2_proj.get_variable('iplug2_dep')

# iplug2_arguments = iplug2_proj.get_variable('arguments')

# foreach iplug2_arg : iplug2_arguments
#   message('adding parent project argument ' + iplug2_arg)
#   add_project_arguments(iplug2_arg, language : 'cpp')
# endforeach


link_args = []

# just copied that from the example plug
link_args += '/DYNAMICBASE "dsound.lib" "winmm.lib" "wininet.lib" "comctl32.lib" "Shlwapi.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"'
link_args += '/TLBID:1'

# executable()
exe = executable('IPlugControls',
		 dependencies : [app_dep, iplug2_dep],
		 link_args: link_args,
		 cpp_args: extra_args,
		 gui_app: true,
		 install: true,
		 implib: true
		)
