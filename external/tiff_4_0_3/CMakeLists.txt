cmake_minimum_required(VERSION 3.4.1)

project(libtiff)

set(TIFF_SRC "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_aux.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_close.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_codec.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_color.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_compress.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_dir.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_dirinfo.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_dirread.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_dirwrite.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_dumpmode.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_error.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_extension.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_fax3.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_fax3sm.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_flush.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_getimage.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_jbig.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_jpeg_12.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_jpeg.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_luv.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_lzma.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_lzw.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_next.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_ojpeg.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_open.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_packbits.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_pixarlog.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_predict.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_print.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_read.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_strip.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_swab.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_thunder.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_tile.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_unix.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_version.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_warning.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_write.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_zip.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/port/dummy.c")

add_library(${PROJECT_NAME} STATIC ${TIFF_SRC})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DHAVE_CONFIG_H)
target_compile_options(${PROJECT_NAME} PUBLIC -fPIC -Wall -W -DPIC -Wno-sign-compare -Wno-misleading-indentation -Wno-missing-field-initializers)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libtiff)
