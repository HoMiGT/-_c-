#include <iostream>
#include <vector>
#include <memory>

// 观察者接口
class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(int value) = 0;
};

// 具体观察者
class ConcreteObserver : public Observer {
public:
	ConcreteObserver(const std::string& name) :name_(name)
	{
	}

	void update(int value) override {
		std::cout << "Observer: " << name_ << " update value: " << value << std::endl;
	}

private:
	std::string name_;

};

// 主题
class Subject {
public:
	void addObserver(std::shared_ptr<Observer> observer) {
		observers.emplace_back(observer);
	}

	void removeObserver(std::shared_ptr<Observer> observer) {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void notifyObservers() {
		for (const auto& observer : observers) {
			observer->update(value);
		}
	}

	void setValue(int newValue) {
		value = newValue;
		notifyObservers();
	}


private:
	std::vector<std::shared_ptr<Observer>> observers;
	int value{ 0 };
};

int main() {

	auto subject = std::make_shared<Subject>();

	auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
	auto observer2 = std::make_shared<ConcreteObserver>("Observer2");

	subject->addObserver(observer1);
	subject->addObserver(observer2);

	subject->setValue(42);
	subject->setValue(100);


	return 0;
}
