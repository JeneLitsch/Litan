#include "inst.hxx"

namespace ltn::c::inst {
	Inst label(const std::string & name) {
		return InstLabel{
			.label = name,
		};
	}

    Inst exit() {
        return InstNone { 
            .name = "exit",
            .opcode = OpCode::EXIT,
        };
    }
	Inst error() {
        return InstNone {
            .name = "error",
            .opcode = OpCode::ERROR,
        };
    }
	Inst trY(const std::string & label) {
        return InstJump {
            .name = "try",
            .opcode = OpCode::TRY,
            .label = label,
        };
    }
	Inst thr0w() {
        return InstNone {
            .name = "throw",
            .opcode = OpCode::THROW,
        };
    }
	Inst build_in(std::uint16_t code) {
        return InstUint16 {
            .name = "build_in",
            .opcode = OpCode::BUILD_IN,
			.value = code,
        };
    }


	
	Inst add() {
        return InstNone {
            .name = "add",
            .opcode = OpCode::ADD,
        };
    }
	Inst sub() {
        return InstNone {
            .name = "sub",
            .opcode = OpCode::SUB,
        };
    }
	Inst mlt() {
        return InstNone {
            .name = "mlt",
            .opcode = OpCode::MLT,
        };
    }
	Inst div() {
        return InstNone {
            .name = "div",
            .opcode = OpCode::DIV,
        };
    }
	Inst mod() {
        return InstNone {
            .name = "mod",
            .opcode = OpCode::MOD,
        };
    }

	Inst eql() {
        return InstNone {
            .name = "eql",
            .opcode = OpCode::EQL,
        };
    }
	Inst ueql() {
        return InstNone {
            .name = "ueql",
            .opcode = OpCode::UEQL,
        };
    }
	Inst lt() {
        return InstNone {
            .name = "lt",
            .opcode = OpCode::LT,
        };
    }
	Inst gt() {
        return InstNone {
            .name = "gt",
            .opcode = OpCode::GT,
        };
    }
	Inst lt_eql() {
        return InstNone {
            .name = "lt_eql",
            .opcode = OpCode::LTEQL,
        };
    }
	Inst gt_eql() {
        return InstNone {
            .name = "gt_eql",
            .opcode = OpCode::GTEQL,
        };
    }

	Inst shift_l() {
        return InstNone {
            .name = "shilf_l",
            .opcode = OpCode::SHIFT_L,
        };
    }
	Inst shift_r() {
        return InstNone {
            .name = "shilf_r",
            .opcode = OpCode::SHIFT_R,
        };
    }

	Inst neg() {
        return InstNone {
            .name = "neg",
            .opcode = OpCode::NEG,
        };
    }
	Inst n0t() {
        return InstNone {
            .name = "not",
            .opcode = OpCode::NOT,
        };
    }
	Inst inc() {
        return InstNone {
            .name = "inc",
            .opcode = OpCode::INC,
        };
    }
	Inst dec() {
        return InstNone {
            .name = "dec",
            .opcode = OpCode::DEC,
        };
    }
	Inst deref() {
		return InstNone {
            .name = "deref",
            .opcode = OpCode::DEREF,
        };
	}



	Inst comp() {
        return InstNone {
            .name = "comp",
            .opcode = OpCode::COMP,
        };
    }



	Inst newi(std::int64_t i64) {
		return InstInt64 {
			.name = "newi",
			.opcode = OpCode::NEWI,
			.value = i64,
		};
	}
	Inst newf(stx::float64_t f64) {
		return InstFloat {
			.name = "newf",
			.opcode = OpCode::NEWF,
			.value = f64,
		};
	}
	Inst newc(std::uint8_t u8) {
		return InstByte {
			.name = "newc",
			.opcode = OpCode::NEWC,
			.value = u8
		};
	}
	Inst bool_true() {
		return InstNone {
			.name = "true",
			.opcode = OpCode::TRUE,
		};
	}
	Inst bool_false() {
		return InstNone {
			.name = "false",
			.opcode = OpCode::FALSE,
		};
	}
	Inst null() {
		return InstNone {
			.name = "null",
			.opcode = OpCode::NVLL,
		};
	}
	Inst newi_small(std::int8_t i8) {
		return InstByte {
			.name = "newi_small",
			.opcode = OpCode::NEWI_SMALL,
			.value = static_cast<std::uint8_t>(i8),
		};
	}



