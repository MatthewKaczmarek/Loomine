%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evalexpr.h"
#include "prog.h"
#include "compilecpp.h"
#define YYDEBUG 1

int yylex (void);
int yyerror(char* s);
%}

%union semrec { /*SEMANTIC RECORD */
	char *val;
    char* id;
}
/* ADDITION: SUBOP, LPAREN, RPAREN, to grammar rules */
%start program
%token READ WRITE END ASSIGNOP COMMA MAP PLAYER GAME DOOR ENEMY ADDM ADDP ADDD ADDE RUN 
%token <id> ID
%token <val> DIGIT
%token <val> CHARACTER
%token <val> LPAREN
%token <val> RPAREN

%%

program : stmt_list END 
;

stmt_list : stmt | stmt_list stmt;

stmt : ID ASSIGNOP mapstmt     { assignMapSymbol($1); }
    | ID ASSIGNOP plrstmt      { assignPlrSymbol($1); }
    | ID ASSIGNOP gmstmt       { assignGameSymbol($1); }
    | ID ASSIGNOP dstmt        { assignDoorSymbol($1); }
    | ID ASSIGNOP estmt        { assignEnemySymbol($1); }
    | RUN gmstmt               { runGame(); }
;

mapstmt : MAP LPAREN DIGIT COMMA DIGIT COMMA CHARACTER COMMA CHARACTER RPAREN { genMap($3, $5, $7, $9); }
    | ID                    { genIdentifierMap($1); }
    | mapstmt ADDD dstmt    { addDoor(); }
    | mapstmt ADDE estmt    { addEnemy(); }
;

plrstmt : PLAYER LPAREN DIGIT COMMA DIGIT COMMA CHARACTER COMMA CHARACTER COMMA CHARACTER COMMA CHARACTER COMMA CHARACTER RPAREN { genPlr($3, $5, $7, $9, $11, $13, $15); }
    | ID                    { genIdentifierPlr($1); }
;

estmt : ENEMY LPAREN DIGIT COMMA DIGIT COMMA CHARACTER COMMA DIGIT RPAREN {genEnemy($3, $5, $7, $9); }
    | ID                    { genIdentifierEnemy($1); }
;

dstmt : DOOR LPAREN DIGIT COMMA DIGIT COMMA CHARACTER RPAREN {genDoor($3, $5, $7); }
    | ID                    { genIdentifierDoor($1); }
;

gmstmt : GAME LPAREN DIGIT RPAREN { genGame($3); }
    | ID                    { genIdentifierGame($1); }
    | gmstmt ADDM mapstmt    { addMap(); }
    | gmstmt ADDP plrstmt    { addPlr(); }
;
%%

int yyerror(char* s) {
    printf("error: %s\n", s);
}

int main(int argc, char**argv) {
    extern FILE* yyin;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("%s doesn't exist\n", argv[1]);
            return -1;
        }
    }
    yyparse();

    printf("compiling...\n");
    compileCPP();

    cleanupSymbols();
}
