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

	SyntaxToken NewToken(std::string text, int position, SyntaxKind kind) {
		
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
};
```

