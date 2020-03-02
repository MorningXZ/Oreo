/*************************************************
File: token.h
Describe:词法基本元素定义
Author: 10127
Date: 2020/02/28
Version:
Other:
****************************************************/
#ifndef token_h__
#define token_h__
#include <string>

//Token基类
class Token
{
public:
	enum TokenType
	{
		TOKEN_NA = 0,	//NA
		TOKEN_INT,		//整型
		TOKEN_DOUBLE,	//浮点数
		TOKEN_STRING,	//字符串
		TOKEN_ID,		//标识符
		TOKEN_SYMBOL,	//符号
		TOKEN_EOF,		//结束符
		TOKEN_EOL,		//换行符
	};

	//构造函数
	Token(unsigned int lineNo, unsigned int colNo, TokenType type)
		:m_lineNo(lineNo), m_colNo(colNo),m_type(type){}

	~Token(){};

	//获取Token类型
	TokenType type(){ return m_type; }

	//Token所在行号
	unsigned int lineNo(){ return m_lineNo; }

	//Token所在列号
	unsigned int columnNo(){ return m_colNo; }

	//返回Token对应字符串
	virtual std::string toString() = 0;

private:
	TokenType m_type;		//Token类型
	unsigned int m_lineNo;	//Token行号
	unsigned int m_colNo;	//Token列号
};

//整数Token
class TokenInt: public Token
{
public:
	TokenInt(unsigned int lineNo, unsigned int colNo, int val) 
		:Token(lineNo, colNo, TOKEN_INT), m_val(val){}

	~TokenInt(){}

	int value(){ return m_val; }

	virtual std::string toString(){ return std::to_string(m_val); }

private:
	int m_val;
};

//浮点数Token
class TokenDouble : public Token
{
public:
	TokenDouble(unsigned int lineNo, unsigned int colNo, double val)
		:Token(lineNo, colNo, TOKEN_DOUBLE), m_val(val){}

	~TokenDouble(){}

	double value(){ return m_val; }

	virtual std::string toString(){ return std::to_string(m_val); }

private:
	double m_val;
};

class TokenString : public Token
{
public:
	TokenString(unsigned int lineNo, unsigned int colNo, const std::string& str)
		:Token(lineNo, colNo, TOKEN_ID), m_str(str){}

	~TokenString(){}

	std::string value(){ return m_str; }

	virtual std::string toString(){ return m_str; }

private:
	std::string m_str;
};


class TokenID : public Token
{
public:
	TokenID(unsigned int lineNo, unsigned int colNo, const std::string& id)
		:Token(lineNo, colNo, TOKEN_STRING), m_id(id){}

	~TokenID(){}

	std::string value(){ return m_id; }

	virtual std::string toString(){ return m_id; }

private:
	std::string m_id;
};

class TokenSymbol : public Token
{
public:
	TokenSymbol(unsigned int lineNo, unsigned int colNo, const std::string& symbol)
		:Token(lineNo, colNo, TOKEN_SYMBOL), m_symbol(symbol){}

	~TokenSymbol(){}

	std::string value(){ return m_symbol; }

	virtual std::string toString(){ return m_symbol; }

private:
	std::string m_symbol;
};


//结束符Token
class TokenEof : public Token
{
public:
	TokenEof() :Token(0, 0, TOKEN_EOF){}

	~TokenEof(){}

	virtual std::string toString(){ return NULL; }
};


class TokenEol : public Token
{
public:
	TokenEol(unsigned int lineNo, unsigned int colNo) :Token(lineNo, colNo, TOKEN_EOL){}
	
	~TokenEol(){}

	virtual std::string toString(){ return "\n"; }
};


#endif // token_h__
