### 摘要

本节实现了一下3点

- 1
- 2
- 3

### 具体实现

#### 定义分析Lexer类

```c++
class Lexer {
private:
	std::string text;

public:
	Lexer(std::string text) {
		this->text = text;
	}
};
```

#### 定义Token类

```c++
class SyntaxToken {
private:
	SyntaxKind kind;
	int position;
	std::string text;
public:
	SyntaxToken(SyntaxKind kind, int position, std::string text){
		this->kind = kind;
		this->position = position;
		this->text = text;
	}

	std::string getText() const { return text; }
	int getPosition() const { return position; }
	SyntaxKind getKind() const { return kind; }
};
```

#### 枚举单词Token类型

```c++
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
```

#### 定义NextToken函数

```c++
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
```

#### 定义main，测试解析token

```c++
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
```

视频位置：30min

```bash
Welcome, Pls input exression: 123 + 345
token kind : 0  token text : 123  token position : 0
token kind : 1  token text :    token position : 3
token kind : 2  token text : +  token position : 4
token kind : 1  token text :    token position : 5
token kind : 0  token text : 345  token position : 6
```

#### 要实现的效果

<img src="https://gitee.com/zhangtinglu/blog_pic/raw/master/uPic/image-20220225084619998.png" alt="image-20220225084619998" style="zoom:50%;float:left" />

