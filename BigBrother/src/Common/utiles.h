#pragma once
#include <vector>

template <typename T>
T const getFromBuffer(std::vector<unsigned char> const & buffer)
{
    return *reinterpret_cast<T const *>(buffer.data());
}

template <typename T>
T takeFromBuffer(std::vector<unsigned char> & buffer)
{
    T res = getFromBuffer<T>(buffer);
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(T));
    return res;
}
