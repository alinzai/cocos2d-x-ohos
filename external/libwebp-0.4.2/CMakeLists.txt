cmake_minimum_required(VERSION 3.4.1)

project(webp)

set(WEBP_DEC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/alpha.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/buffer.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/frame.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/idec.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/io.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/quant.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/tree.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/vp8.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/vp8l.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/dec/webp.c")
add_library(webpdecode STATIC ${WEBP_DEC_SRC})
target_compile_definitions(webpdecode PUBLIC -DHAVE_CONFIG_H)
target_compile_options(webpdecode PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(webpdecode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp)

set(WEBP_ENC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/alpha.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/analysis.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/backward_references.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/config.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/cost.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/filter.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/frame.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/histogram.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/iterator.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/picture.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/picture_csp.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/picture_psnr.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/picture_rescale.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/picture_tools.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/quant.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/syntax.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/token.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/tree.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/vp8l.c"
                 "${CMAKE_CURRENT_SOURCE_DIR}/src/enc/webpenc.c")
add_library(webpencode STATIC ${WEBP_ENC_SRC})
target_compile_definitions(webpencode PUBLIC -DHAVE_CONFIG_H)
target_compile_options(webpencode PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(webpencode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp)

set(WEBP_DSP_AVX2 "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/enc_avx2.c")
add_library(webpdsp_avx2 STATIC ${WEBP_DSP_AVX2})
target_compile_definitions(webpdsp_avx2 PUBLIC -DHAVE_CONFIG_H)
target_compile_options(webpdsp_avx2 PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(webpdsp_avx2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp)

set(WEBP_DSP_DEC_SSE2 "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/dec_sse2.c"
                      "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/lossless_sse2.c"
                      "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/alpha_processing_sse2.c"
                      "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/upsampling_sse2.c"
                      "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/yuv_sse2.c")
add_library(webpdspdecode_sse2 STATIC ${WEBP_DSP_DEC_SSE2})
target_compile_definitions(webpdspdecode_sse2 PUBLIC -DHAVE_CONFIG_H)
target_compile_options(webpdspdecode_sse2 PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(webpdspdecode_sse2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp)

set(WEBP_DSP_SSE2 "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/enc_sse2.c")# ${WEBP_DSP_DEC_SSE2}
add_library(webpdsp_sse2 STATIC ${WEBP_DSP_SSE2} ${WEBP_DSP_DEC_SSE2})
target_compile_definitions(webpdsp_sse2 PUBLIC -DHAVE_CONFIG_H)
target_compile_options(webpdsp_sse2 PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(webpdsp_sse2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp)

set(WEBP_DEP "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/alpha_processing.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/cpu.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/dec.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/dec_clip_tables.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/dec_mips32.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/dec_neon.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/lossless.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/lossless_mips32.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/lossless_neon.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/upsampling.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/upsampling_neon.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/yuv.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/yuv_mips32.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/enc.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/enc_neon.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/enc_mips32.c")
             #${WEBP_DSP_AVX2}
             #${WEBP_DSP_SSE2})
add_library(webpdsp STATIC ${WEBP_DEP} ${WEBP_DSP_AVX2} ${WEBP_DSP_SSE2})
target_compile_definitions(webpdsp PUBLIC -DHAVE_CONFIG_H)
target_compile_options(webpdsp PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(webpdsp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp)

set(WEBP_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/bit_reader.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/bit_writer.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/color_cache.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/filters.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/huffman.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/huffman_encode.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/quant_levels.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/quant_levels_dec.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/random.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/rescaler.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/thread.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.c")
add_library(webputils STATIC ${WEBP_UTILS})
target_compile_definitions(webputils PUBLIC -DHAVE_CONFIG_H)
target_compile_options(webputils PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(webputils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp)

# final lib
add_library(${PROJECT_NAME} STATIC ${WEBP_DEC_SRC} ${WEBP_ENC_SRC} ${WEBP_DSP_AVX2} ${WEBP_DSP_DEC_SSE2}
                                   ${WEBP_DSP_SSE2} ${WEBP_DEP} ${WEBP_UTILS})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DHAVE_CONFIG_H)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wdeclaration-after-statement -Wextra -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -Wshadow -Wunused-but-set-variable -Wunused -Wvla -fPIC)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/webp
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/src/dec
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/src/dsp
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/src/enc
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils)

