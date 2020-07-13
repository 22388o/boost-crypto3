# Generated by YCM Generator at 2020-06-26 18:05:32.201979

# This file is NOT licensed under the GPLv3, which is the license for the rest
# of YouCompleteMe.
#
# Here's the license text for this file:
#
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>

import os
import ycm_core

flags = [
    '-x',
    'c++',
    '-DBOOST_ALL_NO_LIB',
    '-DBOOST_CONTAINER_DYN_LINK',
    '-DBOOST_UNIT_TEST_FRAMEWORK_DYN_LINK',
    '-DCRYPTO3_HAS_ARIA',
    '-DCRYPTO3_HAS_BLOWFISH',
    '-DCRYPTO3_HAS_CAMELLIA',
    '-DCRYPTO3_HAS_DES',
    '-DCRYPTO3_HAS_GOST_28147_89',
    '-DCRYPTO3_HAS_IDEA',
    '-DCRYPTO3_HAS_KASUMI',
    '-DCRYPTO3_HAS_MD4',
    '-DCRYPTO3_HAS_MD5',
    '-DCRYPTO3_HAS_MISTY1',
    '-DCRYPTO3_HAS_NOEKEON',
    '-DCRYPTO3_HAS_RIJNDAEL',
    '-DCRYPTO3_HAS_RIJNDAEL_NI',
    '-DCRYPTO3_HAS_SEED',
    '-DCRYPTO3_HAS_SERPENT',
    '-DCRYPTO3_HAS_SHACAL2',
    '-DCRYPTO3_HAS_SM4',
    '-DCRYPTO3_HAS_THREEFISH',
    '-DCRYPTO3_HAS_TWOFISH',
    '-DCRYPTO3_HAS_XTEA',
    '-D_BLOCK_MP_USE_X86_64_ASM',
    '-D_BLOCK_MP_WORD_BITS=64',
    '-D_BLOCK_TARGET_ARCHITECTURE_IS_X86_64',
    '-D_BLOCK_TARGET_CPU_HAS_NATIVE_64BIT',
    '-D_BLOCK_TARGET_CPU_IS_LITTLE_ENDIAN',
    '-D_BLOCK_TARGET_CPU_IS_X86_FAMILY',
    '-D_BLOCK_TARGET_OSSOCKETS',
    '-D_BLOCK_TARGET_OS_HAS_-maes',
    '-D_BLOCK_TARGET_OS_HAS_ARC4RANDOM',
    '-D_BLOCK_TARGET_OS_HAS_DEV_RANDOM',
    '-D_BLOCK_TARGET_OS_HAS_DLOPEN',
    '-D_BLOCK_TARGET_OS_HAS_FILELSYSTEM',
    '-D_BLOCK_TARGET_OS_HAS_GETTIMEOFDAY',
    '-D_BLOCK_TARGET_OS_HAS_GMTIME_R',
    '-D_BLOCK_TARGET_OS_HAS_MEMSET_S',
    '-D_BLOCK_TARGET_OS_HAS_POSIX1',
    '-D_BLOCK_TARGET_OS_HAS_READDIR',
    '-D_BLOCK_TARGET_OS_HAS_SOCKETS',
    '-D_BLOCK_TARGET_OS_HAS_THREADS',
    '-D_BLOCK_TARGET_OS_HAS_TIMEGM',
    '-D_BLOCK_TARGET_OS_IS_DARWIN',
    '-D_BLOCK_TARGET_OS_TYPE_IS_UNIX',
    '-I/Users/nemo/Documents/Sources/Network/UniversalApplications/nil/libs/crypto3/boost/include',
    '-I/Users/nemo/Documents/Sources/Network/UniversalApplications/nil/libs/crypto3/boost/test/block',
    '-I/Users/nemo/Documents/Sources/Network/UniversalApplications/nil/libs/crypto3/boost/test/block/include',
    '-I/Users/nemo/Documents/Sources/Network/UniversalApplications/nil/libs/crypto3/boost/test/codec',
    '-I/Users/nemo/Documents/Sources/Network/UniversalApplications/nil/libs/crypto3/boost/test/codec/include',
    '-I/Users/nemo/Documents/Sources/Network/UniversalApplications/nil/libs/crypto3/boost/test/hash',
    '-I/Users/nemo/Documents/Sources/Network/UniversalApplications/nil/libs/crypto3/boost/test/hash/include',
    '-I/private/var/folders/my/39n5ww_j3xqd7kwgvb3jy5zm0000gn/T/tmpDh0CJE/include',
    '-std=gnu++14',
    '-isysroot', '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk',
    '-isystem', '/opt/local/include',
]


# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
#
# You can get CMake to generate this file for you by adding:
#   set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
# to your CMakeLists.txt file.
#
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = ''

if os.path.exists( compilation_database_folder ):
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None

SOURCE_EXTENSIONS = [ '.C', '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return list( flags )
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.H', '.h', '.hxx', '.hpp', '.hh' ]


def GetCompilationInfoForFile( filename ):
  # The compilation_commands.json file generated by CMake does not have entries
  # for header files. So we do our best by asking the db for flags for a
  # corresponding source file, if any. If one exists, the flags for that file
  # should be good enough.
  if IsHeaderFile( filename ):
    basename = os.path.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if os.path.exists( replacement_file ):
        compilation_info = database.GetCompilationInfoForFile(
          replacement_file )
        if compilation_info.compiler_flags_:
          return compilation_info
    return None
  return database.GetCompilationInfoForFile( filename )


def FlagsForFile( filename, **kwargs ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = GetCompilationInfoForFile( filename )
    if not compilation_info:
      return None

    final_flags = MakeRelativePathsInFlagsAbsolute(
      compilation_info.compiler_flags_,
      compilation_info.compiler_working_dir_ )

  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }

def Settings( **kwargs ):
    language = kwargs[ 'language' ]
    if language == 'cfamily':
        return {
            'flags': flags
        }

    return {}
