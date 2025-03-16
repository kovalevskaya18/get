add_library(linalg STATIC
        matrix.cpp
        matrix.hpp
        matrix.tpp
        subvector.cpp
        subvector.hpp
        subvector.tpp
)

set_target_properties(linalg PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)