#include "hooks.hpp"

template <typename hook_type>
void c_offsets::create_hook( hook_type* hook, const std::string& signature ) {
	*hook = reinterpret_cast< hook_type >(
		g_mem->scan( signature )
	);
}

template <typename hook_type>
void c_offsets::create_hook( hook_type* hook, const uintptr_t& offset ) {
	*hook = reinterpret_cast< hook_type >(
		g_hooks->rebase( offset )
	);
}

// @version: 2.592.586.0
void c_offsets::init( ) {
	// @ida xref: "Current identity is %d" the function call within.
	create_hook( &g_hooks->print, xorstr_( "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 20 A1 ?? ?? ?? ?? 33 C5 89 45 F0 50 8D 45 F4 64 A3 00 00 00 00 8B" ) );

	// @ida xref: [Watchdog or LuauWatchdog], after second jnz its the sub function.
	create_hook( &g_hooks->get_scheduler, xorstr_( "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 51 56 A1 ?? ?? ?? ?? 33 C5 50 8D 45 F4 64 A3 00 00 00 00 E8 ?? ?? ?? ?? 84" ) );

	// @ida xref: "defer", the function itself.
	create_hook( &g_hooks->task_defer, xorstr_( "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 30 A1 ?? ?? ?? ?? 33 C5 89 45 EC 53 56 57 50 8D 45 F4 64 A3 00 00 00 00 8B 7D 08 C7 45 E8" ) );

	// @ida xref: "spawn", the function itself.
	create_hook( &g_hooks->task_spawn, xorstr_( "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 24 A1 ?? ?? ?? ?? 33 C5 89 45 EC 56 57 50 8D 45 F4 64 A3 00 00 00 00 8B 7D 08 C7" ) );

	// @ida xref: "debug" second sub routine upwards ( use match case ), its right under that.
	create_hook( &g_hooks->get_state, xorstr_( "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 2C A1 ?? ?? ?? ?? 33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3 00 00 00 00 8B F9 8B 45 0C" ) );

	// @ida xref: "oldResult, moduleRef  = ..." last sub function called.
	create_hook( &g_hooks->lua_vm_load, xorstr_( "53 8B DC 83 EC 08 83 E4 F8 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 51 53 81 EC D0 07" ) );

	// @ida xref: "tables cannot be cyclic" decompile then looks for the next unk_xxxxxxx, done.
	create_hook( &g_hooks->lua_nil_object, 0x2E067F8 );

	// @ida xref: "{\"type\":\"table\",\"cat\":%d,\"size\":%d" its the first dword being utilized after the sub function. its right above lua_nil_object.
	create_hook( &g_hooks->lua_dummy_node, 0x2E067D8 );

	// @ida xref: "assertion failed!" its the first unk_xxxxxxx used.
	create_hook( &g_hooks->pseudo2, 0x02EFB810 );

	g_scheduler->script_context = g_scheduler->get_script_context( );
	g_scheduler->lua_state = g_scheduler->get_global_state( );
}