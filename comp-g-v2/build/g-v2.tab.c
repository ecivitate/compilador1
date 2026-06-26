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
#line 1 "src/g-v2.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"
#include "codegen.h"

extern int   yylineno;
extern char *yytext;
extern int   yylex();
extern FILE *yyin;

void yyerror(const char *s);

ASTNode *ast_root = NULL;

#line 89 "build/g-v2.tab.c"

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

#include "g-v2.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_GLOBAL = 3,                     /* GLOBAL  */
  YYSYMBOL_FUNCAO = 4,                     /* FUNCAO  */
  YYSYMBOL_RETORNE = 5,                    /* RETORNE  */
  YYSYMBOL_PRINCIPAL = 6,                  /* PRINCIPAL  */
  YYSYMBOL_LEIA = 7,                       /* LEIA  */
  YYSYMBOL_ESCREVA = 8,                    /* ESCREVA  */
  YYSYMBOL_NOVALINHA = 9,                  /* NOVALINHA  */
  YYSYMBOL_SE = 10,                        /* SE  */
  YYSYMBOL_ENTAO = 11,                     /* ENTAO  */
  YYSYMBOL_SENAO = 12,                     /* SENAO  */
  YYSYMBOL_FIMSE = 13,                     /* FIMSE  */
  YYSYMBOL_ENQUANTO = 14,                  /* ENQUANTO  */
  YYSYMBOL_INT = 15,                       /* INT  */
  YYSYMBOL_CAR = 16,                       /* CAR  */
  YYSYMBOL_OU = 17,                        /* OU  */
  YYSYMBOL_E = 18,                         /* E  */
  YYSYMBOL_IGUAL = 19,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 20,                 /* DIFERENTE  */
  YYSYMBOL_MAIORIGUAL = 21,                /* MAIORIGUAL  */
  YYSYMBOL_MENORIGUAL = 22,                /* MENORIGUAL  */
  YYSYMBOL_IDENTIFICADOR = 23,             /* IDENTIFICADOR  */
  YYSYMBOL_INTCONST = 24,                  /* INTCONST  */
  YYSYMBOL_CARCONST = 25,                  /* CARCONST  */
  YYSYMBOL_CADEIACARACTERES = 26,          /* CADEIACARACTERES  */
  YYSYMBOL_27_ = 27,                       /* '['  */
  YYSYMBOL_28_ = 28,                       /* '('  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_30_ = 30,                       /* ':'  */
  YYSYMBOL_31_ = 31,                       /* ']'  */
  YYSYMBOL_32_ = 32,                       /* ','  */
  YYSYMBOL_33_ = 33,                       /* '{'  */
  YYSYMBOL_34_ = 34,                       /* '}'  */
  YYSYMBOL_35_ = 35,                       /* ';'  */
  YYSYMBOL_36_ = 36,                       /* '='  */
  YYSYMBOL_37_ = 37,                       /* '<'  */
  YYSYMBOL_38_ = 38,                       /* '>'  */
  YYSYMBOL_39_ = 39,                       /* '+'  */
  YYSYMBOL_40_ = 40,                       /* '-'  */
  YYSYMBOL_41_ = 41,                       /* '*'  */
  YYSYMBOL_42_ = 42,                       /* '/'  */
  YYSYMBOL_43_ = 43,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_programa = 45,                  /* programa  */
  YYSYMBOL_declvarglobais = 46,            /* declvarglobais  */
  YYSYMBOL_declfunc = 47,                  /* declfunc  */
  YYSYMBOL_listafuncoes = 48,              /* listafuncoes  */
  YYSYMBOL_listaparametros = 49,           /* listaparametros  */
  YYSYMBOL_listaparametrostail = 50,       /* listaparametrostail  */
  YYSYMBOL_declprograma = 51,              /* declprograma  */
  YYSYMBOL_bloco = 52,                     /* bloco  */
  YYSYMBOL_varsection = 53,                /* varsection  */
  YYSYMBOL_listadeclvar = 54,              /* listadeclvar  */
  YYSYMBOL_listvar = 55,                   /* listvar  */
  YYSYMBOL_tipo = 56,                      /* tipo  */
  YYSYMBOL_listacomando = 57,              /* listacomando  */
  YYSYMBOL_comando = 58,                   /* comando  */
  YYSYMBOL_expr = 59,                      /* expr  */
  YYSYMBOL_lvalueexpr = 60,                /* lvalueexpr  */
  YYSYMBOL_orexpr = 61,                    /* orexpr  */
  YYSYMBOL_andexpr = 62,                   /* andexpr  */
  YYSYMBOL_eqexpr = 63,                    /* eqexpr  */
  YYSYMBOL_desigexpr = 64,                 /* desigexpr  */
  YYSYMBOL_addexpr = 65,                   /* addexpr  */
  YYSYMBOL_mulexpr = 66,                   /* mulexpr  */
  YYSYMBOL_unexpr = 67,                    /* unexpr  */
  YYSYMBOL_primexpr = 68,                  /* primexpr  */
  YYSYMBOL_listexpr = 69                   /* listexpr  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


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
       2,     2,     2,    43,     2,     2,     2,     2,     2,     2,
      28,    29,    41,    39,    32,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,    35,
      37,    36,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    27,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    45,    45,    56,    59,    63,    74,    78,    89,    93,
      96,   100,   106,   113,   120,   131,   136,   141,   150,   155,
     169,   182,   189,   199,   205,   217,   218,   222,   224,   238,
     240,   242,   247,   252,   259,   261,   267,   274,   280,   282,
     290,   296,   301,   306,   315,   322,   327,   334,   339,   346,
     353,   358,   365,   372,   379,   386,   391,   398,   405,   410,
     417,   424,   429,   435,   441,   446,   452,   457,   463,   468,
     473,   478,   483,   485
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "GLOBAL", "FUNCAO",
  "RETORNE", "PRINCIPAL", "LEIA", "ESCREVA", "NOVALINHA", "SE", "ENTAO",
  "SENAO", "FIMSE", "ENQUANTO", "INT", "CAR", "OU", "E", "IGUAL",
  "DIFERENTE", "MAIORIGUAL", "MENORIGUAL", "IDENTIFICADOR", "INTCONST",
  "CARCONST", "CADEIACARACTERES", "'['", "'('", "')'", "':'", "']'", "','",
  "'{'", "'}'", "';'", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'!'", "$accept", "programa", "declvarglobais", "declfunc",
  "listafuncoes", "listaparametros", "listaparametrostail", "declprograma",
  "bloco", "varsection", "listadeclvar", "listvar", "tipo", "listacomando",
  "comando", "expr", "lvalueexpr", "orexpr", "andexpr", "eqexpr",
  "desigexpr", "addexpr", "mulexpr", "unexpr", "primexpr", "listexpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-126)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   -11,    20,    18,    14,  -126,  -126,    36,    39,     3,
      25,    49,    46,   -12,  -126,    61,    14,  -126,    85,    62,
      24,  -126,    89,    67,  -126,  -126,  -126,    88,   102,    48,
     103,   -17,    92,   101,   104,    -9,  -126,  -126,    48,  -126,
      30,    30,  -126,    94,    24,    95,    97,   114,   116,    55,
      71,    64,    65,  -126,  -126,    24,   105,    14,    16,   106,
    -126,   107,   109,   108,   110,   111,  -126,    48,    48,    48,
      37,   112,    83,  -126,  -126,  -126,  -126,  -126,    48,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,   115,    14,  -126,   113,    85,   118,  -126,    48,  -126,
    -126,  -126,   121,   122,   123,  -126,  -126,    57,  -126,    48,
    -126,   116,    55,    71,    71,    64,    64,    64,    64,    65,
      65,  -126,  -126,  -126,  -126,   125,   120,    85,   126,   127,
      24,   117,  -126,    48,   128,    85,   102,   -12,  -126,    24,
    -126,  -126,  -126,   124,  -126,   135,   100,   102,   132,   130,
      24,  -126,  -126,   102,  -126,   149,   134,  -126,   136,    85,
     -12,   135,  -126
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     6,     0,     3,     1,     0,     0,    23,
       0,     0,     0,     0,     2,     0,     0,    18,     0,     0,
       0,    15,     0,     0,    21,    25,    26,     0,    10,     0,
       0,     0,     0,     0,     0,    68,    69,    70,     0,    29,
       0,     0,    38,     0,    27,     0,     0,    41,    45,    47,
      50,    55,    58,    61,    64,     0,    24,    20,     0,     0,
       9,     0,    42,     0,     0,     0,    34,     0,     0,     0,
       0,     0,    68,    62,    63,    16,    28,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,    39,     0,    31,
      33,    32,     0,     0,     0,    66,    72,     0,    71,     0,
      40,    44,    46,    48,    49,    53,    54,    51,    52,    56,
      57,    59,    60,    17,    22,     0,    11,     0,     0,     0,
       0,    67,    65,     0,     0,     0,     0,     0,    43,     0,
      37,    73,    67,    12,    13,     8,     0,     0,     0,     0,
       0,    35,    14,    10,     5,     0,     0,    36,     0,     0,
       0,     8,     7
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,  -126,   -22,    12,  -123,  -126,   -13,   139,
     119,   -14,   -91,   -27,  -125,   -28,   137,  -126,    90,    84,
      33,    11,    29,    31,    78,  -126
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     8,   149,    59,    60,    14,    42,    22,
      10,    11,    27,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   107
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      21,    61,    24,    65,   126,   140,    35,    36,    37,    64,
      71,    38,     1,   144,   146,     4,     4,    76,    69,    70,
       6,    20,     7,    40,   152,   155,    41,   -42,    91,    29,
      15,    30,    31,    32,    33,    16,   137,     9,    34,   102,
     103,   104,   106,    94,   143,    13,    95,    35,    36,    37,
     110,     4,    38,    72,    36,    37,    17,    20,    38,    39,
      35,    36,    37,    12,    40,    38,   105,    41,   160,    19,
     128,    35,    36,    37,    81,    82,    38,    40,   124,    18,
      41,   134,    72,    36,    37,    23,   132,    38,    40,   133,
      28,    41,    83,    84,   115,   116,   117,   118,    56,    40,
      25,    26,    41,    87,    88,   141,    89,    90,    85,    86,
     109,    70,   150,   151,   113,   114,   119,   120,    73,    74,
     121,   122,    55,    57,   145,    58,    62,    66,    75,    67,
      77,    79,    68,    78,    80,    96,    98,    92,   139,   162,
       5,   108,    97,    99,   125,   100,   101,   161,   127,   123,
     129,   130,   136,   -43,   131,   135,   147,   138,   148,   142,
     153,   154,   157,   158,   112,   156,   159,    63,     0,   111,
       0,     0,     0,     0,     0,     0,    93
};

static const yytype_int16 yycheck[] =
{
      13,    29,    16,    31,    95,   130,    23,    24,    25,    26,
      38,    28,     3,   136,   139,    27,    27,    44,    27,    28,
       0,    33,     4,    40,   147,   150,    43,    36,    55,     5,
      27,     7,     8,     9,    10,    32,   127,    23,    14,    67,
      68,    69,    70,    27,   135,     6,    30,    23,    24,    25,
      78,    27,    28,    23,    24,    25,    31,    33,    28,    35,
      23,    24,    25,    27,    40,    28,    29,    43,   159,    23,
      98,    23,    24,    25,    19,    20,    28,    40,    92,    30,
      43,   109,    23,    24,    25,    24,    29,    28,    40,    32,
      28,    43,    21,    22,    83,    84,    85,    86,    31,    40,
      15,    16,    43,    39,    40,   133,    41,    42,    37,    38,
      27,    28,    12,    13,    81,    82,    87,    88,    40,    41,
      89,    90,    33,    35,   137,    23,    23,    35,    34,    28,
      35,    17,    28,    36,    18,    29,    27,    32,    11,   161,
       1,    29,    35,    35,    31,    35,    35,   160,    30,    34,
      29,    29,    32,    36,    31,    30,    32,    31,    23,    31,
      28,    31,    13,    29,    80,   153,    30,    30,    -1,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    57
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    45,    46,    27,    53,     0,     4,    47,    23,
      54,    55,    27,     6,    51,    27,    32,    31,    30,    23,
      33,    52,    53,    24,    55,    15,    16,    56,    28,     5,
       7,     8,     9,    10,    14,    23,    24,    25,    28,    35,
      40,    43,    52,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    33,    31,    35,    23,    49,
      50,    59,    23,    60,    26,    59,    35,    28,    28,    27,
      28,    59,    23,    68,    68,    34,    57,    35,    36,    17,
      18,    19,    20,    21,    22,    37,    38,    39,    40,    41,
      42,    57,    32,    54,    27,    30,    29,    35,    27,    35,
      35,    35,    59,    59,    59,    29,    59,    69,    29,    27,
      59,    62,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    34,    55,    31,    56,    30,    59,    29,
      29,    31,    29,    32,    59,    30,    32,    56,    31,    11,
      58,    59,    31,    56,    50,    52,    58,    32,    23,    48,
      12,    13,    50,    28,    31,    58,    49,    13,    29,    30,
      56,    52,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    49,
      49,    50,    50,    50,    50,    51,    52,    52,    53,    54,
      54,    55,    55,    55,    55,    56,    56,    57,    57,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      63,    64,    64,    64,    64,    64,    65,    65,    65,    66,
      66,    66,    67,    67,    67,    68,    68,    68,    68,    68,
      68,    68,    69,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,    11,     0,     8,     0,     1,
       0,     3,     5,     5,     7,     2,     3,     4,     3,     5,
       4,     3,     6,     1,     4,     1,     1,     1,     2,     1,
       2,     3,     3,     3,     2,     7,     9,     5,     1,     3,
       3,     1,     1,     4,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     4,     3,     4,     1,     1,
       1,     3,     1,     3
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: declvarglobais declfunc declprograma  */
#line 46 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_PROGRAM, (yylsp[0]).first_line);
            (yyval.node)->child[0] = (yyvsp[-2].node);  /* variaveis globais */
            (yyval.node)->child[1] = (yyvsp[-1].node);  /* funcoes */
            (yyval.node)->child[2] = (yyvsp[0].node);  /* principal */
            ast_root = (yyval.node);
        }
