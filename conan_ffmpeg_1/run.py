#!/usr/bin/env python3

from pathlib import Path
from shutil import which
from subprocess import run, PIPE
import os
import sys

srcdir = Path(__file__).absolute().parent
bindir = srcdir / 'build'
bindir.mkdir(exist_ok=True)

cmake_generator = os.environ.get('CMAKE_GENERATOR', 'Unix Makefiles')
configuration = 'Release'


def desc():
    print('Description:')
    print((srcdir / 'description.txt').open().read())


def init():
    conan_exec = which('conan')

    if not conan_exec:
        pip_install = ['pip', 'install']
        if sys.platform != 'win32':
            pip_install  += ['--user']
        pip_install += ['conan']
        run(pip_install, check=True)
        conan_exec = which('conan')

    if not conan_exec:
        print('Cannot find conan after installation!', file=sys.stderr)
    run(['conan', 'user'], check=True)

    remotes = run(['conan', 'remote', 'list'], stdout=PIPE, check=True)
    if b'bincrafters' not in remotes.stdout:
        run(['conan', 'remote', 'add', 'bincrafters', 'https://api.bintray.com/conan/bincrafters/public-conan'], check=True)


def build():
    run(['conan', 'install', str(srcdir)], cwd=bindir, check=True)
    run(['cmake', str(srcdir), '-DCMAKE_BUILD_TYPE={}'.format(configuration), '-G{}'.format(cmake_generator)], cwd=bindir, check=True)
    run(['cmake', '--build', str(bindir)], cwd=bindir, check=True)


def test():
    run(['ctest', '-C', configuration], cwd=bindir, check=True)


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
