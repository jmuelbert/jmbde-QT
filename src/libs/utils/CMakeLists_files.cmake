# -------------------------------------------------------------------------------------------------------------------- #
# Define directory path
# -------------------------------------------------------------------------------------------------------------------- #
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${MAIN_DIR}/include/${TARGET_ID_LOWER})
set(SOURCE_DIR ${MAIN_DIR}/src)

# -------------------------------------------------------------------------------------------------------------------- #
# Define headers files
# -------------------------------------------------------------------------------------------------------------------- #
set(HEADERS
  ${INCLUDE_DIR}/logger.h
)

# Group files in IDE project
source_group("include\\${TARGET_ID_LOWER}" FILES ${HEADERS})

# -------------------------------------------------------------------------------------------------------------------- #
# Define sources files
# -------------------------------------------------------------------------------------------------------------------- #
set(SOURCES 
  ${SOURCE_DIR}/logger.cpp
    )

# Group files in IDE project
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
