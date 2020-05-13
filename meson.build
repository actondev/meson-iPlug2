project('c++ iplug demo', 'cpp',
	# default_options : ['cpp_std=c++14']
       )

# VS fix
# https://github.com/mesonbuild/meson/issues/4455
# https://github.com/mesonbuild/meson/issues/6314
if meson.get_compiler('cpp').get_id() == 'msvc'
    extra_args = ['-std:c++17']
else
    extra_args = []
endif

# inc = include_directories('include')
add_project_arguments('-DNO_IGRAPHICS', language : 'cpp')
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
subdir('IPlug2')


# /DYNAMICBASE "dsound.lib" "winmm.lib" "wininet.lib" "comctl32.lib" "Shlwapi.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"

link_args = []

# gui_app: true seems to take care of this
# link_args += '/SUBSYSTEM:WINDOWS'

# just copied that from the example plug
link_args += '/DYNAMICBASE "dsound.lib" "winmm.lib" "wininet.lib" "comctl32.lib" "Shlwapi.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"'
link_args += '/TLBID:1'

# executable()
exe = executable('iplug_exe',
		 dependencies : [iplug_dep, app_dep],
		 link_args: link_args,
		 # cpp_args: extra_args,
		 gui_app: true,
		 install: true, implib: true
		)
