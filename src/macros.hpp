#pragma once

#if !defined(NDEBUG) || defined(_DEBUG)
    #ifndef IN_DEBUG
        #define IN_DEBUG 1
    #endif
#else
    #ifndef IN_DEBUG
        #define IN_DEBUG 0
    #endif
#endif