#line 1372 "build/g-v2.tab.c"
    break;

  case 3: /* declvarglobais: GLOBAL varsection  */
#line 57 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1378 "build/g-v2.tab.c"
    break;

  case 4: /* declvarglobais: %empty  */
#line 59 "src/g-v2.y"
        { (yyval.node) = NULL; }
#line 1384 "build/g-v2.tab.c"
    break;

  case 5: /* declfunc: FUNCAO '[' IDENTIFICADOR '(' listaparametros ')' ':' tipo bloco listafuncoes ']'  */
#line 64 "src/g-v2.y"
        {
            ASTNode *f = newNode(NODE_FUNC, (yylsp[-8]).first_line);
            f->lexeme = (yyvsp[-8].lexeme);
            f->tipo = (yyvsp[-3].tipo);
            f->child[0] = (yyvsp[-6].node);   /* parametros */
            f->child[1] = (yyvsp[-2].node);   /* bloco */
            f->next = (yyvsp[-1].node);      /* proximas funcoes */
            (yyval.node) = f;
        }
#line 1398 "build/g-v2.tab.c"
    break;

  case 6: /* declfunc: %empty  */
#line 74 "src/g-v2.y"
        { (yyval.node) = NULL; }
#line 1404 "build/g-v2.tab.c"
    break;

  case 7: /* listafuncoes: IDENTIFICADOR '(' listaparametros ')' ':' tipo bloco listafuncoes  */
