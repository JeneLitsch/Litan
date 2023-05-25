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



	function pair(first, second) => [ 
		.first = first,
		.second = second,
	]


	function mono(value) => [ 
		.value = value,
	]



	function typename(x) const => choose(std::typeid(x)) {
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



	function null_v() const => null



	function is_type(value, type) const
		=> typeid(value) == type



	function is_null(value) const   => is(<null>, value)
	function is_bool(value) const   => is(<bool>, value)
	function is_char(value) const   => is(<char>, value)
	function is_int(value) const    => is(<int>, value)
	function is_float(value) const  => is(<float>, value)
	function is_array(value) const  => is(<array>, value)
	function is_string(value) const => is(<string>, value)

	function is_integral(value) const 
		=> is_bool(value)
		|| is_char(value)
		|| is_int(value)

	function is_numeric(value) const 
		=> is_integral(value)
		|| is_float(value)


	function is_istream(value) const 
		=> is_type(value, type::istream)
	
	function is_ostream(value) const 
		=> is_type(value, type::ostream)

	
	
	function is_fxptr(value) const 
		=> is_type(value, type::fxptr)
	
	function is_external(value) const
		=> is_type(value, type::external)
	
	function is_functional(value) const 
		=> is_fxptr(value) 
		|| is_external(value)
	
	
	
	function is_clock(value) const
		=> is_type(value, type::clock)
	
	function is_struct(value) const
		=> is_type(value, type::struct)
	
	function is_range(value) const
		=> is_type(value, type::range)



	function is_queue(value) const
		=> is_type(value, type::queue)

	function is_stack(value) const
		=> is_type(value, type::stack)

	function is_map(value) const
		=> is_type(value, type::map)



	function is_rng(value) const
		=> is_type(value, type::rng)



	build_in is(type, value) const @type_is
	build_in cast(type, value) const @type_cast

	function is_binary_fx(fx) const
		=> std::is(<fx(2)>, fx) && !std::is_variadic(fx)

	function is_unary_fx(fx) const
		=> std::is(<fx(1)>, fx) && !std::is_variadic(fx)

	function is_addable(obj)       const => is_binary_fx(obj.{_+_})
	function is_subtractable(obj)  const => is_binary_fx(obj.{_-_})
	function is_multipliable(obj)  const => is_binary_fx(obj.{_*_})
	function is_divisible(obj)     const => is_binary_fx(obj.{_/_})
	function is_modable(obj)       const => is_binary_fx(obj.{_%_})
	function is_powable(obj)       const => is_binary_fx(obj.{_**_})
	function is_stringifiable(obj) const => is_unary_fx(obj.{str})
}
)###";
