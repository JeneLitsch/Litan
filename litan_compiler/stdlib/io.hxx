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
		
		function set_fg_color(stream, color) => build_in(io_fg_color)
		function set_bg_color(stream, color) => build_in(io_bg_color)
		function reset_color(stream)         => build_in(io_reset_color)
		function close(stream)               => build_in(io_close)

		function set_fg_color(color)         => set_fg_color(std::cout(), color)
		function set_bg_color(color)         => set_bg_color(std::cout(), color)
		function reset_color()               => reset_color(std::cout())
	}



	function cout() 
	 	=> build_in(io_cout)
	
	function fout(path, open_mode)
		=> build_in(io_fout)
	
	function strout() 
		=> build_in(io_strout)

	function fout(path)
		=> fout(path, io::open_mode::OVERRIDE)



	function cin()
		=> build_in(io_cin)

	function fin(path)
		=> build_in(io_fin)

	function strin(str)
		=> build_in(io_strin)


	
	function print(stream, value) 
		=> build_in(io_print)
	
	function read(stream)
		=> build_in(io_read)

	function read_str(stream)
		=> build_in(io_read_str)

	function readln(stream)
		=> build_in(io_readln)

	function read_bool(stream)
		=> build_in(io_read_bool)

	function read_char(stream)
		=> build_in(io_read_char)

	function read_int(stream)
		=> build_in(io_read_int)

	function read_float(stream)
		=> build_in(io_read_float)

	function read_all(stream)
		=> build_in(io_read_all)


	
	function is_eof(stream) const => build_in(io_is_eof)

	function print(value) => print(cout(), value)

	function println(stream, value) {
		print(stream, value);
		print(stream, "\n");
	}

	function println(value) {
		var stream = cout();
		print(stream, value);
		print(stream, "\n");
	}

	function read() 
		=> read(cin())
	
	function read_str()
		=> read(cin())
	
	function readln()
		=> readln(cin())
	
	function read_bool()  
		=> read_bool(cin())

	function read_char()  
		=> read_char(cin())
	
	function read_int()   
		=> read_int(cin())
	
	function read_float() 
		=> read_float(cin())
}
)###";
