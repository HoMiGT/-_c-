#include <iostream>
#include <memory>

// Subject接口
class Subject {
public:
	virtual void request() const = 0;
	virtual ~Subject() = default;
};

// RealSubject类
class RealSubject : public Subject {
public:
	void request() const override {
		std::cout << "RealSubject: Handling request." << std::endl;
	}
};

class Proxy : public Subject {
private:
	mutable std::unique_ptr<RealSubject> realSubject{ nullptr };

	bool checkAccess()const {
		std::cout << "Proxy: Checking access prior to firing a real request." << std::endl;
		return true;
	}

	void logAccess() const {
		std::cout << "Proxy: Logging the time of request." << std::endl;
	}

public:
	void request() const override {
		if (this->checkAccess()) {
			if (!realSubject) {
				realSubject = std::make_unique<RealSubject>();
			}
			realSubject->request();
			this->logAccess();
		}
	}

};


int main() {
	std::unique_ptr<Subject> proxy = std::make_unique<Proxy>();
	proxy->request();

	return 0;
}