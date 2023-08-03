cmake_minimum_required(VERSION 3.3...3.8)
# proj
set(vProjNameUse "ConFiLan")
set(vProjNameLib "l${vProjNameUse}")
set(vProjNameDll "${vProjNameLib}Shared")
set(vProjNameSll "${vProjNameLib}Static")
set(vProjNameExe "e${vProjNameUse}")
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
set(vFileDirBin "${PROJECT_BINARY_DIR}")
set(vFileDirRes "${vFileDirLoc}/res")
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(vMakeToolGnucc "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(vMakeToolMsvcc "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
##lib
option(oMakeLib "make project library" TRUE)
if(oMakeLib)
  add_library(${vProjNameLib} INTERFACE)
  # dep
  find_package(pTermAPar REQUIRED)
  target_link_libraries(${vProjNameLib} INTERFACE pTermAPar::lTermAPar)
  mark_as_advanced(FORCE pTermAPar_DIR)
  find_package(fmt REQUIRED)
  target_link_libraries(${vProjNameLib} INTERFACE fmt::fmt)
  mark_as_advanced(FORCE fmt_DIR)
  find_package(Boost COMPONENTS filesystem REQUIRED)
  target_link_libraries(${vProjNameLib} INTERFACE Boost::filesystem)
  mark_as_advanced(FORCE Boost_FILESYSTEM_LIBRARY_RELEA)
  mark_as_advanced(FORCE Boost_INCLUDE_DIR)
  mark_as_advanced(FORCE Boost_DIR)
  target_compile_definitions(${vProjNameLib} INTERFACE
    ${vProjNameDef}ProjName="${vProjNameUse}"
    ${vProjNameDef}ProjVnum="${vProjVnumWhole}"
    ${vProjNameDef}PathToInternal="${vFileDirLoc}"
    ${vProjNameDef}PathToResource="${vFileDirRes}"
    ) # target_compile_definitions
  # set
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
    include(CTest)
    enable_testing()
    #
    set(vTestName "tHello")
    add_test(NAME ${vTestName}
      COMMAND ${vFileDirBin}/${vProjNameExe} tHello
      ) # add_test
    set(vPassRegex "HelloWorld")
    set_tests_properties(tHello PROPERTIES
      PASS_REGULAR_EXPRESSION ${vPassRegex}
      ) # set_tests_properties
    #
  endif(oMakeExe)
endif(oMakeLib)
