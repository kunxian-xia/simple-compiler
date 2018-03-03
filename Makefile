
lexer_test:
	g++ -o test/lexer_test.exe test/lexer_test.cpp src/lexer.cpp 
parser_test:
	g++ -g -o test/parser_test.exe test/parser_test.cpp src/parser.cpp src/lexer.cpp src/util.cpp src/ast.cpp

clean:
	rm test/parser_test.exe test/lexer_test.exe 
