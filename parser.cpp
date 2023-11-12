/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <cstdio>
#include <cstdlib>

#include "ast.hpp"
#include "lexer.hpp"

/* Use yylineno from lexer file, since the main is in this file we need to use extern here */
extern int yylineno;


#line 83 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_and = 3,                      /* "and"  */
  YYSYMBOL_T_int = 4,                      /* "int"  */
  YYSYMBOL_T_then = 5,                     /* "then"  */
  YYSYMBOL_T_char = 6,                     /* "char"  */
  YYSYMBOL_T_mod = 7,                      /* "mod"  */
  YYSYMBOL_T_var = 8,                      /* "var"  */
  YYSYMBOL_T_div = 9,                      /* "div"  */
  YYSYMBOL_T_not = 10,                     /* "not"  */
  YYSYMBOL_T_while = 11,                   /* "while"  */
  YYSYMBOL_T_do = 12,                      /* "do"  */
  YYSYMBOL_T_nothing = 13,                 /* "nothing"  */
  YYSYMBOL_T_else = 14,                    /* "else"  */
  YYSYMBOL_T_or = 15,                      /* "or"  */
  YYSYMBOL_T_fun = 16,                     /* "fun"  */
  YYSYMBOL_T_ref = 17,                     /* "ref"  */
  YYSYMBOL_T_if = 18,                      /* "if"  */
  YYSYMBOL_T_return = 19,                  /* "return"  */
  YYSYMBOL_T_leq = 20,                     /* "leq"  */
  YYSYMBOL_T_geq = 21,                     /* "geq"  */
  YYSYMBOL_T_arr = 22,                     /* "arr"  */
  YYSYMBOL_T_id = 23,                      /* T_id  */
  YYSYMBOL_T_int_lit = 24,                 /* T_int_lit  */
  YYSYMBOL_T_char_lit = 25,                /* T_char_lit  */
  YYSYMBOL_T_string_lit = 26,              /* T_string_lit  */
  YYSYMBOL_27_ = 27,                       /* '='  */
  YYSYMBOL_28_ = 28,                       /* '#'  */
  YYSYMBOL_29_ = 29,                       /* '>'  */
  YYSYMBOL_30_ = 30,                       /* '<'  */
  YYSYMBOL_31_ = 31,                       /* '+'  */
  YYSYMBOL_32_ = 32,                       /* '-'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_UNARY = 34,                     /* UNARY  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* ')'  */
  YYSYMBOL_37_ = 37,                       /* ':'  */
  YYSYMBOL_38_ = 38,                       /* ';'  */
  YYSYMBOL_39_ = 39,                       /* ','  */
  YYSYMBOL_40_ = 40,                       /* '['  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_42_ = 42,                       /* '{'  */
  YYSYMBOL_43_ = 43,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_func_def = 46,                  /* func_def  */
  YYSYMBOL_local_def_list = 47,            /* local_def_list  */
  YYSYMBOL_header = 48,                    /* header  */
  YYSYMBOL_fpar_def_list = 49,             /* fpar_def_list  */
  YYSYMBOL_fpar_def_rest = 50,             /* fpar_def_rest  */
  YYSYMBOL_fpar_def = 51,                  /* fpar_def  */
  YYSYMBOL_id_rest = 52,                   /* id_rest  */
  YYSYMBOL_data_type = 53,                 /* data_type  */
  YYSYMBOL_type = 54,                      /* type  */
  YYSYMBOL_int_const_bracket_list_var = 55, /* int_const_bracket_list_var  */
  YYSYMBOL_ret_type = 56,                  /* ret_type  */
  YYSYMBOL_int_const_bracket_list = 57,    /* int_const_bracket_list  */
  YYSYMBOL_fpar_type = 58,                 /* fpar_type  */
  YYSYMBOL_local_def = 59,                 /* local_def  */
  YYSYMBOL_func_decl = 60,                 /* func_decl  */
  YYSYMBOL_var_def = 61,                   /* var_def  */
  YYSYMBOL_stmt = 62,                      /* stmt  */
  YYSYMBOL_block = 63,                     /* block  */
  YYSYMBOL_stmt_list = 64,                 /* stmt_list  */
  YYSYMBOL_func_call = 65,                 /* func_call  */
  YYSYMBOL_expr_list = 66,                 /* expr_list  */
  YYSYMBOL_expr_rest = 67,                 /* expr_rest  */
  YYSYMBOL_l_value = 68,                   /* l_value  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_cond = 70                       /* cond  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    28,     2,     2,     2,     2,
      35,    36,    33,    31,    39,    32,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,    38,
      30,    27,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   113,   113,   117,   121,   122,   126,   134,   135,   139,
     140,   144,   150,   159,   160,   169,   170,   174,   178,   179,
     183,   184,   188,   189,   190,   194,   195,   199,   200,   201,
     205,   209,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   229,   233,   234,   238,   247,   248,   252,   253,   257,
     258,   259,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"and\"", "\"int\"",
  "\"then\"", "\"char\"", "\"mod\"", "\"var\"", "\"div\"", "\"not\"",
  "\"while\"", "\"do\"", "\"nothing\"", "\"else\"", "\"or\"", "\"fun\"",
  "\"ref\"", "\"if\"", "\"return\"", "\"leq\"", "\"geq\"", "\"arr\"",
  "T_id", "T_int_lit", "T_char_lit", "T_string_lit", "'='", "'#'", "'>'",
  "'<'", "'+'", "'-'", "'*'", "UNARY", "'('", "')'", "':'", "';'", "','",
  "'['", "']'", "'{'", "'}'", "$accept", "program", "func_def",
  "local_def_list", "header", "fpar_def_list", "fpar_def_rest", "fpar_def",
  "id_rest", "data_type", "type", "int_const_bracket_list_var", "ret_type",
  "int_const_bracket_list", "fpar_type", "local_def", "func_decl",
  "var_def", "stmt", "block", "stmt_list", "func_call", "expr_list",
  "expr_rest", "l_value", "expr", "cond", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-85)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-46)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -6,   -10,    27,   -85,   -85,    25,   -85,     1,    30,   -85,
     -85,   -85,    36,   -85,   -85,   -85,   -85,    45,    68,    70,
      54,   -85,    62,   -85,    66,    86,     9,   150,   150,   163,
      81,   -85,   -85,   -85,   -85,   -85,    77,   -14,    12,    97,
     -85,    24,    41,   -85,   150,   -85,   -85,   179,   179,   150,
     -85,    82,   138,   120,    79,   179,   -85,    80,    85,   -85,
     179,   179,   -85,   -85,   -85,   -85,   -85,    49,    41,   -85,
      87,   -85,   -85,   -85,   110,     8,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   150,    72,   150,
      72,     5,   -85,   100,   179,    96,    -2,    41,    93,   -85,
     104,   -85,   -85,   -85,   -85,   -85,   117,   117,   117,   117,
     117,   117,   144,   144,   -85,   -85,   -85,   149,   140,   -85,
      69,   -85,   -85,   -85,    -9,   131,    72,   -85,   115,   -85,
     121,   116,   -85,   -85,   139,   -85,   123,   -85
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     4,     0,     1,     0,     9,    13,
      42,    27,     4,     5,    28,    29,     3,     0,    13,     0,
       0,    30,     0,    13,     8,     0,     0,     0,     0,     0,
      49,    50,    32,    41,    43,    34,     0,     0,     0,     0,
      10,     0,     0,    14,     0,    52,    53,     0,     0,     0,
      56,    54,     0,     0,     0,     0,    39,     0,    47,    35,
       0,     0,    15,    16,    21,    20,     6,     0,     0,    18,
       0,    65,    57,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40,     0,     0,     0,     0,     0,    25,    12,
      17,    31,    55,    64,    63,    62,    72,    73,    68,    69,
      71,    70,    59,    60,    61,    66,    38,    67,    37,    44,
      46,    33,    51,    11,     0,     0,     0,    48,     0,    22,
      26,     0,    36,    23,     0,    19,     0,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   -85,   155,   -85,   165,   -85,   -85,   -85,    17,    37,
     -85,   -85,   -85,   -85,    83,   -85,   -85,   -85,   -84,   171,
     -85,   -20,   -85,   -85,   -19,   -27,   -25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     7,     4,    17,    18,    24,    19,    98,
      70,   100,    66,   130,    99,    13,    14,    15,    34,    35,
      20,    50,    93,    94,    51,    52,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    37,    57,    54,   116,    76,   118,    77,    60,     9,
       1,    87,    76,     5,    77,   128,    62,     1,    63,    71,
      72,    73,    74,    89,    75,    64,    61,     6,    91,    84,
      85,    86,   129,    95,    96,    25,    84,    85,    86,   122,
      39,   102,   132,    10,   103,    62,    42,    63,    43,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
       8,    68,   115,    43,   117,    27,    -7,   120,    36,    37,
      36,    37,    28,    29,    21,    65,    76,    30,    77,    69,
      31,    22,    87,    27,    90,    23,    97,    76,    43,    77,
      28,    29,    32,    26,    89,    30,    10,    33,    31,    38,
      84,    85,    86,    76,    40,    77,    36,    37,   127,    41,
      32,    84,    85,    86,    10,    59,    58,    76,    92,    77,
      67,   -45,    61,    87,    76,   101,    77,    84,    85,    86,
      78,    79,    88,   124,   121,    89,   119,    80,    81,    82,
      83,    84,    85,    86,   125,    76,   102,    77,    84,    85,
      86,    76,    87,    77,   126,   131,   133,   135,    78,    79,
      44,   134,    11,   136,   137,    80,    81,    82,    83,    84,
      85,    86,    12,    30,    45,    46,    31,    86,    16,     0,
     123,    47,    48,     0,     0,    49,    30,    45,    46,    31,
       0,     0,     0,     0,    47,    48,     0,     0,    55,     0,
       0,    56,    30,    45,    46,    31,     0,     0,     0,     0,
      47,    48,     0,     0,    55
};

static const yytype_int8 yycheck[] =
{
      20,    20,    29,    28,    88,     7,    90,     9,    22,     8,
      16,     3,     7,    23,     9,    24,     4,    16,     6,    44,
      47,    48,    49,    15,    49,    13,    40,     0,    55,    31,
      32,    33,    41,    60,    61,    18,    31,    32,    33,    41,
      23,    36,   126,    42,    36,     4,    37,     6,    39,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      35,    37,    87,    39,    89,    11,    36,    94,    88,    88,
      90,    90,    18,    19,    38,    38,     7,    23,     9,    42,
      26,    36,     3,    11,     5,    17,    37,     7,    39,     9,
      18,    19,    38,    23,    15,    23,    42,    43,    26,    37,
      31,    32,    33,     7,    38,     9,   126,   126,    39,    23,
      38,    31,    32,    33,    42,    38,    35,     7,    38,     9,
      23,    36,    40,     3,     7,    38,     9,    31,    32,    33,
      20,    21,    12,    40,    38,    15,    36,    27,    28,    29,
      30,    31,    32,    33,    40,     7,    36,     9,    31,    32,
      33,     7,     3,     9,    14,    24,    41,    41,    20,    21,
      10,    40,     7,    24,    41,    27,    28,    29,    30,    31,
      32,    33,     7,    23,    24,    25,    26,    33,     7,    -1,
      97,    31,    32,    -1,    -1,    35,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    35,    -1,
      -1,    38,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    32,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    16,    45,    46,    48,    23,     0,    47,    35,     8,
      42,    46,    48,    59,    60,    61,    63,    49,    50,    52,
      64,    38,    36,    17,    51,    52,    23,    11,    18,    19,
      23,    26,    38,    43,    62,    63,    65,    68,    37,    52,
      38,    23,    37,    39,    10,    24,    25,    31,    32,    35,
      65,    68,    69,    70,    70,    35,    38,    69,    35,    38,
      22,    40,     4,     6,    13,    53,    56,    23,    37,    53,
      54,    70,    69,    69,    69,    70,     7,     9,    20,    21,
      27,    28,    29,    30,    31,    32,    33,     3,    12,    15,
       5,    69,    38,    66,    67,    69,    69,    37,    53,    58,
      55,    38,    36,    36,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    70,    62,    70,    62,    36,
      69,    38,    41,    58,    40,    40,    14,    39,    24,    41,
      57,    24,    62,    41,    40,    41,    24,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    47,    47,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    53,    53,    54,    55,    55,
      56,    56,    57,    57,    57,    58,    58,    59,    59,    59,
      60,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    64,    64,    65,    66,    66,    67,    67,    68,
      68,    68,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     0,     2,     7,     0,     2,     0,
       3,     5,     4,     0,     3,     1,     1,     2,     0,     4,
       1,     1,     1,     2,     4,     1,     3,     1,     1,     1,
       2,     6,     1,     4,     1,     2,     6,     4,     4,     2,
       3,     3,     0,     2,     4,     0,     2,     0,     3,     1,
       1,     4,     1,     1,     1,     3,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: func_def  */
