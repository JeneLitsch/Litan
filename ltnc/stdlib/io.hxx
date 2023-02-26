#pragma once
inline const char * std_io = R"###(
namespace std {
	namespace io {
		enum color {
			BLACK        : 0x0;
			RED          : 0x1;
			GREEN        : 0x2;
			YELLOW       : 0x3;
			BLUE         : 0x4;
			MAGENTA      : 0x5;
			CYAN         : 0x6;
			WHITE        : 0x7;

			BOLD_BLACK   : 0x8;
			BOLD_RED     : 0x9;
			BOLD_GREEN   : 0xa;
			BOLD_YELLOW  : 0xb;
			BOLD_BLUE    : 0xc;
			BOLD_MAGENTA : 0xd;
			BOLD_CYAN    : 0xe;
			BOLD_WHITE   : 0xf;
		}

		enum open_mode {
			OVERRIDE : 0;
			APPEND : 1;
		}
		
		build_in set_fg_color(stream, color) @ io_fg_color
		build_in set_bg_color(stream, color) @ io_bg_color
		build_in reset_color(stream)         @ io_reset_color
		build_in close(stream)               @ io_close

		function set_fg_color(color)         => set_fg_color(std::cout(), color)
		function set_bg_color(color)         => set_bg_color(std::cout(), color)
		function reset_color()               => reset_color(std::cout())
	}



	build_in cout() 
		-> ostream
	 	@ io_cout
	
	build_in fout(path, open_mode)
		-> ostream
		@ io_fout
	
	build_in strout() 
		-> ostream
		@ io_strout

	function fout(path)
		-> ostream
		=> fout(path, io::open_mode::OVERRIDE)



	build_in cin()
		-> istream
		@ io_cin

	build_in fin(path)
		-> istream
		@ io_fin

	build_in strin(str)
		-> istream
		@ io_strin


	
	build_in print(stream : ostream, value) 
		-> null
		@ io_print
	
	build_in read(stream : istream)
		-> optional<string> 
		@ io_read

	build_in read_str(stream : istream)
		-> optional<string> 
		@ io_read_str

	build_in readln(stream : istream)
		-> optional<string> 
		@ io_readln

	build_in read_bool(stream : istream)
		-> optional<bool> 
		@ io_read_bool

	build_in read_char(stream : istream)
		-> optional<char> 
		@ io_read_char

	build_in read_int(stream : istream)
		-> optional<int> 
		@ io_read_int

	build_in read_float(stream : istream)
		-> optional<float> 
		@ io_read_float

	build_in read_all(stream : istream)
		-> string 
		@ io_read_all


	
	build_in is_eof(stream) const    @ io_is_eof
	// build_in is_good(stream) const   @ io_is_good

	function print(value) => print(cout(), value)

	function println(stream : ostream, value) {
		print(stream, value);
		print(stream, "\n");
	}

	function println(value) {
		var stream = cout();
		print(stream, value);
		print(stream, "\n");
	}

	function read() 
		-> optional<string>
		=> read(cin())
	
	function read_str()
		-> optional<string>
		=> read(cin())
	
	function readln()
		-> optional<string>
		=> readln(cin())
	
	function read_bool()  
		-> optional<bool>
		=> read_bool(cin())

	function read_char()  
		-> optional<char>
		=> read_char(cin())
	
	function read_int()   
		-> optional<int>
		=> read_int(cin())
	
	function read_float() 
		-> optional<float>
		=> read_float(cin())
	
	function read_all()  
		-> string 
		=> read_all(cin())
}
)###";
