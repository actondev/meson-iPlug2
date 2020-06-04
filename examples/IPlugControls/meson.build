project('IPlugControls-meson', 'cpp', 'c',
	# the main.rc building appears as a build target
	# so specifying that the project of interest is the actual executable
       default_options: ['backend_startup_project=IPlugControls'])

extra_args = []
if meson.get_compiler('cpp').get_id() == 'msvc'
  message('visual studio')
  # examples flags from the provided example
  extra_args += ['/wd"4996"', '/wd"4250"', '/wd"4018"', '/wd"4267"', '/wd"4068"']
  # extra_args += ['-std:c++17']
  # extra_args += ['/showIncludes']
  # extra_args += ['/P']
endif

add_project_arguments('-DAPP_API', language : 'cpp')
add_project_arguments('-DIPLUG_DSP=1', language : 'cpp')
add_project_arguments('-DIPLUG_EDITOR=1', language : 'cpp')
add_project_arguments('-DNOMINMAX', language : 'cpp')
add_project_arguments('-DWIN32', language : 'cpp')
add_project_arguments('-D__WINDOWS_DS__', language : 'cpp')
add_project_arguments('-D__WINDOWS_MM__', language : 'cpp')
add_project_arguments('-D__WINDOWS_ASIO__', language : 'cpp')
subdir('src')

iplug2_proj = subproject('iplug2',
			 default_options: ['IGRAPHICS=IGRAPHICS_NANOVG,IGRAPHICS_GL2']
			)
iplug2_dep = iplug2_proj.get_variable('iplug2_dep')

# adding project arguments defined in subproject
# eg -DIGRAPHICS_NANOVG etc
# seems that adding these arguments inside the subproject doesn't do the trick..
iplug2_args = iplug2_proj.get_variable('arguments')
foreach iplug2_arg : iplug2_args
  add_project_arguments(iplug2_arg, language : 'cpp')
endforeach

link_args = []

# just copied that from the provided examples
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
