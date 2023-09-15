#pragma once

#include "../../common.hpp"

class c_scheduler {
public:
	// scheduler, job
	int get_job( const std::string& job );

	// scheduler, state
	uintptr_t get_script_context( );
	uintptr_t get_global_state( );

	// execution, scripts
	void run_script( const std::string& source );
	void luau_load( const std::string& source );

	// functions, identity
	void set_identity( const uint8_t& identity );
	int get_identity( );

	// functions, stack
	void pop_stack( uint8_t amount );

	// functions, register
	void register_functions( uintptr_t rl );

	std::uintptr_t script_context, lua_state;
};

inline const auto g_scheduler = std::make_unique<c_scheduler>( );