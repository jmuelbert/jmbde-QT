# ==================================================================================
# Documents
# ==================================================================================

if(EMBED_DOCS)
  add_definitions(-DLEMON_EMBED_DOCS)
  set(EMBED_DOC_QRC ${CMAKE_SOURCE_DIR}/docs/manual/manual.qrc)
endif()
