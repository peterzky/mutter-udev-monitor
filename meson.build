project('updater', 'c',
        version : '0.1',
        default_options : ['warning_level=3',
                           'c_std=c11'])

udev = dependency('libudev')

exe = executable('main', 'src/main.c', dependencies: [udev], install : true)
