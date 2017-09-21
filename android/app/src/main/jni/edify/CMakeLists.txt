
# the oiriginal bison version is 2.4, current is 3.x
# something seems different, have to figure it out
# for now the pregenerated files are fine

#find_package(BISON)
#find_package(FLEX)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${CMAKE_CURRENT_BINARY_DIR})

# BISON_TARGET(edifyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
# FLEX_TARGET(edifyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
# ADD_FLEX_BISON_DEPENDENCY(edifyScanner edifyParser)

add_library(libedify    STATIC
            # ${BISON_edifyParser_OUTPUTS}
            parser.c
            # ${FLEX_edifyScanner_OUTPUTS}
            lex.yy.c
            expr.c )
