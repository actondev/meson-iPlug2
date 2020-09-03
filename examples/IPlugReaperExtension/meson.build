project('IPlugReaperExtension-meson', 'cpp', 'c',
	# the main.rc building appears as a build target
	# so specifying that the project of interest is the actual executable
	# default_options: ['backend_startup_project=IPlugControls']
       )

extra_args = []
if meson.get_compiler('cpp').get_id() == 'msvc'
  message('visual studio')
  # examples flags from the provided example
  # extra_args += ['/wd"4996"', '/wd"4250"', '/wd"4018"', '/wd"4267"', '/wd"4068"']
  # extra_args += ['-std:c++17']
  # extra_args += ['/showIncludes']
  # extra_args += ['/P']
endif

subdir('src')

link_args = []

# just copied that from the provided examples
link_args += '/DYNAMICBASE "dsound.lib" "winmm.lib" "wininet.lib" "comctl32.lib" "Shlwapi.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"'
link_args += '/TLBID:1'

iplug2_proj = subproject('iPlug2',
			 default_options: ['IGRAPHICS=NO_IGRAPHICS',
					  ])

app = shared_library(
  'reaper_mesonIPlugReaperExtension',
  dependencies: [
    iplug2_proj.get_variable('iplug2_RPR_dep'),
    app_dep, # from src/
  ],
  link_args: link_args,
  cpp_args: extra_args,
  install: true,
  # implib: true,
  )
