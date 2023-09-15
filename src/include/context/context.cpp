#include "context.hpp"

void c_ctx::init( ) {
    try {
        g_offsets->init( );

        g_scheduler->set_identity( 8 );

        g_scheduler->run_script( xorstr_( "printidentity()" ) );
        g_scheduler->run_script( xorstr_( "print('Execution ready!')" ) );
        
        g_bridge->create_pipe( );
    }
    catch ( const std::exception& error ) {
        g_hooks->print( print_level::error, xorstr_( "Caught an exception: %s" ), error.what( ) );
    }
}

BOOL APIENTRY DllMain( HMODULE module, DWORD reason, LPVOID reserved ) {
    if ( reason != DLL_PROCESS_ATTACH )
        return 0;

    std::jthread{ [ ]( ) {
        g_ctx->init( );
    } }.detach( );

    return 1;
}