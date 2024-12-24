#include <iostream>

// 抽象类定义算法框架
class AbstractClass {
public:
	// 模板方法，定义了算法框架
	void TemplateMethod() {
		BaseOperation1();
		RequiredOperation1();
		BaseOperation2();
		RequiredOperation2();
		Hook();
	}

protected:
	// 基本操作，子类可以重写
	void BaseOperation1() {
		std::cout << "AbstractClass::BaseOperation1" << std::endl;
	}
	void BaseOperation2() {
		std::cout << "AbstractClass::BaseOperation2" << std::endl;
	}

	// 必须由子类实现的操作
	virtual void RequiredOperation1() = 0;
	virtual void RequiredOperation2() = 0;
	// 钩子方法，子类可以选择性重写
	virtual void Hook() {}

};

// 具体类实现抽象类的纯虚函数
class ConcreteClassA : public AbstractClass {
protected:
	void RequiredOperation1() override {
		std::cout << "ConcreteClassA::RequiredOperation1" << std::endl;
	}
	void RequiredOperation2() override {
		std::cout << "ConcreteClassA::RequiredOperation2" << std::endl;
	}
	void Hook() override {
		std::cout << "ConcreteClassA::Hook" << std::endl;
	}

};


class ConcreteClassB : public AbstractClass {
protected:
	void RequiredOperation1() override {
		std::cout << "ConcreteClassB::RequiredOperation1" << std::endl;
	}
	void RequiredOperation2() override {
		std::cout << "ConcreteClassB::RequiredOperation2" << std::endl;
	}

};


int main() {
	ConcreteClassA a;
	ConcreteClassB b;
	std::cout << "a: ";
	a.TemplateMethod();
	std::cout << "b: ";
	b.TemplateMethod();

	return 0;
}