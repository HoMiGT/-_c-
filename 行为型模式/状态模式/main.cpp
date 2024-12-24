#include <iostream>
#include <memory>

// 前向声明
class Context;
class ConcreteStateB;

// 状态基类
class State {
public:
	virtual ~State() = default;
	virtual void handle(Context& context) = 0;
};

// 上下文类
class Context {
public:
	Context(std::unique_ptr<State> state) : state_(std::move(state)) {}
	void setState(std::unique_ptr<State> state) {
		state_ = std::move(state);
	}
	void request() {
		if (state_) {
			state_->handle(*this);
		}
	}
private:
	std::unique_ptr<State> state_;
};

// 具体状态A
class ConcreteStateA : public State {
public:
	void handle(Context& context) override;
};

// 具体状态B
class ConcreteStateB : public State {
public:
	void handle(Context& context) override {
		std::cout << "ConcreteStateB::handle()" << std::endl;
		context.setState(std::make_unique<ConcreteStateA>());
	}
};

void ConcreteStateA::handle(Context& context) {
	std::cout << "ConcreteStateA::handle()" << std::endl;
	context.setState(std::make_unique<ConcreteStateB>());
}

int main() {
	Context context(std::make_unique<ConcreteStateA>());
	context.request();
	context.request();
	context.request();
	return 0;
}
