#pragma once
#include <vector>
#include <memory>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

template <typename T>
T const getFromBuffer(std::vector<unsigned char> const & buffer, size_t offset = 0)
{
    if (offset >= buffer.size() || sizeof(T) + offset >= buffer.size())
    {
        throw std::runtime_error("");
    }

    return *reinterpret_cast<T const *>(buffer.data() + offset);
}

template <typename T>
T takeFromBuffer(std::vector<unsigned char> & buffer)
{
    T res = getFromBuffer<T>(buffer);
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(T));
    return res;
}

template <class T>
std::unique_ptr<T> getUniqueFromBuffer(std::vector<unsigned char> & buffer)
{
    T x = *reinterpret_cast<T*>(buffer.data());
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(T));
    return std::make_unique<T>(x);
}


