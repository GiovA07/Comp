/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_TDS24_SINTAXIS_TAB_H_INCLUDED
# define YY_YY_TDS24_SINTAXIS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONSTANTE = 258,               /* CONSTANTE  */
    ID = 259,                      /* ID  */
    INT = 260,                     /* INT  */
    TTRUE = 261,                   /* TTRUE  */
    TFALSE = 262,                  /* TFALSE  */
    TYPE_INT = 263,                /* TYPE_INT  */
    TYPE_BOOL = 264,               /* TYPE_BOOL  */
    TYPE_VOID = 265,               /* TYPE_VOID  */
    TMAS = 266,                    /* TMAS  */
    TPOR = 267,                    /* TPOR  */
    TMENOS = 268,                  /* TMENOS  */
    TDIVISION = 269,               /* TDIVISION  */
    TRESTO = 270,                  /* TRESTO  */
    ASIGNACION = 271,              /* ASIGNACION  */
    TPAR_OP = 272,                 /* TPAR_OP  */
    TPAR_CL = 273,                 /* TPAR_CL  */
    TLLAVE_OP = 274,               /* TLLAVE_OP  */
    TLLAVE_CL = 275,               /* TLLAVE_CL  */
    OR = 276,                      /* OR  */
    AND = 277,                     /* AND  */
    NOT = 278,                     /* NOT  */
    MAYORQUE = 279,                /* MAYORQUE  */
    MENORQUE = 280,                /* MENORQUE  */
    EQ = 281,                      /* EQ  */
    PROGRAM = 282,                 /* PROGRAM  */
    EXTERN = 283,                  /* EXTERN  */
    THEN = 284,                    /* THEN  */
    IF = 285,                      /* IF  */
    ELSE = 286,                    /* ELSE  */
    WHILE = 287,                   /* WHILE  */
    RETURN = 288,                  /* RETURN  */
    MAIN = 289                     /* MAIN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "TDS24_sintaxis.y"

    struct Tsymbol* symbol;
    struct AST *arbol;

#line 103 "TDS24_sintaxis.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TDS24_SINTAXIS_TAB_H_INCLUDED  */
