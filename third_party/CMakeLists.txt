# Explicitly disable zlib support for now.
# Might be useful later when a output stream is made but for now
# it's not worth it.
set(MCO_WITH_ZLIB OFF)
add_subdirectory(mcolib)