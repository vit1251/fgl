project('freegl', 'c', version: '0.7')

src = [
    'src/fgl2.c',
    'src/fgl3.c',
    'src/fglaux.c',
    'src/fglb.c',
    'src/fgl.c',
    'src/fgle.c',
    'src/fglf.c',
    'src/fglm.c',
    'src/fgls.c',
    'src/fglt.c',
    'src/fglu.c',
    'src/syslog.c',
]

libfgl = static_library('libfgl', src)

executable('demo3d', 'example/demo3d.c', link_with: [ libfgl ] )
