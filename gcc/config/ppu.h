#undef TARGET_PPU
#define TARGET_PPU 1

// Default arguments when running powerpc-ppu-{ld,gcc,g++}
// without specifying -nostlib

// link against C standard library
#undef LIB_SPEC
// newlib splits the libc in three libraries, which get linked in
#define LIB_SPEC "-lc -lm -lg"

// Files that are linked before userland code.
// The %s tells GCC to look for these files in the library directory.
#undef STARTFILE_SPEC
// We want to use libc in a freestanding kernel developement environment.
// Thus, we disallow userland specific start and end objects to get linked in
// into our kernel.
//#define STARTFILE_SPEC "crt0.o%s crti.o%s crtbegin.o%s"

// Files that are linked after userland code.
#undef ENDFILE_SPEC
// Same as above we don't want to link in userland objects in our kernel.
//#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

// Don't automatically add extern "C" { } around header files.
#undef NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C 1

// Additional predefined macros.
// __ppu__ is used in newlib code to identify, if newlib targets our environment
#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()                                                                   \
	do {                                                                                           \
		builtin_define("__ppu__");                                                           \
		builtin_define("__unix__");                                                                \
		builtin_assert("system=ppu");                                                        \
		builtin_assert("system=unix");                                                             \
		builtin_assert("system=posix");                                                            \
	} while (0);
