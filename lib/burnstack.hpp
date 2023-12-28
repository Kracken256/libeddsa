#ifndef BURNSTACK_H
#define BURNSTACK_H

#include "compat.hpp"

namespace def::eddsa
{
#ifdef USE_STACKCLEAN


    void burnstack(int len);

#else

static INLINE void burnstack(int len) { (void)len; }

#endif
} // namespace def::eddsa

#endif
