file(GLOB MAL_H *.h)

set(MAL_SRC
    OffPiste.cpp
)

# ==================== #
# Build shared library #
# ==================== #
OPTION(PACKAGE_MODULE "Enable module creation" OFF)
if(PACKAGE_MODULE)
  add_library(OffPiste MODULE ${MAL_SRC} ${MAL_H})
else()
  add_library(OffPiste SHARED ${MAL_SRC} ${MAL_H})
endif()

# Install targets into specific directories
install(TARGETS OffPiste 
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
	ARCHIVE DESTINATION lib/
)

install(FILES ${MAL_H} DESTINATION include)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