#line 79 "src/g-v2.y"
        {
            ASTNode *f = newNode(NODE_FUNC, (yylsp[-7]).first_line);
            f->lexeme = (yyvsp[-7].lexeme);
            f->tipo = (yyvsp[-2].tipo);
            f->child[0] = (yyvsp[-5].node);
            f->child[1] = (yyvsp[-1].node);
            f->next = (yyvsp[0].node);
            (yyval.node) = f;
        }
#line 1418 "build/g-v2.tab.c"
    break;

  case 8: /* listafuncoes: %empty  */
#line 89 "src/g-v2.y"
        { (yyval.node) = NULL; }
#line 1424 "build/g-v2.tab.c"
    break;

  case 9: /* listaparametros: listaparametrostail  */
#line 94 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1430 "build/g-v2.tab.c"
    break;

  case 10: /* listaparametros: %empty  */
#line 96 "src/g-v2.y"
        { (yyval.node) = NULL; }
#line 1436 "build/g-v2.tab.c"
    break;

  case 11: /* listaparametrostail: IDENTIFICADOR ':' tipo  */
#line 101 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_PARAM, (yylsp[-2]).first_line);
            (yyval.node)->lexeme = (yyvsp[-2].lexeme);
            (yyval.node)->tipo = (yyvsp[0].tipo);
        }