#line 113 "parser.y"
             { (yyval.program) = new Program((yyvsp[0].funcdef)); std::cout << *(yyval.program) << std::endl; }
#line 1515 "parser.cpp"
    break;

  case 3: /* func_def: header local_def_list block  */
#line 117 "parser.y"
                                { (yyval.funcdef) = new FuncDef((yyvsp[-2].header), (yyvsp[-1].vector_local_def), (yyvsp[0].block)); }
#line 1521 "parser.cpp"
    break;

  case 4: /* local_def_list: %empty  */
#line 121 "parser.y"
                              { (yyval.vector_local_def) = new std::vector<LocalDef *>(); }
#line 1527 "parser.cpp"
    break;

  case 5: /* local_def_list: local_def_list local_def  */
#line 122 "parser.y"
                              { (yyvsp[-1].vector_local_def)->push_back((yyvsp[0].localdef)); (yyval.vector_local_def) = (yyvsp[-1].vector_local_def);         }
#line 1533 "parser.cpp"
    break;

  case 6: /* header: "fun" T_id '(' fpar_def_list ')' ':' ret_type  */
#line 126 "parser.y"
                                                  { 
        Id *id; 
        id = new Id(*(yyvsp[-5].str_val));
        (yyval.header) = new Header(id, (yyvsp[-3].vector_fpar_def), (yyvsp[0].data_type)); 
    }
