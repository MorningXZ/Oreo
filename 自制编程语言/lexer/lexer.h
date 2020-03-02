/*************************************************
File: lexer.h
Describe:词法解析器
Author: 10127
Date: 二月 2020
Version:0.01
Other:
****************************************************/
#ifndef lexer_h__
#define lexer_h__
#include "token.h"

#include <list>
#include <regex>
#include <memory>
#include <iostream>

typedef std::shared_ptr<Token> SpToken;
typedef std::list<SpToken> Tokens;

class Lexer
{
public:
	Lexer(std::istream* reader);
	~Lexer();

	//获取一个Token
	SpToken read(bool isPeek = false);

	//预读取igeToken
	SpToken peek();

private:
	bool parserNewLine();

	bool parser(std::string &str);

	void createToken(const std::string& str, int matchNo, int colNum);

	void errMsg(const std::string& msg);
private:
	std::istream* m_reader;									//IO读取对象
	std::regex* m_regex;								//正则表达式
	unsigned int m_lineNo;								//行号
	Tokens m_tokens;									//token集合
	bool m_commentBegin;
};


//正则表达式解释：
//	整数:	(0x[0-9]+)|(0X[0-9]+)|([0-9]+)
//	浮点数:	([0-9]+.[0-9]*)
//	字符串:	"(\\"|\\\\|\\n|[^\"])*\"
//	注释:	(//.*)|(/\*(.|\n)*\*/)
//			第一种注释//.*			//这是一个注释
//			第二种注释/\*(.|\n)*\*/	/*这是一个注释*/
//	标识符:	[A-Z_a-z][A-Z_a-z0-9]*
//	特殊符号:[\+\-\*%/=&!\(\);\.,]|==|>=|<=|\|\||&&|!=
//	空白字符:\s
//
//	整数浮点数标识符集合[A-Z_a-z0-9.]*

//	判断一个给定的字符串是否是指定类型，正则表达式如下，要完全匹配，所以使用了^$限定符
//

#endif // lexer_h__
