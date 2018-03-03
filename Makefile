
lexer_test:
	g++ -o test/lexer_test.exe test/lexer_test.cpp lexer.cpp 
parser_test:
	g++ -g -o test/parser_test.exe test/parser_test.cpp parser.cpp lexer.cpp util.cpp ast.cpp
