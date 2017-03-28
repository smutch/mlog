Import('cc mesg_format')

# we don't need any 3rd party libs here so let's make a new env
env = Environment(CC=cc,
        CFLAGS='-std=gnu99 -march=native -O3 -fPIC'.split())
for k, v in mesg_format.items():
    env[k] = v

sources = Glob('*.c')
sources = [s for s in sources if 'test.c' not in s.name]

mlog = env.SharedLibrary('mlog', sources)
test = env.Program('test', sources+['test.c'])
env.Alias('install', [env.Install('lib', mlog),
                      env.Install('include', 'mlog.h')])
env.Alias('all', [mlog, test])
