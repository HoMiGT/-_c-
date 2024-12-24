#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <memory>

// 抽象表达式类
class Expression {
public:
	virtual int interpret(const std::map<std::string, int>& context) = 0;
	virtual ~Expression() = default;
};

// 变量表达式类
class VariableExpression : public Expression {
	std::string name_;

public:
	VariableExpression(const std::string& name) : name_(name) {}
	int interpret(const std::map<std::string, int>& context) override {
		return context.at(name_);
	}

};

// 常量表达式类
class ConstantExpression : public Expression {
	int value_;
public:
	ConstantExpression(int value) : value_(value) {}
	int interpret(const std::map<std::string, int>& context)override {
		return value_;
	}
};

// 加法表达式类
class AddExpression : public Expression {
	std::unique_ptr<Expression> left_;
	std::unique_ptr<Expression> right_;

public:
	AddExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) : left_(std::move(left)), right_(std::move(right)) {}
	int interpret(const std::map<std::string, int>& context)override {
		return left_->interpret(context) + right_->interpret(context);
	}
};

// 减法表达式类
class SubtractExpression : public Expression {
	std::unique_ptr<Expression> left_;
	std::unique_ptr<Expression> right_;
public:
	SubtractExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) : left_(std::move(left)), right_(std::move(right)) {}
	int interpret(const std::map<std::string, int>& context) override {
		return left_->interpret(context) - right_->interpret(context);
	}
};

int main() {
	// 构建表达式 a + b - c
	std::unique_ptr<Expression> expression = std::make_unique<SubtractExpression>(
		std::make_unique<AddExpression>(
			std::make_unique<VariableExpression>("a"),
			std::make_unique<VariableExpression>("b")
		),
		std::make_unique<VariableExpression>("c")
	);

	// 上下文
	std::map<std::string, int> context = {
		{ "a", 10 },
		{ "b", 5 },
		{ "c", 3 }
	};

	// 解释器表达式
	std::cout << "Result: " << expression->interpret(context) << std::endl;

	return 0;
}

