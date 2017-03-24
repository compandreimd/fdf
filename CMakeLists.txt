cmake_minimum_required(VERSION 3.6)
project(fdf)


add_subdirectory(libft)

include_directories(libft/includes)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES src/fdf.h src/fdf_map.c src/fdf_orto.c src/fdf_tools.c src/fdf_pers.c src/main.c)


add_executable(fdf ${SOURCE_FILES})

target_link_libraries(fdf mlx)
target_link_libraries(fdf "-framework OpenGL")
target_link_libraries(fdf "-framework AppKit")
target_link_libraries(fdf libft)
