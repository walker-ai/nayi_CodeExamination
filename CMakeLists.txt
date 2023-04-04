project(demo)

include_directories (third_party/cJSON)

aux_source_directory (third_party/cJSON SRC_LIST)

add_executable (main main.c parse.c ${SRC_LIST})


