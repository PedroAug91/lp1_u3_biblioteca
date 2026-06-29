add_subdirectory(person)
add_subdirectory(item)
add_subdirectory(database)

add_executable(${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE item person database)
