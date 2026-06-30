add_library(item
    Item.cpp
    PublicItem.cpp
    LoanableItem.cpp
    RestrictedItem.cpp
    ExhibitionItem.cpp
    Visit.cpp
)
target_include_directories(item PUBLIC include)
