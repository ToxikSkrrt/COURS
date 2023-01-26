#minimal version of cmake
cmake_minimum_required(VERSION 2.6)

#usefull line for errors
#set(CMAKE_VERBOSE_MAKEFILE on)


#project's name
project(game_text C)

#activation de la gestion des tests dans CMake
include(CTest)
enable_testing()
find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=yes" )

#setup flags
set (CMAKE_C_FLAGS "-std=c99 -g -Wall --coverage")

#define where to find the library
include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})

#define executable file and his sources
add_executable(game_text game_text.c)


add_library(game game.c game_aux.c game_ext.c queue.c)

#the executable depends on a library
target_link_libraries(game_text game)

add_executable(game_test_ninteyineza game_test_ninteyineza.c )
add_executable(game_test_ecallet game_test_ecallet.c)
add_executable(game_test_pdinghin game_test_pdinghin.c)


target_link_libraries(game_test_ninteyineza game)
target_link_libraries(game_test_pdinghin game)
target_link_libraries(game_test_ecallet game)



#Ajout des tests

# tests pour callet
add_test(test_ecallet_dummy ./game_test_ecallet dummy)
add_test(test_ecallet_get_number ./game_test_ecallet get_number)
add_test(test_ecallet_get_next_square ./game_test_ecallet get_next_square)
add_test(test_ecallet_get_next_square_wrapping ./game_test_ecallet get_next_square_wrapping)
add_test(test_ecallet_check_move ./game_test_ecallet check_move)
add_test(test_ecallet_get_next_number ./game_test_ecallet get_next_number)
add_test(test_ecallet_get_next_number_wrapping ./game_test_ecallet get_next_number_wrapping)
add_test(test_ecallet_is_empty ./game_test_ecallet is_empty)
add_test(test_ecallet_is_immutable ./game_test_ecallet is_immutable)
add_test(test_ecallet_has_error ./game_test_ecallet has_error)
add_test(test_ecallet_has_error_wrapping ./game_test_ecallet has_error_wrapping)
add_test(test_ecallet_has_error_unique ./game_test_ecallet has_error_unique)
add_test(test_ecallet_undo ./game_test_ecallet undo)
add_test(test_ecallet_game_new_ext_moodle ./game_test_ecallet game_new_ext_moodle)
add_test(test_ecallet_is_over_unique ./game_test_ecallet is_over_unique)

# tests pour Paul
add_test(test_pdinghin_dummy ./game_test_pdinghin dummy)
add_test(test_pdinghin_new_game_empty ./game_test_pdinghin new_game_empty)
add_test(test_pdinghin_game_delete ./game_test_pdinghin game_delete)
add_test(test_pdinghin_game_equal ./game_test_pdinghin game_equal)
add_test(test_pdinghin_game_copy ./game_test_pdinghin game_copy)
add_test(test_pdinghin_game_set_square ./game_test_pdinghin game_set_square)
add_test(test_pdinghin_game_get_square ./game_test_pdinghin game_get_square)
add_test(test_pdinghin_game_new ./game_test_pdinghin game_new)
add_test(test_pdinghin_game_new_ext ./game_test_pdinghin game_new_ext)
add_test(test_pdinghin_game_new_empty_ext ./game_test_pdinghin game_new_empty_ext)
add_test(test_pdinghin_game_is_wrapping ./game_test_pdinghin game_is_wrapping)
add_test(test_pdinghin_game_is_unique ./game_test_pdinghin game_is_unique)
add_test(test_pdinghin_game_nb_rows ./game_test_pdinghin game_nb_rows)
add_test(test_pdinghin_game_nb_cols ./game_test_pdinghin game_nb_cols)
add_test(test_pdinghin_game_redo ./game_test_pdinghin game_redo)

# tests pour Neda
add_test(test_ninteyineza_dummy ./game_test_ninteyineza dummy)
#add_test(test_ninteyineza_game_print ./game_test_ninteyineza game_print)
add_test(test_ninteyineza_game_default ./game_test_ninteyineza game_default)
add_test(test_ninteyineza_game_default_solution ./game_test_ninteyineza game_default_solution)
add_test(test_ninteyineza_game_is_over ./game_test_ninteyineza game_is_over)
add_test(test_ninteyineza_game_is_over_unique ./game_test_ninteyineza game_is_over_unique)
add_test(test_ninteyineza_game_is_over_wrapping ./game_test_ninteyineza game_is_over_wrapping)
add_test(test_ninteyineza_game_restart ./game_test_ninteyineza game_restart)
add_test(test_ninteyineza_game_play_move ./game_test_ninteyineza game_play_move)
add_test(test_ninteyineza_game_equal_ext ./game_test_ninteyineza game_equal_ext)


