#include <iostream>
#include <string>
#include <vector>

// 前向声明
class Colleague;
class ConcreteColleague1;
class ConcreteColleague2;

// 中介者接口
class Mediator {
public:
	virtual void send(const std::string& message, Colleague* colleague) = 0;
};

// 具体中介者
class ConcreteMediator : public Mediator {
private:
	ConcreteColleague1* colleague1;
	ConcreteColleague2* colleague2;

public:
	void setColleague1(ConcreteColleague1* c) {
		colleague1 = c;
	}

	void setColleague2(ConcreteColleague2* c) {
		colleague2 = c;
	}

	void send(const std::string& message, Colleague* colleague) override;
};

// 同事类
class Colleague {
protected:
	Mediator* mediator;

public:
	Colleague(Mediator* m) : mediator(m) {}
	virtual void send(const std::string& message) = 0;
	virtual void receive(const std::string& message) = 0;
};

// 具体同事类1
class ConcreteColleague1 : public Colleague {
public:
	ConcreteColleague1(Mediator* m) : Colleague(m) {}

	void send(const std::string& message) override {
		mediator->send(message, this);
	}

	void receive(const std::string& message) override {
		std::cout << "ConcreteColleague1 received: " << message << std::endl;
	}
};

// 具体同事类2
class ConcreteColleague2 : public Colleague {
public:
	ConcreteColleague2(Mediator* m) : Colleague(m) {}

	void send(const std::string& message) override {
		mediator->send(message, this);
	}

	void receive(const std::string& message) override {
		std::cout << "ConcreteColleague2 received: " << message << std::endl;
	}
};

// 具体中介者方法实现
void ConcreteMediator::send(const std::string& message, Colleague* colleague) {
	if (colleague == colleague1) {
		colleague2->receive(message);
	}
	else if (colleague == colleague2) {
		colleague1->receive(message);
	}
}

int main() {
	ConcreteMediator* mediator = new ConcreteMediator();

	ConcreteColleague1* colleague1 = new ConcreteColleague1(mediator);
	ConcreteColleague2* colleague2 = new ConcreteColleague2(mediator);

	mediator->setColleague1(colleague1);
	mediator->setColleague2(colleague2);

	colleague1->send("Hello, Colleague2!");
	colleague2->send("Hi, Colleague1!");

	delete colleague1;
	delete colleague2;
	delete mediator;

	return 0;
}
