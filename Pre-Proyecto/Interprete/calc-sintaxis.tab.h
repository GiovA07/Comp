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

#ifndef YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED
# define YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED
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
    ASIGNACION = 269,              /* ASIGNACION  */
    TPAR_OP = 270,                 /* TPAR_OP  */
    TPAR_CL = 271,                 /* TPAR_CL  */
    TLLAVE_OP = 272,               /* TLLAVE_OP  */
    TLLAVE_CL = 273,               /* TLLAVE_CL  */
    OR = 274,                      /* OR  */
    AND = 275,                     /* AND  */
    NOT = 276,                     /* NOT  */
    IF = 277,                      /* IF  */
    ELSE = 278,                    /* ELSE  */
    WHILE = 279,                   /* WHILE  */
    RETURN = 280,                  /* RETURN  */
    MAIN = 281                     /* MAIN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "calc-sintaxis.y"

    struct Tsymbol* symbol;
    struct AST *arbol;

#line 95 "calc-sintaxis.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED  */
