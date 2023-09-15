#include "serializer.hpp"

class BytecodeEncoderImpl : public Luau::BytecodeEncoder {
public:
    std::uint8_t encodeOp( const std::uint8_t opcode ) override {
        return opcode * 227;
    }
} encoder;

std::string c_serializer::serialize( const std::string& script ) {
    std::string bytecode = Luau::compile( script, {}, {}, &encoder );

    const std::size_t data_size = bytecode.size( );
    const std::size_t max_size = ZSTD_compressBound( data_size );
    std::vector<char> buffer( max_size + 8 );

    std::memcpy( &buffer[ 0 ], xorstr_( "RSB1" ), 4 );
    std::memcpy( &buffer[ 4 ], &data_size, 4 );

    const std::size_t compressed_size = ZSTD_compress( &buffer[ 8 ], max_size, bytecode.data( ), data_size, ZSTD_maxCLevel( ) );

    if ( ZSTD_isError( compressed_size ) ) {
        g_hooks->print( print_level::error, xorstr_( "Unexpected error during serialization." ) );
        return std::string( );
    }

    const std::size_t size = compressed_size + 8;
    const std::uint32_t key = XXH32( buffer.data( ), size, 42 );
    const std::uint8_t* bytes = reinterpret_cast< const std::uint8_t* >( &key );

    for ( std::size_t i = 0; i < size; ++i )
        buffer[ i ] ^= bytes[ i % 4 ] + i * 41;

    return std::string( buffer.data( ), size );
}