#pragma once

#include "../../common.hpp"

class c_ctx {
public:
	void init( );

};

inline const auto g_ctx = std::make_unique<c_ctx>( );