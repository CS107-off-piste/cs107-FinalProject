file(GLOB OFFPISTE_SRC *.h)

set(OFFPISTE_SRC
    OffPiste.cpp
)

# ==================== #
# Build shared library #
# ==================== #
OPTION(PACKAGE_MODULE "Enable module creation" OFF)
if(PACKAGE_MODULE)
  add_library(OffPiste MODULE ${OFFPISTE_SRC} ${OFFPISTE_SRC})
else()
  add_library(OffPiste SHARED ${OFFPISTE_SRC} ${OFFPISTE_SRC})
endif()

# Install targets into specific directories
install(TARGETS OffPiste 
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
	ARCHIVE DESTINATION lib/
)

install(FILES ${OFFPISTE_SRC} DESTINATION include)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
