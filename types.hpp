/*
Copyright (C) 2015 Jonathon Ogden     < jeog.dev@gmail.com >

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses.
*/

#ifndef JO_0815_TYPES
#define JO_0815_TYPES

#include <stdexcept>
#include <exception>
#include <chrono>
#include <ctime>
#include <iostream>
#include <functional>

#include "trimmed_rational.hpp"

namespace NativeLayer{

typedef float               price_type;
typedef double              price_diff_type;
typedef unsigned long       size_type, id_type;
typedef long long           size_diff_type;
typedef unsigned long long  large_size_type;

typedef std::pair<price_type,size_type>         limit_order_type;
typedef std::pair<price_type,limit_order_type>  stop_order_type;

typedef typename std::chrono::steady_clock      clock_type;

typedef const enum {
    cancel = 0,
    fill
}callback_msg;

typedef std::function<void(callback_msg,id_type,
                           price_type,size_type)> fill_callback_type;



inline std::ostream& operator<<(std::ostream& out, limit_order_type lim)
{
  std::cout<< lim.second << ',' << lim.first;
  return out;
}

inline std::ostream& operator<<(std::ostream& out, stop_order_type stp)
{
  std::cout<< stp.first << ',' << stp.second;  // chain to limit overload
  return out;
}

class liquidity_exception
    : public std::runtime_error{
public:
  liquidity_exception(const char* what)
    :
    std::runtime_error(what)
    {
    }
};

class invalid_order
    : public std::invalid_argument{
public:
  invalid_order(const char* what)
    :
     std::invalid_argument(what)
    {
    }
};

class invalid_parameters
    : public std::invalid_argument{
public:
  invalid_parameters(const char* what)
    :
     std::invalid_argument(what)
    {
    }
};

class cache_value_error
    : public std::runtime_error{
public:
  cache_value_error(const char* what)
    :
     std::runtime_error(what)
    {
    }
};

template<typename T1>
inline std::string cat(T1 arg1){ return std::string(arg1); }
template<typename T1, typename... Ts>
inline std::string cat(T1 arg1, Ts... args)
{
  return std::string(arg1) + cat(args...);
}

};
#endif