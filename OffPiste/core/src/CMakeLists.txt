file(GLOB MAL_H *.h)

set(MAL_SRC
    OffPiste.cpp
)

# ==================== #
# Build shared library #
# ==================== #
add_library(OffPiste SHARED ${MAL_SRC} ${MAL_H})

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
