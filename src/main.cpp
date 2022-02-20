#include <iostream>
#include <string>
#include <any>

enum SyntaxKind {
	Number,
	Whitespace,
	Plus,
	Minus,
	Multiply,
	Divide,
	OpenParenthesis,
	CloseParenthesis,
	Bad,
	End,
};

class SyntaxToken {
private:
	SyntaxKind kind;
	int position;
	std::string text;
	std::any value;
public:
	SyntaxToken(SyntaxKind kind, int position, std::string text, std::any value){
		this->kind = kind;
		this->position = position;
		this->text = text;
		this->value = value;
	}

	std::string getText() const { return text; }
	int getPosition() const { return position; }
	SyntaxKind getKind() const { return kind; }

};


class Lexer {
private:
	std::string text;
	unsigned int position;
	char getCurrentToken() const { 
		if (this->position >= text.length()) {
			return '\0';
		}
		
		return text[position]; 
	}

	void next() {
		this->position++;
	}

public:
	Lexer(std::string text) {
		this->text = text;
		this->position = 0;
	}

	SyntaxToken NextToken() {
		if (this->position >= this->text.length()) {
			return SyntaxToken(End,this->position,"\0", nullptr);
		}
		
		if (isdigit(getCurrentToken())) {
			unsigned int start = position;
			while (isdigit(getCurrentToken())) {
				next();
			}
			std::string token = text.substr(start, this->position - start);
			int value = std::stoi(token);
			return SyntaxToken(Number, start, token, value);
		} 

		if (isspace(getCurrentToken())) {
			unsigned int start = position;
			while (isspace(getCurrentToken())) {
				next();
			}
			std::string token = text.substr(start, this->position - start);
			return SyntaxToken(Whitespace, start, token, nullptr);
		}

		if (getCurrentToken() == '+') { return SyntaxToken(Plus, position++, "+", nullptr); }
		if (getCurrentToken() == '-') { return SyntaxToken(Minus, position++, "-", nullptr); }
		if (getCurrentToken() == '*') { return SyntaxToken(Multiply, position++, "*", nullptr); }
		if (getCurrentToken() == '/') { return SyntaxToken(Divide, position++, "/", nullptr); }
		if (getCurrentToken() == '(') { return SyntaxToken(OpenParenthesis, position++, "(", nullptr); }
		if (getCurrentToken() == ')') { return SyntaxToken(CloseParenthesis, position++, ")", nullptr); }

		return SyntaxToken(Bad, position++, text.substr(this->position - 1,1), nullptr);		
	}
};



int main(int argc, char *argv[])
{
	while (true) {
		std::cout << "Welcome, Pls input exression: ";
		std::string input;
		getline(std::cin, input);
		// TODO: 判断input全部是空格的情况,不能直接回车
		if (input.empty()) return 0;

		Lexer *lexer = new Lexer(input);
		while(true) {
			SyntaxToken token = lexer->NextToken();
			if (token.getKind() == End) 
				break;
			std::cout << "token kind : " << token.getKind() << "  token text : " << token.getText() << "  token position : " << token.getPosition() <<std::endl; 
		}
		delete lexer;
	}
}