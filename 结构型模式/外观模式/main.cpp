#include <iostream>

// 子系统A
class SubsystemA {
public:
	void operationA() {
		std::cout << "SubsystemA: operationA" << std::endl;
	}
};

// 子系统B
class SubsystemB {
public:
	void operationB() {
		std::cout << "SubsystemB: operationB" << std::endl;
	}
};

// 子系统C
class SubsystemC {
public:
	void operationC() {
		std::cout << "SubsystemC: operationC" << std::endl;
	}
};

// 外观类
class Facade {
public:
	Facade() : subsystemA(), subsystemB(), subsystemC() {}

	void operation() {
		subsystemA.operationA();
		subsystemB.operationB();
		subsystemC.operationC();
	}

private:
	SubsystemA subsystemA;
	SubsystemB subsystemB;
	SubsystemC subsystemC;
};


int main() {
	Facade facade;
	facade.operation();
	return 0;
}