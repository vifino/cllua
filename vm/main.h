#define ch_signature "\033Lua"
#define ch_version 0x51

typedef struct {
	char a;
	int b;
	int c;
	char op;
} iABC;

typedef struct {
	char a;
	int bx;
	char op;
} iABx;

typedef struct {
	char a;
	int sBx;
	char op;
} iAsBx;

typedef struct {
	ch_string name;
	int lineDefined;
	int lineDefinedLast;
	char nUpvals;
	char nParams;
	char varargMode;
	char nRegisters;
	ch_instr* instrs;
	ch_const* consts;
	ch_func* funcs;	
} ch_chunk

#define op_move       0
#define op_loadk      1
#define op_loadbool   2
#define op_loadnil    3
#define op_getupval   4
#define op_getglobal  5
#define op_gettable   6
#define op_setglobal  7
#define op_setupval   8
#define op_settable   9
#define op_newtable  10
#define op_self      11
#define op_add       12
#define op_sub       13
#define op_mul       14
#define op_div       15
#define op_mod       16
#define op_pow       17
#define op_unm       18
#define op_not       19
#define op_len       20
#define op_concat    21
#define op_jmp       22
#define op_eq        23
#define op_lt        24
#define op_le        25
#define op_test      26
#define op_testset   27
#define op_call      28
#define op_tailcall  29
#define op_return    30
#define op_forloop   31
#define op_forprep   32
#define op_tforloop  33
#define op_setlist   34
#define op_close     35
#define op_closure   36
#define op_vararg    37