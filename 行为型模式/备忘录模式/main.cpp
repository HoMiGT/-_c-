#include <iostream>
#include <vector>
#include <string>

// 备忘录类
class Memento {
public:
	Memento(const std::string& state) : state_(state) {}
	std::string GetState() const { return state_; }

private:
	std::string state_;
};

// 发起者
class Originator {
public:
	void SetState(const std::string& state) {
		state_ = state;
		std::cout << "State set to: " << state << std::endl;
	}

	std::string GetState() const { return state_; }
	Memento SaveStateToMemento() {
		return Memento(state_);
	}

	void GetStateFromMemento(const Memento& memento) {
		state_ = memento.GetState();
	}

private:
	std::string state_;
};

// 管理者类
class Caretaker {
public:
	void AddMemento(const Memento& memento) {
		mementos_.emplace_back(memento);
	}

	Memento GetMemento(int index) const {
		if (index < 0 || index >= mementos_.size()) {
			throw std::out_of_range("Invalid index");
		}
		return mementos_[index];
	}


private:
	std::vector<Memento> mementos_;

};


int main() {
	Originator originator;
	Caretaker caretaker;

	originator.SetState("State #1");
	caretaker.AddMemento(originator.SaveStateToMemento());

	originator.SetState("State #2");
	caretaker.AddMemento(originator.SaveStateToMemento());

	originator.SetState("State #3");
	std::cout << "Current State: " << originator.GetState() << std::endl;

	originator.GetStateFromMemento(caretaker.GetMemento(0));
	std::cout << "First saved State: " << originator.GetState() << std::endl;

	originator.GetStateFromMemento(caretaker.GetMemento(1));
	std::cout << "Second save State: " << originator.GetState() << std::endl;


	return 0;
}