	Inst newarr(std::uint64_t size) {
		return InstUint64 {
			.name = "newarr",
			.opcode = OpCode::NEWARR,
			.value = size,
		};
	}
	Inst newstr(std::vector<std::uint8_t> bytes) {
		return InstBytex0 {
			.name = "newstr",
			.opcode = OpCode::NEWSTR,
			.bytes = bytes,
		};
	}
	Inst newstr(const std::string & str) {
		return newstr(std::vector<std::uint8_t>(str.begin(), str.end()));
	}

	Inst newfx(const std::string & label) {
		return InstCall {
			.name = "newfx",
			.opcode = OpCode::NEWFX,
			.label = label,
		};
	}
	Inst newclock() {
		return InstNone {
			.name = "newclock",
			.opcode = OpCode::NEWCLOCK,
		};
	}
	Inst newstruct() {
		return InstNone {
			.name = "newstruct",
			.opcode = OpCode::NEWSTRUCT,
		};
	}
	Inst newstack() {
		return InstNone {
			.name = "newstack",
			.opcode = OpCode::NEWSTACK,
		};
	}
	Inst newqueue() {
		return InstNone {
			.name = "newqueue",
			.opcode = OpCode::NEWQUEUE,
		};
	}
	Inst newmap() {
		return InstNone {
			.name = "newmap",
			.opcode = OpCode::NEWMAP,
		};
	}
	Inst newtuple(std::uint64_t size) {
		return InstUint64 {
			.name = "newtuple",
			.opcode = OpCode::NEWTUPLE,
			.value = size,
		};
	}
	Inst newtype(std::vector<std::uint8_t> bytes) {
		return InstBytex0 {
			.name = "newtype",
			.opcode = OpCode::NEWTYPE,
			.bytes = bytes,
		};
	}



	Inst jump(const std::string & label) {
		return InstJump {
			.name = "jump",
			.opcode = OpCode::JUMP,
			.label = label,
		};
	}
	Inst call(const std::string & label) {
		return InstCall {
			.name = "call",
			.opcode = OpCode::CALL,
			.label = label,
		};
	}
	Inst retvrn() {
		return InstNone {
			.name = "return",
			.opcode = OpCode::RETURN,
		};
	}
	Inst ifelse(const std::string & label) {
		return InstJump {
			.name = "ifelse",
			.opcode = OpCode::IF,
			.label = label,
		};
	}	
	Inst invoke(std::uint8_t arity) {
		return InstByte {
			.name = "invoke",
			.opcode = OpCode::INVOKE,
			.value = arity,
		};
	}
	Inst invoke_variadic() {
		return InstNone {
			.name = "invoke_variadic",
			.opcode = OpCode::INVOKE_VARIADIC,
		};
	}
	Inst capture() {
		return InstNone {
			.name = "capture",
			.opcode = OpCode::CAPTURE,
		};
	}
	Inst for_next(const std::string & label) {
		return InstJump {
			.name = "for_next",
			.opcode = OpCode::FOR_NEXT,
			.label = label,
		};
	}
	Inst yield() {
		return InstNone {
            .name = "yield",
            .opcode = OpCode::YIELD,
        };
	}
	Inst co_retvrn() {
		return InstNone {
            .name = "co_return",
            .opcode = OpCode::CO_RETURN,
        };
	}
	Inst co_dump() {
		return InstNone {
            .name = "co_dump",
            .opcode = OpCode::CO_DUMP,
        };
	}



	Inst scrap() {
		return InstNone {
			.name = "scrap",
			.opcode = OpCode::SCRAP,
		};
	}

	Inst duplicate() {
		return InstNone {
			.name = "duplicate",
			.opcode = OpCode::DUPLICATE,
		};
	}

