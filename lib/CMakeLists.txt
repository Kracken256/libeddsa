set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EDDSA_SRC fld.cpp sc.cpp ed.cpp sha512.cpp ed25519-sha512.cpp x25519.cpp)

if (USE_STACKCLEAN)
  list(APPEND EDDSA_SRC burn.cpp burnstack.cpp)
endif ()

if (BUILD_STATIC)
  add_library(eddsa-static STATIC ${EDDSA_SRC})
  target_compile_options(eddsa-static PRIVATE -O3 -fPIC -Wall -Wextra -Werror -g)

  if (BITNESS EQUAL 64)
    set_property(TARGET eddsa-static APPEND PROPERTY COMPILE_DEFINITIONS NO_AUTO_BITNESS)
    set_property(TARGET eddsa-static APPEND PROPERTY COMPILE_DEFINITIONS USE_64BIT)
  elseif (BITNESS EQUAL 32)
    set_property(TARGET eddsa-static APPEND PROPERTY COMPILE_DEFINITIONS NO_AUTO_BITNESS)
  endif ()

  if (USE_STACKCLEAN)
    set_property(TARGET eddsa-static APPEND PROPERTY COMPILE_DEFINITIONS USE_STACKCLEAN)
  endif ()

  if (HAVE_MEMSET_S)
    set_property(TARGET eddsa-static APPEND PROPERTY COMPILE_DEFINITIONS HAVE_MEMSET_S)
  endif ()
  if (HAVE_EXPLICIT_BZERO)
    set_property(TARGET eddsa-static APPEND PROPERTY COMPILE_DEFINITIONS HAVE_EXPLICIT_BZERO)
  endif ()

  set_property(TARGET eddsa-static APPEND PROPERTY COMPILE_DEFINITIONS EDDSA_BUILD EDDSA_STATIC)
  set_property(TARGET eddsa-static APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS EDDSA_STATIC)

  install(TARGETS eddsa-static DESTINATION ARCHIVE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
endif ()