#line 1543 "parser.cpp"
    break;

  case 7: /* fpar_def_list: %empty  */
#line 134 "parser.y"
                            { (yyval.vector_fpar_def) = new std::vector<FParDef *>(); }
#line 1549 "parser.cpp"
    break;

  case 8: /* fpar_def_list: fpar_def_rest fpar_def  */
#line 135 "parser.y"
                            { (yyvsp[-1].vector_fpar_def)->push_back((yyvsp[0].fpar_def)); (yyval.vector_fpar_def) = (yyvsp[-1].vector_fpar_def);        }
#line 1555 "parser.cpp"
    break;

  case 9: /* fpar_def_rest: %empty  */
#line 139 "parser.y"
                                { (yyval.vector_fpar_def) = new std::vector<FParDef *>(); }
#line 1561 "parser.cpp"
    break;

  case 10: /* fpar_def_rest: fpar_def_rest fpar_def ';'  */
#line 140 "parser.y"
                                { (yyvsp[-2].vector_fpar_def)->push_back((yyvsp[-1].fpar_def)); (yyval.vector_fpar_def) = (yyvsp[-2].vector_fpar_def);        }
#line 1567 "parser.cpp"
    break;

  case 11: /* fpar_def: "ref" id_rest T_id ':' fpar_type  */
