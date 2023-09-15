#include "scheduler.hpp"
#include "../../third-party/Luau/src/lobject.h"
#include "../../third-party/Luau/src/lgc.h"

int c_scheduler::get_job( const std::string& job_name ) {
    uintptr_t scheduler = g_hooks->get_scheduler( );

    uintptr_t job_start = *( uintptr_t* ) ( scheduler + g_offsets->scheduler::job_start );
    uintptr_t job_end = *( uintptr_t* ) ( scheduler + g_offsets->scheduler::job_end );

    while ( job_start != job_end ) {
        uintptr_t job = *( uintptr_t* ) ( job_start );

        if ( *reinterpret_cast< std::string* >( job + g_offsets->scheduler::job_name ) == job_name )
            return job;

        job_start += 8;
    }

    return NULL;
}

uintptr_t c_scheduler::get_script_context( ) {
    return *( uintptr_t* ) ( get_job( xorstr_( "WaitingHybridScriptsJob" ) ) + g_offsets->scheduler::job_context );
}

uintptr_t c_scheduler::get_global_state( ) {
    int identity = 8, script = 0;
    return g_hooks->get_state( script_context, &identity, &script );
}

void c_scheduler::run_script( const std::string& source ) {
    if ( source.length( ) <= 8 )
        return;

    std::string bytecode = g_serializer->serialize( source );

    // @note: rebuild Luau_Load, it's what you should be using!
    if ( g_hooks->lua_vm_load( lua_state, &bytecode, g_util->random_string( 16 ).c_str( ), 0 ) ) {
        g_hooks->print( print_level::error, xorstr_( "Unexpected error during execution." ) );
        return;
    }

    g_hooks->task_defer( lua_state );
    pop_stack( 1 );
}

// @note: Everything below this note is experimental or incomplete.
// @note: https://github.com/Roblox/luau/blob/105f54b2330d0227059c08d2e03454efa934c5db/VM/src/lvmload.cpp#L79
template<typename T>
static T read( const char* data, size_t size, size_t& offset ) {
    T result;
    memcpy( &result, data + offset, sizeof( T ) );
    offset += sizeof( T );

    return result;
}

// @note: https://github.com/Roblox/luau/blob/105f54b2330d0227059c08d2e03454efa934c5db/VM/src/lvmload.cpp#L156
void c_scheduler::luau_load( const std::string& source ) {
    
}