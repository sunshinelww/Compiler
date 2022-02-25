#include <iostream>
#include <string>
#include <any>
#include <boost/any.hpp>
#include <vector>

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
	NumberExpression,
	BinaryExpression,
};

class SyntaxToken {
private:
	SyntaxKind kind;
	int position;
	std::string text;
	boost::any value;
public:
	SyntaxToken(SyntaxKind kind, int position, std::string text, boost::any value){
		this->kind = kind;
		this->position = position;
		this->text = text;
		this->value = value;
	}
    SyntaxToken(): kind(Bad), position(0), text(""), value(nullptr){}
	// SyntaxToken(const SyntaxToken &rhs) : kind(rhs.kind), position(rhs.position), text(rhs.text), value(rhs.value) { }

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

	SyntaxToken nextToken() {
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

struct SyntaxNode {
	virtual SyntaxKind getKind() = 0;
};

struct ExpressionSyntax: SyntaxNode {
	virtual SyntaxKind getKind() = 0;
};

struct NumberExpressionSyntax final: ExpressionSyntax {
public:
	NumberExpressionSyntax(SyntaxToken numberToken) { this->numberToken = numberToken; }
	SyntaxKind getKind() override { return NumberExpression;}
private:
	SyntaxToken numberToken;
};

struct BinaryExpressionSyntax final: ExpressionSyntax {
	BinaryExpressionSyntax(ExpressionSyntax *left,SyntaxNode *operatorToken, ExpressionSyntax *right): left(left),operatorToken(operatorToken),right(right) {};
	ExpressionSyntax *getLeft() const {return this->left;}
	SyntaxNode *getOperatorToken() const { return this->operatorToken;}
	ExpressionSyntax *getRight() const {return this->right;}
	SyntaxKind getKind() override { return BinaryExpression;}

private:
	ExpressionSyntax *left;
	SyntaxNode *operatorToken;
	ExpressionSyntax *right;
};

class Parser {
private:
	std::vector<SyntaxToken> tokens;
	unsigned int position;

	SyntaxToken peek(int offset) {
		int index = offset + this->position;
		if (index >= tokens.size()) return tokens[tokens.size()-1];
		return tokens[index];
	}

	SyntaxToken current() { return peek(0);}

public:
	Parser(const std::string text) {
		Lexer *lexer = new Lexer(text);
		SyntaxToken token = lexer->nextToken();
		while (token.getKind() != End)
		{
			if (token.getKind() != Bad && token.getKind() != Whitespace)
			{
				this->tokens.push_back(token);
			}
			token = lexer->nextToken();
		}
		delete lexer;
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
			SyntaxToken token = lexer->nextToken();
			if (token.getKind() == End) 
				break;
			std::cout << "token kind : " << token.getKind() << "  token text : " << token.getText() << "  token position : " << token.getPosition() <<std::endl; 
		}
		delete lexer;
	}
}