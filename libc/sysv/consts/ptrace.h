#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_PTRACE_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_PTRACE_H_
#include "libc/runtime/symbolic.h"

#define PTRACE_GETREGSET SYMBOLIC(PTRACE_GETREGSET)
#define PTRACE_GETSIGMASK SYMBOLIC(PTRACE_GETSIGMASK)
#define PTRACE_INTERRUPT SYMBOLIC(PTRACE_INTERRUPT)
#define PTRACE_LISTEN SYMBOLIC(PTRACE_LISTEN)
#define PTRACE_PEEKSIGINFO SYMBOLIC(PTRACE_PEEKSIGINFO)
#define PTRACE_SECCOMP_GET_FILTER SYMBOLIC(PTRACE_SECCOMP_GET_FILTER)
#define PTRACE_SEIZE SYMBOLIC(PTRACE_SEIZE)
#define PTRACE_SETREGSET SYMBOLIC(PTRACE_SETREGSET)
#define PTRACE_SETSIGMASK SYMBOLIC(PTRACE_SETSIGMASK)
#define PTRACE_SYSCALL SYMBOLIC(PTRACE_SYSCALL)

#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

hidden extern const long PTRACE_GETREGSET;
hidden extern const long PTRACE_GETSIGMASK;
hidden extern const long PTRACE_INTERRUPT;
hidden extern const long PTRACE_LISTEN;
hidden extern const long PTRACE_PEEKSIGINFO;
hidden extern const long PTRACE_SECCOMP_GET_FILTER;
hidden extern const long PTRACE_SEIZE;
hidden extern const long PTRACE_SETREGSET;
hidden extern const long PTRACE_SETSIGMASK;
hidden extern const long PTRACE_SYSCALL;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_PTRACE_H_ */