#line 1446 "build/g-v2.tab.c"
    break;

  case 12: /* listaparametrostail: IDENTIFICADOR '[' ']' ':' tipo  */
#line 107 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_PARAM, (yylsp[-4]).first_line);
            (yyval.node)->lexeme = (yyvsp[-4].lexeme);
            (yyval.node)->tipo = (yyvsp[0].tipo);
            (yyval.node)->isArray = 1;
        }
#line 1457 "build/g-v2.tab.c"
    break;

  case 13: /* listaparametrostail: IDENTIFICADOR ':' tipo ',' listaparametrostail  */
#line 114 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_PARAM, (yylsp[-4]).first_line);
            (yyval.node)->lexeme = (yyvsp[-4].lexeme);
            (yyval.node)->tipo = (yyvsp[-2].tipo);
            (yyval.node)->next = (yyvsp[0].node);
        }
#line 1468 "build/g-v2.tab.c"
    break;

  case 14: /* listaparametrostail: IDENTIFICADOR '[' ']' ':' tipo ',' listaparametrostail  */
#line 121 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_PARAM, (yylsp[-6]).first_line);
            (yyval.node)->lexeme = (yyvsp[-6].lexeme);
            (yyval.node)->tipo = (yyvsp[-2].tipo);
            (yyval.node)->isArray = 1;
            (yyval.node)->next = (yyvsp[0].node);
        }
