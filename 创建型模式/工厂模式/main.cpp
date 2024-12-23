#include <iostream>
#include <memory>

// 产品接口
class Product {
public:
	virtual void use() const = 0;
	virtual ~Product() = default;
};

// 具体产品A
class ConcreteProductA : public Product {
public:
	void use() const override {
		std::cout << "Using ConcreteProductA" << std::endl;
	}
};

// 具体产品B
class ConcreteProductB : public Product {
public:
	void use() const override {
		std::cout << "Using ConcreteProductB" << std::endl;
	}
};

// 工厂接口

class Factory {
public:
	virtual std::unique_ptr<Product> createProduct();
	virtual ~Factory() = default;
};

// 具体工厂A
class ConcreteFactoryA : public Factory {
public:
	std::unique_ptr<Product> createProduct() override {
		return std::make_unique<ConcreteProductA>();
	}
};

// 具体工厂B
class ConcreteFactoryB : public Factory {
public:
	std::unique_ptr<Product> createProduct() override {
		return std::make_unique<ConcreteProductB>();
	}
};

int main() {
	std::unique_ptr<Factory> factoryA = std::make_unique<ConcreteFactoryA>();
	std::unique_ptr<Product> productA = factoryA->createProduct();
	productA->use();

	std::unique_ptr<Factory> factoryB = std::make_unique<ConcreteFactoryB>();
	std::unique_ptr<Product> productB = factoryB->createProduct();
	productB->use();

	return 0;
}