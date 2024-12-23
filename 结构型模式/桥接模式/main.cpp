#include <iostream>
#include <memory>

// 实现部分接口
class Implementor {
public:
	virtual void OperationImpl() = 0;
	virtual ~Implementor() = default;
};

// 具体实现A
class ConcreteImplementorA : public Implementor {
public:
	void OperationImpl() override {
		std::cout << "ConcreteImplementorA::OperationImpl()" << std::endl;
	}
};

// 具体实现B
class ConcreteImplementorB : public Implementor {
public:
	void OperationImpl() override {
		std::cout << "ConcreteImplementorB::OperationImpl()" << std::endl;
	}
};

// 抽象部分
class Abstraction {
protected:
	std::shared_ptr<Implementor> implementor;
public:
	Abstraction(std::shared_ptr<Implementor> impl) : implementor(impl) {};
	virtual void Operation() {
		implementor->OperationImpl();
	}
	virtual ~Abstraction() = default;
};

// 扩展抽象部分
class RefinedAbstraction : public Abstraction {
public:
	RefinedAbstraction(std::shared_ptr<Implementor> impl) : Abstraction(impl) {}
	void Operation() override {
		std::cout << "RefinedAbstraction::Operation()" << std::endl;
		implementor->OperationImpl();
	}
};



int main() {
	std::shared_ptr<Implementor> implA = std::make_shared<ConcreteImplementorA>();
	std::shared_ptr<Implementor> implB = std::make_shared<ConcreteImplementorB>();

	Abstraction* abstractionA = new RefinedAbstraction(implA);
	Abstraction* abstractionB = new RefinedAbstraction(implB);

	abstractionA->Operation();
	abstractionB->Operation();

	delete abstractionA;
	delete abstractionB;

	return 0;
}