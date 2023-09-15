#include "scheduler.hpp"

void c_scheduler::set_identity( const uint8_t& identity ) {
    *reinterpret_cast<int8_t*>( reinterpret_cast< int8_t* >( *( uintptr_t* ) ( g_scheduler->lua_state + g_offsets->lua::extra_space ) + g_offsets->lua::identity ) ) = identity;
}

int c_scheduler::get_identity( ) {
    return *reinterpret_cast< int8_t* >( reinterpret_cast< int8_t* >( *( uintptr_t* ) ( g_scheduler->lua_state + g_offsets->lua::extra_space ) + g_offsets->lua::identity ) );
}

void c_scheduler::pop_stack( uint8_t amount ) {
    *reinterpret_cast< uintptr_t* >( g_scheduler->lua_state + g_offsets->lua::top ) -= 0x10 * amount;
}

void c_scheduler::register_functions( uintptr_t rl ) {

}