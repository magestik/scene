set(ASSIMP_ROOT_DIR CACHE PATH "ASSIMP root directory")

if (WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(ASSIMP_MSVC_ARCHITECTURE "x64")
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(ASSIMP_MSVC_ARCHITECTURE "x86")
	endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
	if(MSVC12)
		set(ASSIMP_MSVC_VERSION "vc120")
	elseif(MSVC14)	
		set(ASSIMP_MSVC_VERSION "vc140")
	endif(MSVC12)
	
	find_path(assimp_INCLUDE_DIRS NAMES assimp/Importer.hpp HINTS ${ASSIMP_ROOT_DIR}/include)
	
	find_library(assimp_LIBRARIES NAMES assimp HINTS ${ASSIMP_ROOT_DIR}/lib/${ASSIMP_MSVC_ARCHITECTURE})

	if(MSVC12 OR MSVC14)

		FUNCTION(ASSIMP_COPY_BINARIES TargetDirectory)
			ADD_CUSTOM_TARGET(AssimpCopyBinaries
				COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_ROOT_DIR}/bin/${ASSIMP_MSVC_ARCHITECTURE}/assimp-${ASSIMP_MSVC_VERSION}-mt.dll 		${TargetDirectory}/Release/assimp-${ASSIMP_MSVC_VERSION}-mt.dll
			COMMENT "Copying Assimp binaries to '${TargetDirectory}'"
			VERBATIM)
		ENDFUNCTION(ASSIMP_COPY_BINARIES)
	
	endif()
	
else (WIN32)

	find_path(assimp_INCLUDE_DIRS NAMES assimp/Importer.hpp PATHS /usr/local/include/)

	find_library(assimp_LIBRARIES NAMES assimp PATHS /usr/local/lib/)

endif (WIN32)

if (assimp_INCLUDE_DIRS AND assimp_LIBRARIES)
	SET(assimp_FOUND TRUE)
ENDIF (assimp_INCLUDE_DIRS AND assimp_LIBRARIES)

if (assimp_FOUND)
	if (NOT assimp_FIND_QUIETLY)
	message(STATUS "Found asset importer library: ${assimp_LIBRARIES}")
	endif (NOT assimp_FIND_QUIETLY)
else (assimp_FOUND)
	if (assimp_FIND_REQUIRED)
	message(FATAL_ERROR "Could not find asset importer library")
	endif (assimp_FIND_REQUIRED)
endif (assimp_FOUND)
	