#line 144 "parser.y"
                                     { 
        Id *id; 
        id = new Id(*(yyvsp[-2].str_val));
        (yyvsp[-3].id_defs)->push_back(id); 
        (yyval.fpar_def) = new FParDef((yyvsp[-3].id_defs), (yyvsp[0].type), true);  
    }
#line 1578 "parser.cpp"
    break;

  case 12: /* fpar_def: id_rest T_id ':' fpar_type  */
#line 150 "parser.y"
                               { 
        Id *id; 
        id = new Id(*(yyvsp[-2].str_val));
        (yyvsp[-3].id_defs)->push_back(id); 
        (yyval.fpar_def) = new FParDef((yyvsp[-3].id_defs), (yyvsp[0].type), false); 
    }
#line 1589 "parser.cpp"
    break;

  case 13: /* id_rest: %empty  */
#line 159 "parser.y"
                     { (yyval.id_defs) = new std::vector<Id *>(); }
#line 1595 "parser.cpp"
    break;

  case 14: /* id_rest: id_rest T_id ','  */
#line 160 "parser.y"
                     { 
        Id *id; 
        id = new Id(*(yyvsp[-1].str_val));
        (yyvsp[-2].id_defs)->push_back(id); 
        (yyval.id_defs) = (yyvsp[-2].id_defs);   
    }
