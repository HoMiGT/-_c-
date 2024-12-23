#include <iostream>
#include <mutex>

/// <summary>
/// 单例模式
/// </summary>
class Singleton {
public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	void showMessage() {
		std::cout << "Hello, Singleton!" << std::endl;
	}

private:
	Singleton() {
		std::cout << "Singleton instance created!" << std::endl;
	}
	~Singleton() {
		std::cout << "Singleton instance destroyed!" << std::endl;
	}

};

int main() {
	Singleton& instance = Singleton::getInstance();
	instance.showMessage();
	std::cout << "instance id: " << &instance << std::endl;
	Singleton& instance2 = Singleton::getInstance();
	instance2.showMessage();
	std::cout << "instance2 id: " << &instance2 << std::endl;
	return 0;
}