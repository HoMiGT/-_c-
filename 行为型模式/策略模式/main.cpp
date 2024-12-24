#include <iostream>
#include <memory>

// 策略接口
class Strategy {
public:
	virtual ~Strategy() = default;
	virtual int execute(int a, int b) const = 0;
};

// 具体策略：加法
class AddStrategy : public Strategy {
public:
	int execute(int a, int b) const override {
		return a + b;
	}
};

// 具体策略：减法
class SubtractStrategy : public Strategy {
public:
	int execute(int a, int b) const override {
		return a - b;
	}

};

// 上下文类
class Context {
private:
	std::unique_ptr<Strategy> strategy;

public:
	void setStrategy(std::unique_ptr<Strategy> newStrategy) {
		strategy = std::move(newStrategy);
	}

	int executeStrategy(int a, int b) const {
		return strategy->execute(a, b);
	}
};



int main() {
	Context context;

	// 使用加法策略
	context.setStrategy(std::make_unique<AddStrategy>());
	std::cout << "10 + 5 = " << context.executeStrategy(10, 5) << std::endl;

	// 使用减法策略
	context.setStrategy(std::make_unique<SubtractStrategy>());
	std::cout << "10 - 5 = " << context.executeStrategy(10, 5) << std::endl;


	return 0;
}