#line 1606 "parser.cpp"
    break;

  case 15: /* data_type: "int"  */
#line 169 "parser.y"
            { (yyval.data_type) = DATA_TYPE_int;  }
#line 1612 "parser.cpp"
    break;

  case 16: /* data_type: "char"  */
#line 170 "parser.y"
            { (yyval.data_type) = DATA_TYPE_char; }
#line 1618 "parser.cpp"
    break;

  case 17: /* type: data_type int_const_bracket_list_var  */
#line 174 "parser.y"
                                                 { (yyval.type) = new Type((yyvsp[-1].data_type), (yyvsp[0].int_vec)); }
#line 1624 "parser.cpp"
    break;

  case 18: /* int_const_bracket_list_var: %empty  */
#line 178 "parser.y"
                                                 { (yyval.int_vec) = new std::vector<int>(); }
#line 1630 "parser.cpp"
    break;

  case 19: /* int_const_bracket_list_var: int_const_bracket_list_var '[' T_int_lit ']'  */
#line 179 "parser.y"
                                                 { (yyvsp[-3].int_vec)->push_back((yyvsp[-1].int_val)); (yyval.int_vec) = (yyvsp[-3].int_vec);  }
#line 1636 "parser.cpp"
    break;

  case 20: /* ret_type: data_type  */
#line 183 "parser.y"
               { (yyval.data_type) = (yyvsp[0].data_type);                }
#line 1642 "parser.cpp"
    break;

  case 21: /* ret_type: "nothing"  */
#line 184 "parser.y"
               { (yyval.data_type) = DATA_TYPE_nothing; }
#line 1648 "parser.cpp"
    break;

  case 22: /* int_const_bracket_list: ']'  */
#line 188 "parser.y"
                                              { (yyval.int_vec) = new std::vector<int>(); (yyval.int_vec)->push_back(INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE); }
#line 1654 "parser.cpp"
    break;

  case 23: /* int_const_bracket_list: T_int_lit ']'  */
#line 189 "parser.y"
                                              { (yyval.int_vec) = new std::vector<int>(); (yyval.int_vec)->push_back((yyvsp[-1].int_val));                                            }
#line 1660 "parser.cpp"
    break;

  case 24: /* int_const_bracket_list: int_const_bracket_list '[' T_int_lit ']'  */
#line 190 "parser.y"
                                              { (yyvsp[-3].int_vec)->push_back((yyvsp[-1].int_val)); (yyval.int_vec) = (yyvsp[-3].int_vec);                                                                }
#line 1666 "parser.cpp"
    break;

  case 25: /* fpar_type: data_type  */
#line 194 "parser.y"
                                         { (yyval.type) = new Type((yyvsp[0].data_type), new std::vector<int>()); }
