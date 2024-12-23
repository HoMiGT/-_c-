#include <iostream>
#include <memory>

// coffee接口
class Coffee {
public:
	virtual ~Coffee() = default;
	virtual std::string getDescription() const = 0;
	virtual double getCost() const = 0;
};

// SimpleCoffee类
class SimpleCoffee : public Coffee {
public:
	std::string getDescription() const override {
		return "Simple Coffee";
	}
	double getCost() const override {
		return 5.0;
	}
};

// 装饰器基类，实现Coffee接口，并持有一个Coffee对象
class CoffeeDecorator : public Coffee {
protected:
	std::unique_ptr<Coffee> coffee;

public:
	CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee(std::move(coffee)) {};
	std::string getDescription() const override {
		return coffee->getDescription();
	}

	double getCost() const override {
		return coffee->getCost();
	}
};

class MilkDecorator : public CoffeeDecorator {
public:
	MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {};
	std::string getDescription() const override {
		return coffee->getDescription() + ", Milk";
	}

	double getCost() const override {
		return coffee->getCost() + 2.0;
	}

};

class SugarDecorator : public CoffeeDecorator {
public:
	SugarDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {};

	std::string getDescription() const override {
		return coffee->getDescription() + ", Sugar";
	}

	double getCost() const override {
		return coffee->getCost() + 1.0;
	}
};


int main() {
	std::unique_ptr<Coffee> myCoffee = std::make_unique<SimpleCoffee>();
	std::cout << myCoffee->getDescription() << " $" << myCoffee->getCost() << std::endl;

	myCoffee = std::make_unique<MilkDecorator>(std::move(myCoffee));
	std::cout << myCoffee->getDescription() << " $" << myCoffee->getCost() << std::endl;

	myCoffee = std::make_unique<SugarDecorator>(std::move(myCoffee));
	std::cout << myCoffee->getDescription() << " $" << myCoffee->getCost() << std::endl;
	return 0;
}