#!/usr/bin/env python3

from collections import namedtuple
from pathlib import Path
from shutil import which, rmtree
import os
import platform
import subprocess
import sys

srcdir = Path(__file__).absolute().parent
bindir = srcdir / 'build'

cmake_generator = os.environ.get('CMAKE_GENERATOR', 'Unix Makefiles')
configuration = os.environ.get('CONFIGURATION', 'Release')

if platform.system() == 'Windows':
    static_runtime = False
    std_runtime = '{}{}'.format('MT' if static_runtime else 'MD', 'd' if configuration != 'Release' else '')


def run(*args, **kwargs):
    print('exec: {}'.format(' '.join(['"{}"'.format(arg) for arg in args[0]])))
    sys.stdout.flush()
    return subprocess.run(*args, **kwargs)


def desc():
    print((srcdir / 'description.txt').open().read())
    sys.stdout.flush()


def init():
    if bindir.is_dir():
        rmtree(bindir)
    bindir.mkdir()

    conan_exec = which('conan')

    if not conan_exec:
        if which('pip3'):
            pip_cmd = 'pip3'
        else:
            pip_cmd = 'pip'
        pip_install = [pip_cmd, 'install']
        if sys.platform != 'win32':
            pip_install  += ['--user']
        pip_install += ['conan', 'ninja']
        run(pip_install, check=True)
        conan_exec = which('conan')

    if not conan_exec:
        print('Cannot find conan after installation!', file=sys.stderr)
    run(['conan', 'user'], check=True)

    remotes = run(['conan', 'remote', 'list'], stdout=subprocess.PIPE, check=True)
    if b'bincrafters' not in remotes.stdout:
        run(['conan', 'remote', 'add', 'bincrafters', 'https://api.bintray.com/conan/bincrafters/public-conan'], check=True)


def build():
    conan_install = ['conan', 'install', '-u', str(srcdir), '-s', 'build_type={}'.format(configuration), '--build=missing']
    if platform.system() == 'Windows':
        conan_install += ['-s', 'arch={}'.format('x86_64' if 'Win64' in cmake_generator else 'x86')]
        conan_install += ['-s', 'compiler.runtime={}'.format(std_runtime)]
    run(conan_install, cwd=bindir, check=True)

    env = dict(os.environ)
    if platform.system() == 'Windows':
        cflags = '/{}'.format(std_runtime)
        env['CFLAGS'] = cflags
        env['CXXFLAGS'] = cflags
    run(['cmake', str(srcdir), '-DCMAKE_BUILD_TYPE={}'.format(configuration), '-G{}'.format(cmake_generator)], cwd=bindir, check=True, env=env)
    run(['cmake', '--build', str(bindir), '--config', configuration], cwd=bindir, check=True)


def test():
    run(['ctest', '-C', '-V', configuration], cwd=bindir, check=True)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv += ['desc', 'init', 'build', 'test']

    if 'desc' in sys.argv:
        desc()

    if 'init' in sys.argv:
        init()

    if 'build' in sys.argv:
        build()

    if 'test' in sys.argv:
        test()
