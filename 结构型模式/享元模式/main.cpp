#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

// 享元类
class Flyweight {
public:
	Flyweight(const std::string& intrinsicState) : instrinsicState_(intrinsicState) {};
	void operation(const std::string& extrinsicState) {
		std::cout << "instrinsicState: " << instrinsicState_ << " extrinsicState: " << extrinsicState << std::endl;
	}

private:
	std::string instrinsicState_;
};

// 享元工厂类
class FlyweightFactory {
public:
	std::shared_ptr<Flyweight> getFlyweight(const std::string& key) {
		if (flyweights_.find(key) == flyweights_.end()) {
			flyweights_[key] = std::make_shared<Flyweight>(key);
		}
		return flyweights_[key];
	};

private:
	std::unordered_map<std::string, std::shared_ptr<Flyweight>> flyweights_;
};


int main() {
	FlyweightFactory factory;

	auto flyweight1 = factory.getFlyweight("state1");
	flyweight1->operation("Context1");

	auto flyweight2 = factory.getFlyweight("state2");
	flyweight2->operation("Context2");

	auto flyweight3 = factory.getFlyweight("state1");
	flyweight3->operation("Context3");

	return 0;
}