#line 1480 "build/g-v2.tab.c"
    break;

  case 15: /* declprograma: PRINCIPAL bloco  */
#line 132 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1486 "build/g-v2.tab.c"
    break;

  case 16: /* bloco: '{' listacomando '}'  */
#line 137 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BLOCK, (yylsp[-2]).first_line);
            (yyval.node)->child[1] = (yyvsp[-1].node);
        }
#line 1495 "build/g-v2.tab.c"
    break;

  case 17: /* bloco: varsection '{' listacomando '}'  */
#line 142 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BLOCK, (yylsp[-2]).first_line);
            (yyval.node)->child[0] = (yyvsp[-3].node);
            (yyval.node)->child[1] = (yyvsp[-1].node);
        }
#line 1505 "build/g-v2.tab.c"
    break;

  case 18: /* varsection: '[' listadeclvar ']'  */
#line 151 "src/g-v2.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1511 "build/g-v2.tab.c"
    break;

  case 19: /* listadeclvar: listvar ':' tipo ';' listadeclvar  */
#line 156 "src/g-v2.y"
        {
            ASTNode *cur = (yyvsp[-4].node);
            while (cur) {
                cur->tipo = (yyvsp[-2].tipo);
                cur = cur->next;
            }

            ASTNode *tail = (yyvsp[-4].node);
            while (tail && tail->next) tail = tail->next;
            if (tail) tail->next = (yyvsp[0].node);

            (yyval.node) = (yyvsp[-4].node);
        }
#line 1529 "build/g-v2.tab.c"
    break;

  case 20: /* listadeclvar: listvar ':' tipo ';'  */
#line 170 "src/g-v2.y"
        {
            ASTNode *cur = (yyvsp[-3].node);
            while (cur) {
                cur->tipo = (yyvsp[-1].tipo);
                cur = cur->next;
            }

            (yyval.node) = (yyvsp[-3].node);
        }
#line 1543 "build/g-v2.tab.c"
    break;

  case 21: /* listvar: IDENTIFICADOR ',' listvar  */
#line 183 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_DECL, (yylsp[-2]).first_line);
            (yyval.node)->lexeme = (yyvsp[-2].lexeme);
            (yyval.node)->tipo = TIPO_NENHUM;
            (yyval.node)->next = (yyvsp[0].node);
        }
#line 1554 "build/g-v2.tab.c"
    break;

  case 22: /* listvar: IDENTIFICADOR '[' INTCONST ']' ',' listvar  */
#line 190 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_DECL, (yylsp[-5]).first_line);
            (yyval.node)->lexeme = (yyvsp[-5].lexeme);
            (yyval.node)->tipo = TIPO_NENHUM;
            (yyval.node)->isArray = 1;
            (yyval.node)->arraySize = atoi((yyvsp[-3].lexeme));
            free((yyvsp[-3].lexeme));
            (yyval.node)->next = (yyvsp[0].node);
        }
