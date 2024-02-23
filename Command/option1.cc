#include <iostream>
#include <stack>
class object {
 public:
  object() : x_(0), y_(0) {}
  void moveRight() {
    ++x_;
  }
  void moveLeft() {
    --x_;
  }
  void moveUp() {
    ++y_;
  }
  void modeDown() {
    --y_;
  }

  int getX() {
    return x_;
  }

  int getY() {
    return y_;
  }

 private:
  int x_, y_;
};

class ICommand {
 public:
  virtual ~ICommand() {}
  virtual void execute(object& obj) = 0;
};

class MoveRightCommand : public ICommand {
 public:
  void execute(object& obj) override {
    obj.moveRight();
  }
};

class MoveLeftCommand : public ICommand {
 public:
  void execute(object& obj) override {
    obj.moveLeft();
  }
};

class MoveUpCommand : public ICommand {
 public:
  void execute(object& obj) override {
    obj.moveUp();
  }
};

class MoveDownCommand : public ICommand {
 public:
  void execute(object& obj) override {
    obj.modeDown();
  }
};

void printObjectCoordinates(object& obj) {
  std::cout << "Object has coordinates: " << obj.getX() << ", " << obj.getY() << std::endl;
}

class InputHandler {
 public:
  ~InputHandler() {
    delete button_d_;
    delete button_a_;
    delete button_s_;
    delete button_w_;
  }
  ICommand* handleInput(const char& sym) {
    switch (sym) {
    case 'd':
      return button_d_;
      break;
    case 'a':
      return button_a_;
      break;
    case 'w':
      return button_w_;
      break;
    case 's':
      return button_s_;
      break;
    default:
      break;
    }
    return nullptr;
  }

  void setButton_d_(ICommand* button_d) {
    button_d_ = button_d;
  }

  void setButton_a_(ICommand* button_a) {
    button_a_ = button_a;
  }

  void setButton_w_(ICommand* button_w) {
    button_w_ = button_w;
  }

  void setButton_s_(ICommand* button_s) {
    button_s_ = button_s;
  }

 private:
  ICommand* button_d_;
  ICommand* button_a_;
  ICommand* button_w_;
  ICommand* button_s_;
};

int main() {
  object obj;
  char sym;
  printObjectCoordinates(obj);
  std::stack<ICommand*> command_stack;
  InputHandler input_handler;
  input_handler.setButton_a_(new MoveLeftCommand());
  input_handler.setButton_d_(new MoveRightCommand());
  input_handler.setButton_s_(new MoveDownCommand());
  input_handler.setButton_w_(new MoveUpCommand());
  while ((sym = getchar()) != 'e') {
    std::cin.get();
    ICommand* command = input_handler.handleInput(sym);
    if (command) {
      command->execute(obj);
      command_stack.push(command);
    }
    printObjectCoordinates(obj);
  }
  return 0;
}