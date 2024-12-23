#include <iostream>
#include <memory>

// 抽象产品A
class AbstractProductA {
public:
	virtual ~AbstractProductA() = default;
	virtual void operationA() const = 0;
};

// 具体产品A1
class ConcreteProductA1 : public AbstractProductA {
public:
	void operationA() const override {
		std::cout << "ConcreteProductA1::operationA" << std::endl;
	}
};

// 具体产品A2
class ConcreteProductA2 : public AbstractProductA {
public:
	void operationA() const override {
		std::cout << "ConcreteProductA2::operationA" << std::endl;
	}
};

// 抽象产品B
class AbstractProductB {
public:
	virtual ~AbstractProductB() = default;
	virtual void operationB() const = 0;
};

// 具体产品B1
class ConcreteProductB1 : public AbstractProductB {
public:
	void operationB() const override {
		std::cout << "ConcreteProductB1::operationB" << std::endl;
	}
};

// 具体产品B2
class ConcreteProductB2 : public AbstractProductB {
public:
	void operationB() const override {
		std::cout << "ConcreteProductB2::operationB" << std::endl;
	}
};

// 抽象工厂
class AbstractFactory {
public:
	virtual ~AbstractFactory() = default;
	virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
	virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
};

// 具体工厂1
class ConcreteFactory1 : public AbstractFactory {
public:
	std::unique_ptr<AbstractProductA> createProductA() const override {
		return std::make_unique<ConcreteProductA2>();
	}
	std::unique_ptr<AbstractProductB> createProductB() const override {
		return std::make_unique<ConcreteProductB2>();
	};
};

class ConcreteFactory2 : public AbstractFactory {
public:
	std::unique_ptr<AbstractProductA> createProductA() const override {
		return std::make_unique<ConcreteProductA2>();
	}
	std::unique_ptr<AbstractProductB> createProductB() const override {
		return std::make_unique<ConcreteProductB2>();
	};
};

int main() {
	std::unique_ptr<AbstractFactory> factory1 = std::make_unique<ConcreteFactory1>();
	auto productA1 = factory1->createProductA();
	auto productB1 = factory1->createProductB();
	productA1->operationA();
	productB1->operationB();

	std::unique_ptr<AbstractFactory> factory2 = std::make_unique<ConcreteFactory2>();
	auto productA2 = factory2->createProductA();
	auto productB2 = factory2->createProductB();
	productA2->operationA();
	productB2->operationB();
	return 0;
}