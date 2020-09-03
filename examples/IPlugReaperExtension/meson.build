project('IPlugReaperExtension-meson', 'cpp', 'c',
       )

subdir('src')

link_args = []

iplug2_proj = subproject('iPlug2',
			 default_options: ['IGRAPHICS=NO_IGRAPHICS',
					  ])

app = shared_library(
  'reaper_mesonIPlugReaperExtension',
  name_prefix: '', # skipping the lib prefix in linux
  dependencies: [
    iplug2_proj.get_variable('iplug2_RPR_dep'),
    app_dep, # from src/
  ],
  link_args: link_args,
  install: true,
  # implib: true,
  )
