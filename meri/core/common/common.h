#ifndef COMMON_H_
#define COMMON_H_

#ifdef WIN32
#include <Windows.h>

#endif // WIN32


#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <future>
#include <sstream>
#include <map>
#include <queue>
#include <memory>
#include <type_traits>
#include <variant>
#include <cassert>

#include "singleton.h"
#include "mericommon.h"
#include "modulevirtualinterface.h"


enum MeriStatus
{
    kNomal = 0,
    kError = 100
};

namespace meri
{
    class MediaBuffer
    {
    public:
        void* buffer_;
        int width_, height_;
        
    };
}

template <typename E>
constexpr auto ToUnderlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}
#endif // MERI_COMMON_H_
