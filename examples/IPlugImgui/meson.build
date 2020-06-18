project('IPlugImgui-meson', 'cpp', 'c',
	# the main.rc building appears as a build target
	# so specifying that the project of interest is the actual executable
	# default_options: ['backend_startup_project=IPlugControls']
       )

extra_args = []
if meson.get_compiler('cpp').get_id() == 'msvc'
  message('visual studio')
  # examples flags from the provided example
  extra_args += ['/wd"4996"', '/wd"4250"', '/wd"4018"', '/wd"4267"', '/wd"4068"', '-D_DEBUG']
endif

subdir('src')

link_args = []

system = host_machine.system()
if system == 'windows'
  # just copied that from the provided examples
  link_args += '/DYNAMICBASE "dsound.lib" "winmm.lib" "wininet.lib" "comctl32.lib" "Shlwapi.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"'
  link_args += '/TLBID:1'

  # so turns out that imgui subproject builds a library
  # and it has to be linked against opengl32.lib
  # it dones't just work if I add this link arg in my vst/exe target
  add_global_link_arguments('/DYNAMICBASE "opengl32.lib"', language: 'cpp')
elif system == 'linux'
  link_args += ['-lpthread', '-lxcb', '-ldl', '-lGL',
		'-lfontconfig',
		# '-lGLU',
		'-lpulse', '-lpulse-simple']
  extra_args += ['-fpermissive']
endif

targets = get_option('IPLUG_TARGETS')

message('Building app for targets [' + ', '.join(targets) + ']')

iplug2_proj = subproject('iPlug2',
			 default_options: ['IGRAPHICS=NO_IGRAPHICS',
					  ])

sdl2_proj = subproject('sdl2')
sdl2_dep = sdl2_proj.get_variable('sdl2_dep')

# imgui searched for sdl
# https://mesonbuild.com/Reference-manual.html#dependency
meson.override_dependency('sdl', sdl2_dep)

imgui = subproject('imgui',
		   default_options: ['sdl=enabled',
				     'opengl2=enabled',
				    ])

imgui_dep = imgui.get_variable('imgui_dep')

# if targets.contains('APP')
#   iplug2_APP_args = iplug2_proj.get_variable('args_common') + iplug2_proj.get_variable('args_APP')
#   message('Target APP, adding cpp_args ' + ','.join(iplug2_APP_args))

#   app = executable(
#     'IPlugImgui-APP',
#     dependencies : [
#       app_dep,
#       iplug2_proj.get_variable('iplug2_APP_dep'),
#       sdl2_dep,
#       imgui_dep
#     ],
#     link_args: link_args,
#     cpp_args: extra_args + iplug2_APP_args,
#     gui_app: true,
#     install: true,
#     implib: true,
#   )
# endif

if targets.contains('VST3')
  iplug2_VST3_args = iplug2_proj.get_variable('args_common') + iplug2_proj.get_variable('args_VST3')
  message('Target VST3, adding cpp_args ' + ','.join(iplug2_VST3_args))
  
  vst3 = shared_library(
    'IPlugImgui-VST3',
    dependencies : [
      app_dep,
      iplug2_proj.get_variable('iplug2_VST3_dep'),
      sdl2_dep,
      imgui_dep,
    ],
    link_args: link_args,
    cpp_args: extra_args + iplug2_VST3_args,
    install: true,
    name_suffix: 'vst3',
    vs_module_defs: 'subprojects/iPlug2/Dependencies/IPlug/VST3_SDK/public.sdk/source/main/winexport.def'
  )
endif

