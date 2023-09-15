#pragma once

#include "../../common.hpp"

class c_mem {
public:
	std::uintptr_t scan( const std::string& signature );

};

inline const auto g_mem = std::make_unique<c_mem>( );