#line 1672 "parser.cpp"
    break;

  case 26: /* fpar_type: data_type '[' int_const_bracket_list  */
#line 195 "parser.y"
                                         { (yyval.type) = new Type((yyvsp[-2].data_type), (yyvsp[0].int_vec));                     }
#line 1678 "parser.cpp"
    break;

  case 27: /* local_def: func_def  */
#line 199 "parser.y"
              { (yyval.localdef) = (yyvsp[0].funcdef); }
#line 1684 "parser.cpp"
    break;

  case 28: /* local_def: func_decl  */
#line 200 "parser.y"
              { (yyval.localdef) = (yyvsp[0].func_decl); }
#line 1690 "parser.cpp"
    break;

  case 29: /* local_def: var_def  */
#line 201 "parser.y"
              { (yyval.localdef) = (yyvsp[0].var_def); }
#line 1696 "parser.cpp"
    break;

  case 30: /* func_decl: header ';'  */
#line 205 "parser.y"
               { (yyval.func_decl) = new FuncDecl((yyvsp[-1].header)); }
#line 1702 "parser.cpp"
    break;

  case 31: /* var_def: "var" id_rest T_id ':' type ';'  */
#line 209 "parser.y"
                                     {
        Id *id; 
        id = new Id(*(yyvsp[-3].str_val));
        (yyvsp[-4].id_defs)->push_back(id);
        (yyval.var_def) = new VarDef((yyvsp[-4].id_defs), (yyvsp[-1].type)); 
    }
#line 1713 "parser.cpp"
    break;

  case 32: /* stmt: ';'  */
#line 218 "parser.y"
                                      { /* nothing */              }
#line 1719 "parser.cpp"
    break;

  case 33: /* stmt: l_value "arr" expr ';'  */
#line 219 "parser.y"
                                      { (yyval.stmt) = new Assign((yyvsp[-3].abstractlvalue), (yyvsp[-1].expr));   }
#line 1725 "parser.cpp"
    break;

  case 34: /* stmt: block  */
#line 220 "parser.y"
                                      { (yyval.stmt) = (yyvsp[0].block);                   }
#line 1731 "parser.cpp"
    break;

  case 35: /* stmt: func_call ';'  */
#line 221 "parser.y"
                                      { (yyval.stmt) = new FuncCallStmt((yyvsp[-1].funccall)); }
#line 1737 "parser.cpp"
    break;

  case 36: /* stmt: "if" cond "then" stmt "else" stmt  */
#line 222 "parser.y"
                                      { (yyval.stmt) = new If((yyvsp[-4].cond), (yyvsp[-2].stmt), (yyvsp[0].stmt));   }
#line 1743 "parser.cpp"
    break;

  case 37: /* stmt: "if" cond "then" stmt  */
#line 223 "parser.y"
                                      { (yyval.stmt) = new If((yyvsp[-2].cond), (yyvsp[0].stmt));       }
#line 1749 "parser.cpp"
    break;

  case 38: /* stmt: "while" cond "do" stmt  */
#line 224 "parser.y"
                                      { (yyval.stmt) = new While((yyvsp[-2].cond), (yyvsp[0].stmt));    }
#line 1755 "parser.cpp"
    break;

  case 39: /* stmt: "return" ';'  */
#line 225 "parser.y"
                                      { (yyval.stmt) = new Return();         }
#line 1761 "parser.cpp"
    break;

  case 40: /* stmt: "return" expr ';'  */
#line 226 "parser.y"
                                      { (yyval.stmt) = new Return((yyvsp[-1].expr));       }
#line 1767 "parser.cpp"
    break;

  case 41: /* block: '{' stmt_list '}'  */
#line 229 "parser.y"
                                      { (yyval.block) = (yyvsp[-1].block);                   }
#line 1773 "parser.cpp"
    break;

  case 42: /* stmt_list: %empty  */
#line 233 "parser.y"
                                      { (yyval.block) = new Block();          }
