#pragma once
#include <unordered_map>
#include <string_view>
#include <tuple>
#include "ltn/InstructionSet.hxx"
namespace ltn::a {
	
	using namespace std::string_view_literals;
	
	enum struct ArgFormat {
		NONE,
		UINT, UINTx2,
		JUMP, JUMP_UINT,
		INT,
		FLOAT,
		BYTE, UINT_BYTExX,
	};
	
	struct InstructionData {
		Inst opcode;
		ArgFormat arg_format = ArgFormat::NONE;
	};

	using InstructionTable = std::unordered_map<
		std::string_view,
		InstructionData>;
	
	const InstructionTable instruction_table{
		{"error",         {Inst::ERROR}},
		{"exit",          {Inst::EXIT}},
		{"state",         {Inst::STATE}},
		{"try",           {Inst::TRY,        ArgFormat::JUMP}},
		{"throw",         {Inst::THROW}},

		// Binary operations
		{"add",           {Inst::ADD}},
		{"sub",           {Inst::SUB}},
		{"mlt",           {Inst::MLT}},
		{"div",           {Inst::DIV}},
		{"mod",           {Inst::MOD}},
		{"eql",           {Inst::EQL}},
		{"ueql",          {Inst::UEQL}},
		{"sml",           {Inst::SML}},
		{"bgr",           {Inst::BGR}},
		{"smleql",        {Inst::SMLEQL}},
		{"bgreql",        {Inst::BGREQL}},
		{"shift_l",       {Inst::SHIFT_L}},
		{"shift_r",       {Inst::SHIFT_R}},

		// Unary operations
		{"neg",           {Inst::NEG}},
		{"not",           {Inst::NOT}},
		{"inc",           {Inst::INC}},
		{"dec",           {Inst::DEC}},

		// Special comparison
		{"comp",          {Inst::COMP}},
		{"approx",        {Inst::APPROX}},
		{"between",       {Inst::BETWEEN}},

		// Values
		{"newu",          {Inst::NEWU,         ArgFormat::UINT}},
		{"newi",          {Inst::NEWI,         ArgFormat::INT}},
		{"newf",          {Inst::NEWF,         ArgFormat::FLOAT}},
		{"newc",          {Inst::NEWC,         ArgFormat::BYTE}},
		{"true",          {Inst::TRUE}},
		{"false",         {Inst::FALSE}},
		{"null",          {Inst::NVLL}},
		
		// Allocations
		{"newarr",        {Inst::NEWARR,       ArgFormat::UINT}},
		{"newstr",        {Inst::NEWSTR,       ArgFormat::UINT_BYTExX}},
		{"newout",        {Inst::NEWOUT,       ArgFormat::BYTE}},
		{"newin",         {Inst::NEWIN,        ArgFormat::BYTE}},
		{"newfx",         {Inst::NEWFX,        ArgFormat::JUMP_UINT}},
		{"newclock",      {Inst::NEWCLOCK}},
		{"newstruct",     {Inst::NEWSTRUCT}},
		{"newrange",      {Inst::NEWRANGE}},
		{"newstack",      {Inst::NEWSTACK}},
		{"newqueue",      {Inst::NEWQUEUE}},
		{"newmap",        {Inst::NEWMAP}},
		{"newrng",        {Inst::NEWRNG,       ArgFormat::BYTE}},

		// Control flow
		{"jump",          {Inst::JUMP,         ArgFormat::JUMP}},
		{"call",          {Inst::CALL,         ArgFormat::JUMP}},
		{"parameters",    {Inst::PARAMETERS,   ArgFormat::BYTE}},
		{"return",        {Inst::RETURN}},
		{"ifelse",        {Inst::IF,           ArgFormat::JUMP}},

		// Functional
		{"invoke",        {Inst::INVOKE}},
		{"external",      {Inst::EXTERNAL}},
		{"capture",       {Inst::CAPTURE}},

		// Memory
		{"read",          {Inst::READ}},
		{"write",         {Inst::WRITE}},
		{"scrap",         {Inst::SCRAP}},
		{"duplicate",     {Inst::DUPLICATE}},
		{"makevar",       {Inst::MAKEVAR}},
		{"read_x",        {Inst::READ_X,       ArgFormat::UINT}},
		{"write_x",       {Inst::WRITE_X,      ArgFormat::UINT}},
		{"swap",          {Inst::SWAP}},

		{"read_0",        {Inst::READ_0}},
		{"read_1",        {Inst::READ_1}},
		{"read_2",        {Inst::READ_2}},
		{"read_3",        {Inst::READ_3}},
		{"write_0",       {Inst::WRITE_0}},
		{"write_1",       {Inst::WRITE_1}},
		{"write_2",       {Inst::WRITE_2}},
		{"write_3",       {Inst::WRITE_3}},

		// Io
		{"out",           {Inst::OUT}},
		{"stylize",       {Inst::STYLIZE,      ArgFormat::BYTE}},
		{"close_stream",  {Inst::CLOSE_STREAM,      ArgFormat::BYTE}},
		{"in_str",        {Inst::IN_STR}},
		{"in_line",       {Inst::IN_LINE}},
		{"in_bool",       {Inst::IN_BOOL}},
		{"in_char",       {Inst::IN_CHAR}},
		{"in_int",        {Inst::IN_INT}},
		{"in_float",      {Inst::IN_FLOAT}},
		{"in_all",        {Inst::IN_ALL}},
		{"is_eof",        {Inst::IS_EOF}},
		{"is_good",       {Inst::IS_GOOD}},

		// Math
		{"min",           {Inst::MIN}},
		{"max",           {Inst::MAX}},
		{"round",         {Inst::ROUND}},
		{"floor",         {Inst::FLOOR}},
		{"ceil",          {Inst::CEIL}},
		{"abs",           {Inst::ABS}},
		{"hypot",         {Inst::HYPOT}},
		{"sqrt",          {Inst::SQRT}},
		{"log",           {Inst::LOG}},
		{"ln",            {Inst::LN}},
		{"pow",           {Inst::POW}},

		{"sin",           {Inst::SIN}},
		{"cos",           {Inst::COS}},
		{"tan",           {Inst::TAN}},

		// bitwise
		{"bitand",        {Inst::BITAND}},
		{"bitor",         {Inst::BITOR}},
		{"bitxor",        {Inst::BITXOR}},

		// Array Utils
		{"size",          {Inst::SIZE}},
		{"at",            {Inst::AT}},
		{"at_write",      {Inst::AT_WRITE}},
		{"front",         {Inst::FRONT}},
		{"back",          {Inst::BACK}},
		{"insert",        {Inst::INSERT,       ArgFormat::BYTE}},
		{"remove",        {Inst::REMOVE,       ArgFormat::BYTE}},
		{"begin",         {Inst::BEGIN}},
		{"end",           {Inst::END}},
		{"push",          {Inst::PUSH}},
		{"pop",           {Inst::POP}},
		{"peek",          {Inst::PEEK}},
		{"contains",      {Inst::CONTAINS}},

		// Chrono utils
		{"cast_char",     {Inst::CAST_CHAR}},
		{"cast_bool",     {Inst::CAST_BOOL}},
		{"cast_int",      {Inst::CAST_INT}},
		{"cast_float",    {Inst::CAST_FLOAT}},
		{"cast_string",   {Inst::CAST_STRING}},
		{"cast_array",    {Inst::CAST_ARRAY}},

		// Type utils
		{"typeid",        {Inst::TYPEID}},
		{"clone",         {Inst::CLONE}},

		{"member_read",   {Inst::MEMBER_READ,  ArgFormat::UINT}},
		{"member_write",  {Inst::MEMBER_WRITE, ArgFormat::UINT}},

		// Build-ins
		{"algorithm",     {Inst::ALGORITHM,    ArgFormat::BYTE}},
		{"random",        {Inst::RANDOM,       ArgFormat::BYTE}},
	};
}