#line 1568 "build/g-v2.tab.c"
    break;

  case 23: /* listvar: IDENTIFICADOR  */
#line 200 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_DECL, (yylsp[0]).first_line);
            (yyval.node)->lexeme = (yyvsp[0].lexeme);
            (yyval.node)->tipo = TIPO_NENHUM;
        }
#line 1578 "build/g-v2.tab.c"
    break;

  case 24: /* listvar: IDENTIFICADOR '[' INTCONST ']'  */
#line 206 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_DECL, (yylsp[-3]).first_line);
            (yyval.node)->lexeme = (yyvsp[-3].lexeme);
            (yyval.node)->tipo = TIPO_NENHUM;
            (yyval.node)->isArray = 1;
            (yyval.node)->arraySize = atoi((yyvsp[-1].lexeme));
            free((yyvsp[-1].lexeme));
        }
#line 1591 "build/g-v2.tab.c"
    break;

  case 25: /* tipo: INT  */
#line 217 "src/g-v2.y"
          { (yyval.tipo) = TIPO_INT; }
#line 1597 "build/g-v2.tab.c"
    break;

  case 26: /* tipo: CAR  */
#line 218 "src/g-v2.y"
          { (yyval.tipo) = TIPO_CAR; }
#line 1603 "build/g-v2.tab.c"
    break;

  case 27: /* listacomando: comando  */
#line 223 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1609 "build/g-v2.tab.c"
    break;

  case 28: /* listacomando: comando listacomando  */
#line 225 "src/g-v2.y"
        {
            if ((yyvsp[-1].node)) {
                ASTNode *tail = (yyvsp[-1].node);
                while (tail->next) tail = tail->next;
                tail->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            } else {
                (yyval.node) = (yyvsp[0].node);
            }
        }
#line 1624 "build/g-v2.tab.c"
    break;

  case 29: /* comando: ';'  */
#line 239 "src/g-v2.y"
        { (yyval.node) = NULL; }
#line 1630 "build/g-v2.tab.c"
    break;

  case 30: /* comando: expr ';'  */
#line 241 "src/g-v2.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1636 "build/g-v2.tab.c"
    break;

  case 31: /* comando: LEIA lvalueexpr ';'  */
#line 243 "src/g-v2.y"
    {
        (yyval.node) = newNode(NODE_LEIA, (yylsp[-2]).first_line);
        (yyval.node)->child[0] = (yyvsp[-1].node);
    }
#line 1645 "build/g-v2.tab.c"
    break;

  case 32: /* comando: ESCREVA expr ';'  */
#line 248 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_ESCREVA, (yylsp[-2]).first_line);
            (yyval.node)->child[0] = (yyvsp[-1].node);
        }
#line 1654 "build/g-v2.tab.c"
    break;

  case 33: /* comando: ESCREVA CADEIACARACTERES ';'  */
#line 253 "src/g-v2.y"
        {
            ASTNode *cad = newNode(NODE_CADEIA, (yylsp[-1]).first_line);
            cad->lexeme  = (yyvsp[-1].lexeme);
            (yyval.node) = newNode(NODE_ESCREVA, (yylsp[-2]).first_line);
            (yyval.node)->child[0] = cad;
        }
#line 1665 "build/g-v2.tab.c"
    break;

  case 34: /* comando: NOVALINHA ';'  */
#line 260 "src/g-v2.y"
        { (yyval.node) = newNode(NODE_NOVALINHA, (yylsp[-1]).first_line); }
#line 1671 "build/g-v2.tab.c"
    break;

  case 35: /* comando: SE '(' expr ')' ENTAO comando FIMSE  */
#line 262 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_SE, (yylsp[-6]).first_line);
            (yyval.node)->child[0] = (yyvsp[-4].node);
            (yyval.node)->child[1] = (yyvsp[-1].node);
        }
#line 1681 "build/g-v2.tab.c"
    break;

  case 36: /* comando: SE '(' expr ')' ENTAO comando SENAO comando FIMSE  */
#line 268 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_SE, (yylsp[-8]).first_line);
            (yyval.node)->child[0] = (yyvsp[-6].node);
            (yyval.node)->child[1] = (yyvsp[-3].node);
            (yyval.node)->child[2] = (yyvsp[-1].node);
        }