#line 1779 "parser.cpp"
    break;

  case 43: /* stmt_list: stmt_list stmt  */
#line 234 "parser.y"
                                      { (yyvsp[-1].block)->append((yyvsp[0].stmt)); (yyval.block) = (yyvsp[-1].block);   }
#line 1785 "parser.cpp"
    break;

  case 44: /* func_call: T_id '(' expr_list ')'  */
#line 238 "parser.y"
                            { 
        Id *id; 
        id = new Id(*(yyvsp[-3].str_val));
        (yyval.funccall) = new FuncCall(id, (yyvsp[-1].vector_expr));
    }
#line 1795 "parser.cpp"
    break;

  case 45: /* expr_list: %empty  */
#line 247 "parser.y"
                            { (yyval.vector_expr) = new std::vector<Expr *>(); }
#line 1801 "parser.cpp"
    break;

  case 46: /* expr_list: expr_rest expr  */
#line 248 "parser.y"
                            { (yyvsp[-1].vector_expr)->push_back((yyvsp[0].expr)); (yyval.vector_expr) = (yyvsp[-1].vector_expr);     }
#line 1807 "parser.cpp"
    break;

  case 47: /* expr_rest: %empty  */
#line 252 "parser.y"
                            { (yyval.vector_expr) = new std::vector<Expr *>(); }
#line 1813 "parser.cpp"
    break;

  case 48: /* expr_rest: expr_rest expr ','  */
#line 253 "parser.y"
                            { (yyvsp[-2].vector_expr)->push_back((yyvsp[-1].expr)); (yyval.vector_expr) = (yyvsp[-2].vector_expr); }
#line 1819 "parser.cpp"
    break;

  case 49: /* l_value: T_id  */
#line 257 "parser.y"
                          { (yyval.abstractlvalue) = new Id(*(yyvsp[0].str_val));    }
#line 1825 "parser.cpp"
    break;

  case 50: /* l_value: T_string_lit  */
#line 258 "parser.y"
                          { (yyval.abstractlvalue) = new StrLit(yylval.str_val); }
#line 1831 "parser.cpp"
    break;

  case 51: /* l_value: l_value '[' expr ']'  */
#line 259 "parser.y"
                          { (yyval.abstractlvalue) = new LMatrix((yyvsp[-3].abstractlvalue), (yyvsp[-1].expr));        }
#line 1837 "parser.cpp"
    break;

  case 52: /* expr: T_int_lit  */
#line 263 "parser.y"
                          { (yyval.expr) = new IntConst((yyvsp[0].int_val));       }
#line 1843 "parser.cpp"
    break;

  case 53: /* expr: T_char_lit  */
#line 264 "parser.y"
                          { (yyval.expr) = new CharConst((yyvsp[0].char_val));      }
#line 1849 "parser.cpp"
    break;

  case 54: /* expr: l_value  */
#line 265 "parser.y"
                          { (yyval.expr) = (yyvsp[0].abstractlvalue);                     }
#line 1855 "parser.cpp"
    break;

  case 55: /* expr: '(' expr ')'  */
#line 266 "parser.y"
                          { (yyval.expr) = (yyvsp[-1].expr);                     }
#line 1861 "parser.cpp"
    break;

  case 56: /* expr: func_call  */
#line 267 "parser.y"
                          { (yyval.expr) = (yyvsp[0].funccall);                     }
#line 1867 "parser.cpp"
    break;

  case 57: /* expr: '+' expr  */
#line 268 "parser.y"
                          { (yyval.expr) = new UnaryOp((yyvsp[-1].char_val), (yyvsp[0].expr));    }
#line 1873 "parser.cpp"
    break;

  case 58: /* expr: '-' expr  */
#line 269 "parser.y"
                          { (yyval.expr) = new UnaryOp((yyvsp[-1].char_val), (yyvsp[0].expr));    }
#line 1879 "parser.cpp"
    break;

  case 59: /* expr: expr '+' expr  */
