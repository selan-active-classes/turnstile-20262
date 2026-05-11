#=== Main App ==
add_executable( ${APP_NAME} main.cpp turnstile.cpp)
target_compile_features( ${APP_NAME}  PUBLIC cxx_std_17 )
target_compile_options( ${APP_NAME} PRIVATE -Wall -pedantic -g)
# target_compile_options( ${APP_NAME} PRIVATE -Wall -pedantic -O3)
target_link_libraries( ${APP_NAME} PRIVATE ${LIB_NAME})
# Define where the binary will be output to.
set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
