set(TARGET_NAME lc-majority-element)

add_executable(${TARGET_NAME} main.cpp)

target_link_libraries(
  ${TARGET_NAME}
  PRIVATE
    Catch2::Catch2
)

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 17)