#line 270 "parser.y"
                          { (yyval.expr) = new BinOp((yyvsp[-2].expr), '+', (yyvsp[0].expr)); }
#line 1885 "parser.cpp"
    break;

  case 60: /* expr: expr '-' expr  */
#line 271 "parser.y"
                          { (yyval.expr) = new BinOp((yyvsp[-2].expr), '-', (yyvsp[0].expr)); }
#line 1891 "parser.cpp"
    break;

  case 61: /* expr: expr '*' expr  */
#line 272 "parser.y"
                          { (yyval.expr) = new BinOp((yyvsp[-2].expr), '*', (yyvsp[0].expr)); }
#line 1897 "parser.cpp"
    break;

  case 62: /* expr: expr "div" expr  */
#line 273 "parser.y"
                          { (yyval.expr) = new BinOp((yyvsp[-2].expr), '/', (yyvsp[0].expr)); }
#line 1903 "parser.cpp"
    break;

  case 63: /* expr: expr "mod" expr  */
#line 274 "parser.y"
                          { (yyval.expr) = new BinOp((yyvsp[-2].expr), '%', (yyvsp[0].expr)); }
#line 1909 "parser.cpp"
    break;

  case 64: /* cond: '(' cond ')'  */
#line 278 "parser.y"
                          { (yyval.cond) = (yyvsp[-1].cond);                           }
#line 1915 "parser.cpp"
    break;

  case 65: /* cond: "not" cond  */
#line 279 "parser.y"
                          { (yyval.cond) = new LogicalCond((yyvsp[0].cond), 'n');     }
#line 1921 "parser.cpp"
    break;

  case 66: /* cond: cond "and" cond  */
#line 280 "parser.y"
                          { (yyval.cond) = new LogicalCond((yyvsp[-2].cond), 'a', (yyvsp[0].cond)); }
#line 1927 "parser.cpp"
    break;

  case 67: /* cond: cond "or" cond  */
#line 281 "parser.y"
                          { (yyval.cond) = new LogicalCond((yyvsp[-2].cond), 'o', (yyvsp[0].cond)); }
#line 1933 "parser.cpp"
    break;

  case 68: /* cond: expr '=' expr  */
#line 282 "parser.y"
                          { (yyval.cond) = new NumericCond((yyvsp[-2].expr), (yyvsp[-1].char_val), (yyvsp[0].expr));  }
#line 1939 "parser.cpp"
    break;

  case 69: /* cond: expr '#' expr  */
#line 283 "parser.y"
                          { (yyval.cond) = new NumericCond((yyvsp[-2].expr), (yyvsp[-1].char_val), (yyvsp[0].expr));  }
#line 1945 "parser.cpp"
    break;

  case 70: /* cond: expr '<' expr  */
#line 284 "parser.y"
                          { (yyval.cond) = new NumericCond((yyvsp[-2].expr), (yyvsp[-1].char_val), (yyvsp[0].expr));  }
#line 1951 "parser.cpp"
    break;

  case 71: /* cond: expr '>' expr  */
#line 285 "parser.y"
                          { (yyval.cond) = new NumericCond((yyvsp[-2].expr), (yyvsp[-1].char_val), (yyvsp[0].expr));  }
#line 1957 "parser.cpp"
    break;

  case 72: /* cond: expr "leq" expr  */
#line 286 "parser.y"
                          { (yyval.cond) = new NumericCond((yyvsp[-2].expr), 'l', (yyvsp[0].expr)); }
#line 1963 "parser.cpp"
    break;

  case 73: /* cond: expr "geq" expr  */
#line 287 "parser.y"
                          { (yyval.cond) = new NumericCond((yyvsp[-2].expr), 'g', (yyvsp[0].expr)); }
#line 1969 "parser.cpp"
    break;


#line 1973 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 290 "parser.y"


void yyerror(const char *msg) {
  fprintf(stderr, "Error: %s at line %d\n", msg, yylineno);
  exit(1);
}

int main() {
  int result = yyparse();
  if (result == 0) printf("Success!\n");
  return result;
}
