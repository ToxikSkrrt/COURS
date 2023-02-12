cmake_minimum_required(VERSION 2.6)
project(GameText C)

enable_testing()
include(CTest)

link_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_C_FLAGS "-std=c99 -g -Wall --coverage")

add_library(game game.c game_aux.c game_ext.c queue.c game_tools.c)

add_executable(game_text game_text.c)

add_executable(game_test_tcohen game_test_tcohen.c)
add_executable(game_test_cebarrat game_test_cebarrat.c)
add_executable(game_test_thmoreau game_test_thmoreau.c)

target_link_libraries(game_text game)
target_link_libraries(game_test_cebarrat game)
target_link_libraries(game_test_thmoreau game)
target_link_libraries(game_test_tcohen game)

# ${CMAKE_CURRENT_SOURCE_DIR}/build/
add_test(test_tcohen_dummy ./game_test_tcohen dummy)
add_test(test_tcohen_game_equal ./game_test_tcohen game_equal)
add_test(test_tcohen_game_copy ./game_test_tcohen game_copy)
add_test(test_tcohen_game_is_empty ./game_test_tcohen game_is_empty)
add_test(test_tcohen_game_is_immutable ./game_test_tcohen game_is_immutable)
add_test(test_tcohen_game_has_error ./game_test_tcohen game_has_error)
add_test(test_tcohen_game_check_move ./game_test_tcohen game_check_move)
add_test(test_tcohen_game_delete ./game_test_tcohen game_delete)
add_test(test_tcohen_game_new_ext ./game_test_tcohen game_new_ext)
add_test(test_tcohen_game_new_empty_ext ./game_test_tcohen game_new_empty_ext)
add_test(test_tcohen_game_nb_rows ./game_test_tcohen game_nb_rows)
add_test(test_tcohen_game_nb_cols ./game_test_tcohen game_nb_cols)


add_test(test_cebarrat_dummy ./game_test_cebarrat dummy)
add_test(test_cebarrat_game_default ./game_test_cebarrat game_default)
add_test(test_cebarrat_game_get_square ./game_test_cebarrat game_get_square)
add_test(test_cebarrat_game_get_next_square ./game_test_cebarrat game_get_next_square)
add_test(test_cebarrat_game_get_number ./game_test_cebarrat game_get_number)
add_test(test_cebarrat_game_get_next_number ./game_test_cebarrat game_get_next_number)
add_test(test_cebarrat_game_set_square ./game_test_cebarrat game_set_square)
add_test(test_cebarrat_game_is_unique ./game_test_cebarrat game_is_unique)
add_test(test_cebarrat_game_is_wrapping ./game_test_cebarrat game_is_wrapping)

add_test(test_thmoreau_dummy ./game_test_thmoreau dummy)
add_test(test_thmoreau_game_is_over ./game_test_thmoreau game_is_over)
add_test(test_thmoreau_game_restart ./game_test_thmoreau game_restart)
add_test(test_thmoreau_game_play_move ./game_test_thmoreau game_play_move)
add_test(test_thmoreau_game_new_empty ./game_test_thmoreau game_new_empty)
add_test(test_thmoreau_game_new ./game_test_thmoreau game_new)
add_test(test_thmoreau_game_default_solution ./game_test_thmoreau game_default_solution)
add_test(test_thmoreau_game_print ./game_test_thmoreau game_print)
add_test(test_thmoreau_game_undo ./game_test_thmoreau game_undo)
add_test(test_thmoreau_game_redo ./game_test_thmoreau game_redo)