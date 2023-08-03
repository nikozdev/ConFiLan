cmake_minimum_required(VERSION 3.3...3.8)
# proj
set(vProjNameUse "ConFiLan")
set(vProjNameLib "l${vProjNameUse}")
set(vProjNameDll "${vProjNameLib}Shared")
set(vProjNameSll "${vProjNameLib}Static")
set(vProjNameExe "e${vProjNameUse}")
set(vProjNameCon "c${vProjNameUse}")
set(vProjNameDef "d${vProjNameUse}")
set(vProjVnumMajor 0)
set(vProjVnumMinor 0)
set(vProjVnumMicro 0)
set(vProjVnumWhole "${vProjVnumMajor}.${vProjVnumMinor}.${vProjVnumMicro}")
project(${vProjNameUse}
  VERSION ${vProjVnumWhole}
  DESCRIPTION
  "configuration file language library"
  ) # project
# osys
mark_as_advanced(FORCE CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(FORCE CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(FORCE CMAKE_OSX_SYSROOT)
# lang
enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# file
set(vFileDirLoc "${PROJECT_SOURCE_DIR}/..")
set(vFileDirSrc "${vFileDirLoc}/src")
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(vMakeToolGnucc "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(vMakeToolMsvcc "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
##lib
option(oMakeLib "make project library" TRUE)
if(oMakeLib)
  add_library(${vProjNameLib} INTERFACE)
  target_compile_definitions(${vProjNameLib} INTERFACE
    ${vProjNameCon}ProjName=${vProjNameUse}
    ${vProjNameCon}ProjVnum=${vProjVnumWhole}
    ) # target_compile_definitions
  target_compile_definitions(${vProjNameLib} INTERFACE ${vProjNameDef}MakeLib)
  target_compile_options(${vProjNameLib} INTERFACE
    "$<${vMakeToolGnucc}:>"
    "$<${vMakeToolMsvcc}:>"
    ) # target_compile_options
  target_include_directories(${vProjNameLib} INTERFACE
    "$<BUILD_INTERFACE:${vFileDirSrc}>;"
    "$<INSTALL_INTERFACE:${vFileDirDstHead}>;"
    ) # target_include_directories
  # dll
  option(oMakeDll "make project shared library" TRUE)
  if(oMakeDll)
    add_library(${vProjNameDll} SHARED ${vFileDirSrc}/${vProjNameUse}.cxx)
    target_compile_definitions(${vProjNameDll} PRIVATE ${vProjNameDef}MakeDll)
    target_link_libraries(${vProjNameDll} PRIVATE ${vProjNameLib})
  endif(oMakeDll)
  # sll
  option(oMakeSll "make project static library" TRUE)
  if(oMakeSll)
    add_library(${vProjNameSll} STATIC ${vFileDirSrc}/${vProjNameUse}.cxx)
    target_compile_definitions(${vProjNameSll} PRIVATE ${vProjNameDef}MakeSll)
    target_link_libraries(${vProjNameSll} PRIVATE ${vProjNameLib})
  endif(oMakeSll)
  # exe
  option(oMakeExe "make project executable" TRUE)
  if(oMakeExe)
    add_executable(${vProjNameExe} ${vFileDirSrc}/${vProjNameUse}.cxx)
    target_compile_definitions(${vProjNameExe} PRIVATE ${vProjNameDef}MakeExe)
    target_link_libraries(${vProjNameExe} PRIVATE ${vProjNameLib})
    # test
  endif(oMakeExe)
endif(oMakeLib)
