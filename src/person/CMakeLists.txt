add_library(person
    AcademicMember.cpp
    Librarian.cpp
    Professor.cpp
    Student.cpp
)
target_include_directories(person PUBLIC include)
