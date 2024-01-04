cd ".\compiler_files"
..\win_flex_bison3-latest\win_flex.exe expr.lex 
..\win_flex_bison3-latest\win_bison.exe -vd expr.y 
gcc .\lex.yy.c .\expr.tab.c 
pause