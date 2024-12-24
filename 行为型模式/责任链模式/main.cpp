#include <iostream>
#include <memory>

// 抽象处理者类
class Handler {
public:
	virtual  ~Handler() = default;
	void setNext(std::shared_ptr<Handler> nextHandler) {
		next = nextHandler;
	}

	void handleRequest(int request) {
		if (canHandle(request)) {
			handle(request);
		}
		else if (next) {
			next->handleRequest(request);
		}
		else {
			std::cout << "No handler could handle the requset" << std::endl;
		}
	}


protected:
	virtual bool canHandle(int request) = 0;
	virtual void handle(int request) = 0;

private:
	std::shared_ptr<Handler> next{ nullptr };

};


// 具体处理者类
class ConcreteHandlerA : public Handler {
protected:
	bool canHandle(int request) override {
		return request < 10;
	}
	void handle(int request) override {
		std::cout << "ConcreteHandlerA: " << request << std::endl;
	}
};

// 具体处理者类B
class ConcreteHandlerB : public Handler {
protected:
	bool canHandle(int request) override {
		return request >= 10 && request < 20;
	}
	void handle(int request) override {
		std::cout << "ConcreteHandlerB: " << request << std::endl;
	}
};

// 具体处理者类C
class ConcreteHandlerC : public Handler {
protected:
	bool canHandle(int request) override {
		return request >= 20;
	}
	void handle(int request) override {
		std::cout << "ConcreteHandlerC: " << request << std::endl;
	}
};



int main() {
	auto handlerA = std::make_shared<ConcreteHandlerA>();
	auto handlerB = std::make_shared<ConcreteHandlerB>();
	auto handlerC = std::make_shared<ConcreteHandlerC>();

	handlerA->setNext(handlerB);
	handlerB->setNext(handlerC);

	int requests[] = { 2, 5, 14, 22, 18, 3, 27, 20 };
	for (int request : requests) {
		handlerA->handleRequest(request);
	}
	return 0;
}