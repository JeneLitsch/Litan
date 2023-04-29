#pragma once
inline const char * std_type = R"###(
namespace std {

	enum type {
		nul      : 0x00;
		bool     : 0x10;
		char     : 0x13;
		int      : 0x11;
		float    : 0x12;
		array    : 0x20;
		string   : 0x21;
		istream  : 0x30;
		ostream  : 0x31;
		fxptr    : 0x40;
		external : 0x41;
		clock    : 0x50;
		struct   : 0x60;
		range    : 0x61;
		queue    : 0x70;
		stack    : 0x71;
		map      : 0x72;
		rng      : 0x80;
	}



	build_in struct() const       @ struct
	build_in typeid(value) const  @ type_typeid
	build_in clone(ref) const     @ type_clone



	function pair(first : <T1>, second : <T2>) {
		return [ 
			.first = first,
			.second = second,
		];
	}


	function mono(value : <T>) {
		return [ 
			.value = value,
		];
	}



	function typename(x) const -> string => choose(std::typeid(x)) {
		case std::type::nul       => "null"
		case std::type::bool      => "bool"
		case std::type::char      => "char"
		case std::type::int       => "int"		
		case std::type::float     => "float"	
		case std::type::string    => "string"
		case std::type::array     => "array"
		case std::type::istream   => "istream"
		case std::type::ostream   => "ostream"
		case std::type::fxptr     => "fxptr"
		case std::type::external  => "external"
		case std::type::clock     => "clock"
		case std::type::struct    => "struct"
		case std::type::range     => "range"
		case std::type::queue     => "queue"
		case std::type::stack     => "stack"
		case std::type::map       => "map"
		case std::type::rng       => "rng"
		default                   => "unknown";
	}



	function null_v() const -> null => null



	function is_type(value, type) const -> bool
		=> typeid(value) == type



	function is_null(value) const -> bool
		=> is_type(value, type::nul)



	function is_bool(value) const -> bool
		=> is_type(value, type::bool)

	function is_char(value) const -> bool
		=> is_type(value, type::char)

	function is_int(value) const -> bool
		=> is_type(value, type::int)

	function is_float(value) const -> bool
		=> is_type(value, type::float)

	function is_integral(value) const -> bool
		=> is_bool(value)
		|| is_char(value)
		|| is_int(value)

	function is_numeric(value) const -> bool
		=> is_integral(value)
		|| is_float(value)





	function is_array(value) const -> bool
		=> is_type(value, type::array)
	
	function is_string(value) const -> bool
		=> is_type(value, type::string)



	function is_istream(value) const -> bool
		=> is_type(value, type::istream)
	
	function is_ostream(value) const -> bool
		=> is_type(value, type::ostream)

	
	
	function is_fxptr(value) const -> bool
		=> is_type(value, type::fxptr)
	
	function is_external(value) const-> bool
		=> is_type(value, type::external)
	
	function is_functional(value) const -> bool
		=> is_fxptr(value) 
		|| is_external(value)
	
	
	
	function is_clock(value) const -> bool
		=> is_type(value, type::clock)
	
	function is_struct(value) const -> bool
		=> is_type(value, type::struct)
	
	function is_range(value) const -> bool
		=> is_type(value, type::range)



	function is_queue(value) const -> bool
		=> is_type(value, type::queue)

	function is_stack(value) const -> bool
		=> is_type(value, type::stack)

	function is_map(value) const -> bool
		=> is_type(value, type::map)



	function is_rng(value) const -> bool
		=> is_type(value, type::rng)
}
)###";
