#include <iostream>
#include <vector>
#include <memory>

// 前向声明
class Element;
class ConcreteElementA;
class ConcreteElementB;

// 访问者接口
class Visitor {
public:
	virtual void visit(ConcreteElementA& element) = 0;
	virtual void visit(ConcreteElementB& element) = 0;
	virtual ~Visitor() = default;
};

// 元素接口
class Element {
public:
	virtual void accept(Visitor& visitor) = 0;
	virtual ~Element() = default;
};

// 具体元素A
class ConcreteElementA : public Element {
public:
	void accept(Visitor& visitor) override {
		visitor.visit(*this);
	}
	void operationA() const {
		std::cout << "ConcreteElementA operation." << std::endl;
	}
};

// 具体元素B
class ConcreteElementB : public Element {
public:
	void accept(Visitor& visitor) override {
		visitor.visit(*this);
	}
	void operationB() const {
		std::cout << "ConcreteElementB operation." << std::endl;
	}
};


// 具体访问者
class ConcreteVisitor : public Visitor {
public:
	void visit(ConcreteElementA& element) override {
		element.operationA();
	}
	void visit(ConcreteElementB& element) override {
		element.operationB();
	}
};


int main() {
	std::vector<std::unique_ptr<Element>> elements;
	elements.emplace_back(std::make_unique<ConcreteElementA>());
	elements.emplace_back(std::make_unique<ConcreteElementB>());

	ConcreteVisitor visitor;
	for (auto& element : elements) {
		element->accept(visitor);
	}

	return 0;
}