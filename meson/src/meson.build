talkcalendar_sources = [
  'main.c',  
  'calendarevent.c',
  'customcalendar.c',
  'dbmanager.c',
]

talkcalendar_deps = [
  dependency('gtk4'), dependency('sqlite3'),
]


executable('talkcalendar', talkcalendar_sources,
  dependencies: talkcalendar_deps,
       install: true,
)
