#include "subvector.hpp"

#define INSTANTIATE_SUBVECTOR_FOR_TYPE(T) template class subvector<T>;

INSTANTIATE_SUBVECTOR_FOR_TYPE(int)
INSTANTIATE_SUBVECTOR_FOR_TYPE(double)
INSTANTIATE_SUBVECTOR_FOR_TYPE(float)
