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
set(vProjVnumMicro 1)
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
set(vFileDirMainRoot "${PROJECT_SOURCE_DIR}/..")
set(vFileDirMainCode "${vFileDirMainRoot}/code")
set(vFileSetMainCode "${vFileDirMainCode}/${vProjNameUse}.cpp")
set(vFileDirMainHead "${vFileDirMainRoot}/code")
set(vFileSetMainHead "${vFileDirMainHead}/${vProjNameUse}.hpp")
set(vFileDirMainBins "${PROJECT_BINARY_DIR}")
set(vFileSetMainBins "${vFileDirMainBins}/${vProjNameExe}")
set(vFileDirMainData "${vFileDirMainRoot}/data")
set(vFileDirDestRoot "$ENV{HOME}$ENV{UserProfile}/.local")
set(vFileDirDestHead "${vFileDirDestRoot}/include")
set(CMAKE_PREFIX_PATH "${vFileDirDestRoot}" CACHE PATH "destination prefix" FORCE)
set(CMAKE_INSTALL_PREFIX "" CACHE PATH "install prefix" FORCE)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(vMakeToolGnucc "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(vMakeToolMsvcc "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
##lib
option(oMakeLib "make project library" TRUE)
if(oMakeLib)
  add_library(${vProjNameLib} INTERFACE)
  # dep
  find_package(fmt 10.0.0 REQUIRED)
  target_link_libraries(${vProjNameLib} INTERFACE fmt::fmt)
  mark_as_advanced(FORCE fmt_DIR)
  find_package(Boost 1.82.0 COMPONENTS filesystem REQUIRED)
  target_link_libraries(${vProjNameLib} INTERFACE Boost::filesystem)
  mark_as_advanced(FORCE Boost_FILESYSTEM_LIBRARY_RELEA)
  mark_as_advanced(FORCE Boost_INCLUDE_DIR)
  mark_as_advanced(FORCE Boost_DIR)
  target_compile_definitions(${vProjNameLib} INTERFACE
    ${vProjNameDef}ProjName="${vProjNameUse}"
    ${vProjNameDef}ProjVnum="${vProjVnumWhole}"
    ${vProjNameDef}FileRoot="${vFileDirMainRoot}"
    ${vProjNameDef}FileData="${vFileDirMainData}"
    "$<${vMakeToolGnucc}:${vProjNameDef}ToolGnucc"
    "$<${vMakeToolMsvcc}:${vProjNameDef}ToolMsvcc"
    ) # target_compile_definitions
  # set
  target_compile_definitions(${vProjNameLib} INTERFACE ${vProjNameDef}MakeLib)
  target_compile_options(${vProjNameLib} INTERFACE
    "$<${vMakeToolGnucc}:>"
    "$<${vMakeToolMsvcc}:>"
    ) # target_compile_options
  target_include_directories(${vProjNameLib} INTERFACE
    "$<BUILD_INTERFACE:${vFileDirMainCode}>;"
    "$<INSTALL_INTERFACE:${vFileDirDestHead}>;"
    ) # target_include_directories
  # dll
  option(oMakeDll "make project shared library" TRUE)
  if(oMakeDll)
    add_library(${vProjNameDll} SHARED ${vFileSetMainCode})
    target_compile_definitions(${vProjNameDll} PRIVATE ${vProjNameDef}MakeDll)
    target_link_libraries(${vProjNameDll} PRIVATE ${vProjNameLib})
  endif(oMakeDll)
  # sll
  option(oMakeSll "make project static library" TRUE)
  if(oMakeSll)
    add_library(${vProjNameSll} STATIC ${vFileSetMainCode})
    target_compile_definitions(${vProjNameSll} PRIVATE ${vProjNameDef}MakeSll)
    target_link_libraries(${vProjNameSll} PRIVATE ${vProjNameLib})
  endif(oMakeSll)
  # exe
  option(oMakeExe "make project executable" TRUE)
  if(oMakeExe)
    add_executable(${vProjNameExe} ${vFileSetMainCode})
    target_compile_definitions(${vProjNameExe} PRIVATE ${vProjNameDef}MakeExe)
    target_link_libraries(${vProjNameExe} PRIVATE ${vProjNameLib})
    find_package(pTermAPar 4.2.1 REQUIRED)
    target_link_libraries(${vProjNameExe} PRIVATE pTermAPar::lTermAPar)
    mark_as_advanced(FORCE pTermAPar_DIR)
    # test
    include(CTest)
    enable_testing()
    #
    set(vTestName "tHello")
    add_test(NAME ${vTestName}
      COMMAND ${vFileSetMainBins} ${vTestName}
      ) # add_test
    set_tests_properties(${vTestName} PROPERTIES
      PASS_REGULAR_EXPRESSION  "HelloWorld"
      ) # set_tests_properties
    #
    set(vTestName "tFileSystem")
    add_test(NAME ${vTestName}
      COMMAND ${vFileSetMainBins} ${vTestName}
      ) # add_test
    set_tests_properties(${vTestName} PROPERTIES
      PASS_REGULAR_EXPRESSION "RelativePath=."
      ) # set_tests_properties
    #
    set(vTestName "tFileSave")
    add_test(NAME ${vTestName}
      COMMAND ${vFileSetMainBins} ${vTestName}
      ) # add_test
    set_tests_properties(${vTestName} PROPERTIES
      PASS_REGULAR_EXPRESSION "\\[index\\]=\\(value\\)=\\[index\\]"
      REQUIRED_FILES ${vFileDirMainData}/save.cfl
      ) # set_tests_properties
    #
    set(vTestName "tFileLoad")
    add_test(NAME ${vTestName}
      COMMAND ${vFileSetMainBins} ${vTestName}
      ) # add_test
    set_tests_properties(${vTestName} PROPERTIES
      PASS_REGULAR_EXPRESSION "\\[index\\]=\\(value\\)=\\[index\\]"
      REQUIRED_FILES ${vFileDirMainData}/save.cfl
      ) # set_tests_properties
    #
  endif(oMakeExe)
endif(oMakeLib)