#line 1692 "build/g-v2.tab.c"
    break;

  case 37: /* comando: ENQUANTO '(' expr ')' comando  */
#line 275 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_ENQUANTO, (yylsp[-4]).first_line);
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1702 "build/g-v2.tab.c"
    break;

  case 38: /* comando: bloco  */
#line 281 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1708 "build/g-v2.tab.c"
    break;

  case 39: /* comando: RETORNE expr ';'  */
#line 283 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_RETORNE, (yylsp[-2]).first_line);
            (yyval.node)->child[0] = (yyvsp[-1].node);
        }
#line 1717 "build/g-v2.tab.c"
    break;

  case 40: /* expr: lvalueexpr '=' expr  */
#line 291 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_ATRIB, (yylsp[-1]).first_line);
            (yyval.node)->child[0] = (yyvsp[-2].node);  /* destino */
            (yyval.node)->child[1] = (yyvsp[0].node);  /* valor */
        }
#line 1727 "build/g-v2.tab.c"
    break;

  case 41: /* expr: orexpr  */
#line 297 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1733 "build/g-v2.tab.c"
    break;

  case 42: /* lvalueexpr: IDENTIFICADOR  */
#line 302 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_IDENT, (yylsp[0]).first_line);
            (yyval.node)->lexeme = (yyvsp[0].lexeme);
        }
#line 1742 "build/g-v2.tab.c"
    break;

  case 43: /* lvalueexpr: IDENTIFICADOR '[' expr ']'  */
#line 307 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_ARRAY_ACCESS, (yylsp[-3]).first_line);
            (yyval.node)->lexeme = (yyvsp[-3].lexeme);
            (yyval.node)->child[0] = (yyvsp[-1].node);  /* indice */
        }
#line 1752 "build/g-v2.tab.c"
    break;

  case 44: /* orexpr: orexpr OU andexpr  */
#line 316 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("||");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1763 "build/g-v2.tab.c"
    break;

  case 45: /* orexpr: andexpr  */
#line 323 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1769 "build/g-v2.tab.c"
    break;

  case 46: /* andexpr: andexpr E eqexpr  */
#line 328 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("&");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1780 "build/g-v2.tab.c"
    break;

  case 47: /* andexpr: eqexpr  */
#line 335 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1786 "build/g-v2.tab.c"
    break;

  case 48: /* eqexpr: eqexpr IGUAL desigexpr  */
#line 340 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("==");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1797 "build/g-v2.tab.c"
    break;

  case 49: /* eqexpr: eqexpr DIFERENTE desigexpr  */
#line 347 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("!=");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1808 "build/g-v2.tab.c"
    break;

  case 50: /* eqexpr: desigexpr  */
#line 354 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1814 "build/g-v2.tab.c"
    break;

  case 51: /* desigexpr: desigexpr '<' addexpr  */
#line 359 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("<");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1825 "build/g-v2.tab.c"
    break;

  case 52: /* desigexpr: desigexpr '>' addexpr  */
#line 366 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup(">");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1836 "build/g-v2.tab.c"
    break;

  case 53: /* desigexpr: desigexpr MAIORIGUAL addexpr  */
#line 373 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup(">=");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1847 "build/g-v2.tab.c"
    break;

  case 54: /* desigexpr: desigexpr MENORIGUAL addexpr  */
#line 380 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("<=");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1858 "build/g-v2.tab.c"
    break;

  case 55: /* desigexpr: addexpr  */
#line 387 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1864 "build/g-v2.tab.c"
    break;

  case 56: /* addexpr: addexpr '+' mulexpr  */
#line 392 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("+");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1875 "build/g-v2.tab.c"
    break;

  case 57: /* addexpr: addexpr '-' mulexpr  */
#line 399 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("-");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1886 "build/g-v2.tab.c"
    break;

  case 58: /* addexpr: mulexpr  */
#line 406 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1892 "build/g-v2.tab.c"
    break;

  case 59: /* mulexpr: mulexpr '*' unexpr  */
#line 411 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("*");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1903 "build/g-v2.tab.c"
    break;

  case 60: /* mulexpr: mulexpr '/' unexpr  */
#line 418 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_BINOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("/");
            (yyval.node)->child[0] = (yyvsp[-2].node);
            (yyval.node)->child[1] = (yyvsp[0].node);
        }
