#include <iostream>
#include <string>
#include <memory>

// 产品类
class House {
public:
	void setWalls(const std::string& walls) {
		this->walls = walls;
	}
	void setRoof(const std::string& roof) {
		this->roof = roof;
	}
	void setWindows(const std::string& windows) {
		this->windows = windows;
	}

	void show() const {
		std::cout << "House with " << walls << " walls, " << roof << " roof and " << windows << " windows." << std::endl;
	}

private:
	std::string walls;
	std::string roof;
	std::string windows;
};

// 抽象建造者
template<typename T>
class Builder {
public:
	virtual ~Builder() {}
	virtual void buildWalls() = 0;
	virtual void buildRoof() = 0;
	virtual void buildWindows() = 0;
	virtual T* getProduct() = 0;
};

// 具体建造者类
template<typename T>
class ConcreteBuilder : public Builder<T> {
public:
	ConcreteBuilder() {
		this->product = std::make_unique<T>();
	}
	~ConcreteBuilder() = default;

	void buildWalls() override {
		product->setWalls("Concrete");
	}
	void buildRoof() override {
		product->setRoof("Concrete");
	}
	void buildWindows() override {
		product->setWindows("Concrete");
	}
	T* getProduct() override {
		return product.get();
	}

private:
	std::unique_ptr<T> product;
};

// 指导类
template<typename T>
class Director {
public:
	void setBuilder(Builder<T>* builder) {
		this->builder = builder;
	}
	T* construct() {
		builder->buildWalls();
		builder->buildRoof();
		builder->buildWindows();
		return builder->getProduct();
	}

private:
	Builder<T>* builder;
};

int main() {
	Director<House> director;
	ConcreteBuilder<House> builder;
	director.setBuilder(&builder);
	House* house = director.construct();
	house->show();

	return 0;
}