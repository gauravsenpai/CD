%{
#include <stdio.h>
int identifier_count = 0;

int keyword_count = 0;
int newline_count = 0;
int tab_count = 0;
int whitespace_count = 0;
int character_count = 0;
int nnn = 0;
%}



%%
int|float|char|if|else|scanf|printf { keyword_count++; }
[a-zA-Z][a-zA-Z0-9]*   { identifier_count++;}
[0-9]+ {nnn++;}
[\n]                     { newline_count++; }
[\t]                {tab_count++;}
[ ]+             { whitespace_count++; }
.                      { character_count++; }
%%



int main() {
    yylex();


    printf("Identifiers: %d\n", identifier_count);

    printf("Keywords: %d\n", keyword_count);

    printf("Numbers: %d\n", nnn);

    printf("Characters: %d\n", character_count);

    printf("Newlines: %d\n", newline_count);

    printf("Whitespaces: %d\n", whitespace_count);

    printf("tabspaces: %d\n", tab_count);


    return 0;
}


int yywrap(){
    return 1;
}