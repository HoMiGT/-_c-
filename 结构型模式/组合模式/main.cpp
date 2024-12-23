#include <iostream>
#include <vector>
#include <memory>

// 抽象基类
class Component {
public:
	virtual ~Component() = default;
	virtual void Operation() const = 0;
	virtual void Add(std::shared_ptr<Component> component) {};
	virtual void Remove(std::shared_ptr<Component> component) {};
	virtual std::shared_ptr<Component> GetChild(int index) const { return nullptr; };

};

// 叶子节点
class Leaf : public Component {
public:
	void Operation() const override {
		std::cout << "Leaf Operation" << std::endl;
	}
};

// 组合节点
class Composite : public Component {
private:
	std::vector<std::shared_ptr<Component>> children;
public:
	void Operation() const override {
		std::cout << "Composite Operation" << std::endl;
		for (const auto& child : children) {
			child->Operation();
		}
	}

	void Add(std::shared_ptr<Component> component)override {
		children.emplace_back(component);
	}

	void Remove(std::shared_ptr<Component> component) override {
		children.erase(std::remove(children.begin(), children.end(), component), children.end());
	}

	std::shared_ptr<Component> GetChild(int index)const override {
		if (index >= 0 && index < children.size()) {
			return children[index];
		}
		return nullptr;
	}
};


int main() {
	std::shared_ptr<Component> leaf1 = std::make_shared<Leaf>();
	std::shared_ptr<Component> leaf2 = std::make_shared<Leaf>();
	std::shared_ptr<Component> composite = std::make_shared<Composite>();

	composite->Add(leaf1);
	composite->Add(leaf2);
	composite->Operation();
	return 0;
}