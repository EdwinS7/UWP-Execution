#pragma once

#include "../../common.hpp"

class c_bridge {
public:
	void create_pipe( );

};

inline const auto g_bridge = std::make_unique<c_bridge>( );