#pragma once
#include "lex/lexing.hxx"
#include "parse/parse.hxx"
#include "analyze/analyze.hxx"
#include "optimize/optimize.hxx"
#include "compile/compile.hxx"
#include "peephole/peephole.hxx"
#include "assemble/assemble.hxx"
#include "print/print.hxx"
#include "read_sources/read_sources.hxx"
#include "transpile/cxx/transpile_c.hxx"

#include "source/FileSource.hxx"
#include "source/StringSource.hxx"