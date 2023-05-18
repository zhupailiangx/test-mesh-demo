cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
if(POLICY CMP0074)
  # 1. Remove with 3.12.4.
  # 2. Remove search paths with *_ROOT since they will be automatically checked
  cmake_policy(SET CMP0074 NEW)
endif()

project(voxel_grid)
set(CMAKE_C_COMPILER "icx")
set(CMAKE_CXX_COMPILER "icpx")
set(CMAKE_CXX_STANDARD 17)
set(PCL_CXX_COMPILE_FEATURES cxx_std_17)

#set(INTEL_CPP_COMPILER "Intel C++ Compiler 2023")
#set(INTEL_DPCPP_COMPILER "Intel(R) oneAPI DPC++ Compiler 2023")
#set(CMAKE_GENERATOR_TOOLSET ${INTEL_DPCPP_COMPILER})
if(WIN32)
#set(CMAKE_GENERATOR_TOOLSET "Intel(R) oneAPI DPC++ Compiler 2023")
set(PCL_ROOT "C:/Program Files (x86)/PCL")
set(PCL_BIN "C:/Program Files (x86)/PCL/bin")
#set(PCL_ONEAPI_ROOT "C:/Program Files (x86)/PCL-ONEAPI")

set(BOOST_ROOT "C:/boost_1_81_0")
set(BOOST_LIBRARYDIR "C:/boost_1_81_0/stage/lib")
set(Boost_LIB_PREFIX "lib")
#set(VTK_ROOT "C:/Program Files/PCL 1.12.1/3rdParty/VTK")

find_package(PCL 1.12 REQUIRED)
find_package(PCL-ONEAPI 1.12 REQUIRED)
include_directories(
  $ENV{ONEAPI_ROOT}/dpcpp-ct/latest/include
  $ENV{ONEAPI_ROOT}/dpl/latest/windows/include
  $ENV{ONEAPI_ROOT}/compiler/latest/windows/include/sycl
  $ENV{ONEAPI_ROOT}/compiler/latest/windows/include
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  )
link_directories($ENV{ONEAPI_ROOT}/tbb/latest/lib/intel64/vc14)
else() 
find_package(PCL 1.12 REQUIRED NO_MODULE PATHS /usr/local/share/pcl-1.12 NO_DEFAULT_PATH)
find_package(PCL-ONEAPI 1.12 REQUIRED NO_MODULE PATHS /usr/local/share/pcl-oneapi-1.12 NO_DEFAULT_PATH)  
endif()




include_directories(${PCL-ONEAPI_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
link_directories(${PCL-ONEAPI_LIBRARY_DIRS} ${PCL_LIBRARY_DIRS})
add_definitions(${PCL-ONEAPI_DEFINITIONS} ${PCL_DEFINITIONS})
if(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-dev -Qiopenmp -Qopenmp-targets=spir64 /QxCORE-AVX2")
else()
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wno-unknown-pragmas -Wno-pass-failed -Wno-unneeded-internal-declaration -Wno-gnu-anonymous-struct -Wno-nested-anon-types -Wno-extra-semi -fsycl -fsycl-unnamed-lambda -ferror-limit=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fiopenmp -fopenmp-targets=spir64")
endif()
add_executable (voxel_grid voxel_grid.cpp)

if(WIN32)
set_target_properties(voxel_grid PROPERTIES VS_PLATFORM_TOOLSET "Intel(R) oneAPI DPC++ Compiler 2023")  
else()
set_target_properties(voxel_grid PROPERTIES LINKER_LANGUAGE CXX)  
endif()

# Make sure PCL-ONEAPI libs are linked in prior to the PCL libs !!!
target_link_libraries (voxel_grid pcl_oneapi_containers pcl_oneapi_filters_omp pcl_oneapi_surface_omp)
target_link_libraries (voxel_grid ${PCL_LIBRARIES})
