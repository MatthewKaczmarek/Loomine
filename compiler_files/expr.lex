%{
    #include "expr.tab.h"

    #define YY_SKIP_YYWRAP
    int yywrap() { return 1; }
%}

ID [a-z][a-z0-9]*
CHARACTER \".\"
DIGIT [0-9]
LPAREN [(]
RPAREN [)]
COMMA [,]

%%

{LPAREN} {
    return (LPAREN);
}

{RPAREN} {
    return (RPAREN);
}

"map" {
    return (MAP);
}

"player" {
    return (PLAYER);
}

"game" {
    return (GAME);
}

"door" {
    return (DOOR);
}

"enemy" {
    return (ENEMY);
}

"addM" {
    return (ADDM);
}

"addP" {
    return (ADDP);
}

"addD" {
    return (ADDD);
}

"addE" {
    return (ADDE);
}

"run" {
    return (RUN);
}

{DIGIT}+ {
    yylval.val = (char*) strdup(yytext);
    return (DIGIT);
}

{ID} {
    yylval.id = (char*) strdup(yytext);
    return (ID);
}

{CHARACTER} {
    yylval.val = (char*) strdup(yytext);
    return (CHARACTER);
}

"," {
    return (COMMA);
}

":=" {
    return (ASSIGNOP);
}

"$$" {
    return (END);
}

[ \t\n\r]+ /* eat up whitespace */
. { printf( "Unknown: '%s'\n", yytext ); }

%%