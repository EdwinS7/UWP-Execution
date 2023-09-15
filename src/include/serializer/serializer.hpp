#pragma once

#include "../../common.hpp"

class c_serializer {
public:
	std::string serialize( const std::string& bytecode );

};

inline const auto g_serializer = std::make_unique<c_serializer>( );