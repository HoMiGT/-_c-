#include <iostream>
#include <memory>

// 旧接口
class OldInterface {
public:
	virtual void oldRequest() const {
		std::cout << "Old request" << std::endl;
	}
};

class NewInterface {
public:
	virtual void newRequest() const = 0;
};

class Adapter : public NewInterface {
private:
	std::shared_ptr<OldInterface> oldInterface;

public:
	Adapter(std::shared_ptr<OldInterface> oldInterface) : oldInterface(oldInterface) {};

	void newRequest() const override {
		std::cout << "Before adjustment" << std::endl;
		oldInterface->oldRequest();
		std::cout << "After adjustment" << std::endl;
	}
};


int main() {
	std::shared_ptr<OldInterface> oldInterface = std::make_shared<OldInterface>();
	std::shared_ptr<NewInterface> adapter = std::make_shared<Adapter>(oldInterface);
	adapter->newRequest();

	return 0;
}