#line 1914 "build/g-v2.tab.c"
    break;

  case 61: /* mulexpr: unexpr  */
#line 425 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1920 "build/g-v2.tab.c"
    break;

  case 62: /* unexpr: '-' primexpr  */
#line 430 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_UNOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("-");
            (yyval.node)->child[0] = (yyvsp[0].node);
        }
#line 1930 "build/g-v2.tab.c"
    break;

  case 63: /* unexpr: '!' primexpr  */
#line 436 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_UNOP, (yylsp[-1]).first_line);
            (yyval.node)->lexeme   = strdup("!");
            (yyval.node)->child[0] = (yyvsp[0].node);
        }
#line 1940 "build/g-v2.tab.c"
    break;

  case 64: /* unexpr: primexpr  */
#line 442 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1946 "build/g-v2.tab.c"
    break;

  case 65: /* primexpr: IDENTIFICADOR '(' listexpr ')'  */
#line 447 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_CALL, (yylsp[-3]).first_line);
            (yyval.node)->lexeme = (yyvsp[-3].lexeme);
            (yyval.node)->child[0] = (yyvsp[-1].node);
        }
#line 1956 "build/g-v2.tab.c"
    break;

  case 66: /* primexpr: IDENTIFICADOR '(' ')'  */
#line 453 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_CALL, (yylsp[-2]).first_line);
            (yyval.node)->lexeme = (yyvsp[-2].lexeme);
        }
#line 1965 "build/g-v2.tab.c"
    break;

  case 67: /* primexpr: IDENTIFICADOR '[' expr ']'  */
#line 458 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_ARRAY_ACCESS, (yylsp[-3]).first_line);
            (yyval.node)->lexeme = (yyvsp[-3].lexeme);
            (yyval.node)->child[0] = (yyvsp[-1].node);
        }
#line 1975 "build/g-v2.tab.c"
    break;

  case 68: /* primexpr: IDENTIFICADOR  */
#line 464 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_IDENT, (yylsp[0]).first_line);
            (yyval.node)->lexeme = (yyvsp[0].lexeme);
        }
#line 1984 "build/g-v2.tab.c"
    break;

  case 69: /* primexpr: INTCONST  */
#line 469 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_INTCONST, (yylsp[0]).first_line);
            (yyval.node)->lexeme = (yyvsp[0].lexeme);
        }
#line 1993 "build/g-v2.tab.c"
    break;

  case 70: /* primexpr: CARCONST  */
#line 474 "src/g-v2.y"
        {
            (yyval.node) = newNode(NODE_CARCONST, (yylsp[0]).first_line);
            (yyval.node)->lexeme = (yyvsp[0].lexeme);
        }
#line 2002 "build/g-v2.tab.c"
    break;

  case 71: /* primexpr: '(' expr ')'  */
#line 479 "src/g-v2.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 2008 "build/g-v2.tab.c"
    break;

  case 72: /* listexpr: expr  */
#line 484 "src/g-v2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2014 "build/g-v2.tab.c"
    break;

  case 73: /* listexpr: listexpr ',' expr  */
#line 486 "src/g-v2.y"
        {
            ASTNode *tail = (yyvsp[-2].node);
            while (tail->next) tail = tail->next;
            tail->next = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-2].node);
        }
#line 2025 "build/g-v2.tab.c"
    break;


#line 2029 "build/g-v2.tab.c"

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
  *++yylsp = yyloc;

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
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 494 "src/g-v2.y"


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso correto: ./g-v2 nome_arquivo\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "arquivo nao pode ser aberto\n");
        return 1;
    }

    int parseResult = yyparse();
    fclose(yyin);

    if (parseResult != 0) {
        freeAST(ast_root);
        return 1;
    }

    if (ast_root) {
        semanticAnalyze(ast_root);

        char outname[512];
        strncpy(outname, argv[1], sizeof(outname) - 5);
        outname[sizeof(outname) - 5] = '\0';
        char *dot = strrchr(outname, '.');
        if (dot) strcpy(dot, ".asm");
        else strcat(outname, ".asm");

        FILE *out = fopen(outname, "w");
        if (!out) { fprintf(stderr, "erro: nao foi possivel criar %s\n", outname); return 1; }
        codegenProgram(ast_root, out);
        fclose(out);

        freeAST(ast_root);
    }

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
}
