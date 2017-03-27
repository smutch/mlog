vars = Variables(None, ARGUMENTS)
vars.Add('prefix', 'Installation prefix', '.')

env = Environment(
        CFLAGS='-std=gnu99 -march=native -O3 -fPIC'.split(),
        CC='mpicc',
        variables=vars)
Help(vars.GenerateHelpText(env))

sources = Glob('*.c')
sources = [s for s in sources if 'test.c' not in s.name]

lib = env.SharedLibrary('mlog', sources)
test = env.Program('test', sources+['test.c'])
env.Alias('install', [env.Install('${prefix}/lib', lib),
                      env.Install('${prefix}/include', 'mlog.h')])
env.Alias('all', [lib, test])

env.Default(lib)
