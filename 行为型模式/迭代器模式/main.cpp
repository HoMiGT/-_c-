#include <iostream>
#include <vector>
#include <memory>

// 迭代器类
template<typename T>
class Iterator {
public:
	virtual ~Iterator() {}
	virtual T& next() = 0;
	virtual bool hasNext() const = 0;
};

// 集合类
template<typename T>
class Aggregate {
public:
	virtual ~Aggregate() {}
	virtual std::unique_ptr<Iterator<T>> createIterator() const = 0;
};

// 具体迭代器类
template<typename T>
class ConcreteIterator : public Iterator<T> {
public:
	ConcreteIterator(const std::vector<T>& items) :items_(items), index_(0) {}
	T& next() override {
		return items_[index_++];
	}

	bool hasNext() const override {
		return index_ < items_.size();
	}

private:
	std::vector<T> items_;
	size_t index_;

};

// 具体集合类
template<typename T>
class ConcreteAggregate : public Aggregate<T> {
public:
	ConcreteAggregate() : items_() {}

	void addItem(const T& item) {
		items_.emplace_back(item);
	}

	std::unique_ptr<Iterator<T>> createIterator() const override {
		return std::make_unique<ConcreteIterator<T>>(items_);
	}

private:
	std::vector<T> items_;
};


int main() {
	ConcreteAggregate<int> aggregate;
	aggregate.addItem(1);
	aggregate.addItem(2);
	aggregate.addItem(3);


	auto iterator = aggregate.createIterator();
	while (iterator->hasNext()) {
		std::cout << iterator->next() << ", ";
	}
	std::cout << std::endl;

	return 0;
}
