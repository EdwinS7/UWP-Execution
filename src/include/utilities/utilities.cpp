#include "utilities.hpp"

std::string alphabet = xorstr_( "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" );

std::string c_util::random_string( int length ) {
    std::random_device rd;
    std::mt19937 generator( rd( ) );
    std::uniform_int_distribution<int> distribution( 0, alphabet.size( ) - 1 );

    std::string random_str;

    for ( int i = 0; i < length; ++i )
        random_str.push_back( alphabet[ distribution( generator ) ] );

    return random_str;
}