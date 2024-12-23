#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Prototype {
public:
	virtual ~Prototype() = default;
	virtual std::unique_ptr<Prototype> clone() const = 0;
	virtual void print() const = 0;
};

// 具体原型类1
class ConcretePrototype1 : public Prototype {
public:
	ConcretePrototype1(const std::string& name) : name_(name) {}
	std::unique_ptr<Prototype> clone() const override {
		return std::make_unique<ConcretePrototype1>(*this);
	}
	void print() const override {
		std::cout << "ConcretePrototype1: " << name_ << std::endl;
	}

private:
	std::string name_;
};

// 具体原型类2
class ConcretePrototype2 : public Prototype {
public:
	ConcretePrototype2(const std::string& name) : name_(name) {}
	std::unique_ptr<Prototype> clone() const override {
		return std::make_unique<ConcretePrototype2>(*this);
	}
	void print() const override {
		std::cout << "ConcretePrototype2: " << name_ << std::endl;
	}

private:
	std::string name_;
};

// 原型工厂
class PrototypeFactory {
public:
	PrototypeFactory() {
		prototypes_["type1"] = std::make_unique<ConcretePrototype1>("Default1");
		prototypes_["type2"] = std::make_unique<ConcretePrototype2>("Default2");
	}

	std::unique_ptr<Prototype> createPrototype(const std::string& type) {
		return prototypes_[type]->clone();
	}

private:
	std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes_;
};

int main() {

	PrototypeFactory factory;
	auto prototype1 = factory.createPrototype("type1");
	prototype1->print();

	auto prototype2 = factory.createPrototype("type2");
	prototype2->print();

	return 0;
}