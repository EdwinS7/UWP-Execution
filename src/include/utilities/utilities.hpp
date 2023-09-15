#pragma once

#include "../../common.hpp"

class c_util {
public:
	std::string random_string( int length );

};

inline const auto g_util = std::make_unique<c_util>( );