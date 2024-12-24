#include <iostream>

// 定义命令接口
class Command {
public:
	virtual ~Command() = default;
	virtual void execute() const = 0;
};


// 定义一个电灯类
class Light {
public:
	void on() const {
		std::cout << "The Light is on" << std::endl;
	}
	void off() const {
		std::cout << "The Light is off" << std::endl;
	}
};

// 定义一个电灯开关命令
class LightOnCommand : public Command {
public:
	explicit LightOnCommand(const Light& light) : light_(light) {}
	void execute() const override {
		light_.on();
	}

private:
	const Light& light_;
};

class LightOffCommand : public Command {
public:
	explicit LightOffCommand(const Light& light) : light_(light) {}
	void execute() const override {
		light_.off();
	}

private:
	const Light& light_;

};

// 创建一个调用者类
class RemoteControl {
public:
	void setCommand(std::unique_ptr<Command> command) {
		command_ = std::move(command);
	}
	void pressButton() const {
		if (command_) {
			command_->execute();
		}
	}
private:
	std::unique_ptr<Command> command_;
};

int main() {

	Light liveingRoomLight;

	auto lightOn = std::make_unique<LightOnCommand>(liveingRoomLight);
	auto lightOff = std::make_unique<LightOffCommand>(liveingRoomLight);

	RemoteControl remote;
	remote.setCommand(std::move(lightOn));
	remote.pressButton();

	remote.setCommand(std::move(lightOff));
	remote.pressButton();

	return 0;
}