	Inst read_x(std::uint64_t u64) {
		return InstUint64 {
			.name = "read_x",
			.opcode = OpCode::READ_X,
			.value = u64,
		};
	}

	Inst write_x(std::uint64_t u64) {
		return InstUint64 {
			.name = "write_x",
			.opcode = OpCode::WRITE_X,
			.value = u64,
		};
	}

	Inst swap() {
		return InstNone {
			.name = "swap",
			.opcode = OpCode::SWAP,
		};
	}

	Inst unpack(std::uint8_t size) {
		return InstByte {
			.name = "unpack",
			.opcode = OpCode::UNPACK,
			.value = size,
		};
	}



	Inst read_0() {
		return InstNone {
			.name = "read_0",
			.opcode = OpCode::READ_0,
		};
	}
	Inst read_1() {
		return InstNone {
			.name = "read_1",
			.opcode = OpCode::READ_1,
		};
	}
	Inst read_2() {
		return InstNone {
			.name = "read_2",
			.opcode = OpCode::READ_2,
		};
	}
	Inst read_3() {
		return InstNone {
			.name = "read_3",
			.opcode = OpCode::READ_3,
		};
	}
	Inst write_0() {
		return InstNone {
			.name = "write_0",
			.opcode = OpCode::WRITE_0,
		};
	}
	Inst write_1() {
		return InstNone {
			.name = "write_1",
			.opcode = OpCode::WRITE_1,
		};
	}
	Inst write_2() {
		return InstNone {
			.name = "write_2",
			.opcode = OpCode::WRITE_2,
		};
	}
	Inst write_3() {
		return InstNone {
			.name = "write_3",
			.opcode = OpCode::WRITE_3,
		};
	}



	Inst newi_const_0() {
		return InstNone {
			.name = "newi_const_0",
			.opcode = OpCode::NEWI_CONST_0,
		};
	}

	Inst newi_const_1() {
		return InstNone {
			.name = "newi_const_1",
			.opcode = OpCode::NEWI_CONST_1,
		};
	}

	Inst newi_const_2() {
		return InstNone {
			.name = "newi_const_2",
			.opcode = OpCode::NEWI_CONST_2,
		};
	}



	Inst pow() {
		return InstNone {
			.name = "pow",
			.opcode = OpCode::POW,
		};
	}
	Inst bit_and() {
		return InstNone {
			.name = "bit_and",
			.opcode = OpCode::BITAND,
		};
	}
	Inst bit_or() {
		return InstNone {
			.name = "bit_or",
			.opcode = OpCode::BITOR,
		};
	}
	Inst bit_xor() {
		return InstNone {
			.name = "bit_xor",
			.opcode = OpCode::BITXOR,
		};
	}
	Inst bit_not() {
		return InstNone {
			.name = "bit_not",
			.opcode = OpCode::BITNOT,
		};
	}
	Inst at() {
		return InstNone {
			.name = "at",
			.opcode = OpCode::AT,
		};
	}
	Inst at_write() {
		return InstNone {
			.name = "at_write",
			.opcode = OpCode::AT_WRITE,
		};
	}
	Inst iter() {
		return InstNone {
			.name = "iter",
			.opcode = OpCode::ITER,
		};
	}



	Inst cast_bool() {
		return InstNone {
			.name = "cast_bool",
			.opcode = OpCode::CAST_BOOL,
		};
	}
	Inst member_read(std::uint64_t id) {
		return InstUint64 {
			.name = "member_read",
			.opcode = OpCode::MEMBER_READ,
			.value = id,
		};
	}
	Inst member_write(std::uint64_t id) {
		return InstUint64 {
			.name = "member_write",
			.opcode = OpCode::MEMBER_WRITE,
			.value = id,
		};
	}
	Inst global_read(std::uint64_t id) {
		return InstUint64 {
			.name = "global_read",
			.opcode = OpCode::GLOBAL_READ,
			.value = id,
		};
	}
	Inst global_write(std::uint64_t id) {
		return InstUint64 {
			.name = "global_write",
			.opcode = OpCode::GLOBAL_WRITE,
			.value = id,
		};
	}
}