#include "bridge.hpp"

// @note: incomplete but it works relativly the same as any other except for on the executor you have to actually search for the pipe (UWP).
void c_bridge::create_pipe( ) {
	DWORD Read{};
	char BufferSize[ 999999 ];
	std::string name = ( xorstr_( "\\\\.\\pipe\\local\\" ) + std::string( ENVIORNMENT_NAME ) ), script{};

	HANDLE Pipe = CreateNamedPipeA( name.c_str( ), PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, PIPE_WAIT, 1, 9999999, 9999999, NMPWAIT_USE_DEFAULT_WAIT, nullptr );

	while ( Pipe != INVALID_HANDLE_VALUE ) {
		if ( ConnectNamedPipe( Pipe, nullptr ) != FALSE ) {
			while ( ReadFile( Pipe, BufferSize, sizeof( BufferSize ) - 1, &Read, nullptr ) != FALSE ) {
				BufferSize[ Read ] = '\0';
				script += BufferSize;
			}

			g_scheduler->run_script( script );
			script.clear( );
		}
		DisconnectNamedPipe( Pipe );
	}
}