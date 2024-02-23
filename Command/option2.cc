#include <iostream>
#include <stack>
class object {
 public:
  object() : x_(0), y_(0) {}
  void MoveTo(const int& x, const int& y) {
    x_ = x;
    y_ = y;
  }

  int getX() const { return x_; }
  int getY() const { return y_; }

 private:
  int x_;
  int y_;
};

class ICommand {
 public:
  virtual ~ICommand() {}
  virtual void execute() = 0;
  virtual void undo() = 0;
};

class MoveObjectCommand : public ICommand {
 public:
  MoveObjectCommand(object* obj, int x, int y) : obj_(obj), x_(x), y_(y), x_before_(obj->getX()), y_before_(obj->getY()) {}
  void execute() override {
    obj_->MoveTo(x_, y_);
  }

  void undo() override {
    obj_->MoveTo(x_before_, y_before_);
  }

 private:
  object* obj_;
  int x_;
  int y_;
  int x_before_;
  int y_before_;
};
void printObjectCoordinates(object& obj) {
  std::cout << "Object has coordinates: " << obj.getX() << ", " << obj.getY() << std::endl;
}

class InputHandler {
 public:
  ICommand* handleInput(const char& sym, object& obj) {
    switch (sym) {
    case 'd':
      return new MoveObjectCommand(&obj, obj.getX() + 1, obj.getY());
      break;
    case 'a':
      return new MoveObjectCommand(&obj, obj.getX() - 1, obj.getY());
      break;
    case 'w':
      return new MoveObjectCommand(&obj, obj.getX(), obj.getY() + 1);
      break;
    case 's':
      return new MoveObjectCommand(&obj, obj.getX(), obj.getY() - 1);
      break;
    default:
      break;
    }
    return nullptr;
  }
};

int main() {
  object obj;
  char sym;
  printObjectCoordinates(obj);
  InputHandler input_handler;
  std::stack<ICommand*> command_stack;

  while ((sym = getchar()) != 'q') {
    std::cin.get();
    if (sym == 'z' && command_stack.size() > 0) {
      ICommand* command = command_stack.top();
      command_stack.pop();
      command->undo();
      delete command;
    } else {
      ICommand* command = input_handler.handleInput(sym, obj);
      if (command) {
        command->execute();
        command_stack.push(command);
      }
    }
    printObjectCoordinates(obj);
  }

  while (command_stack.empty()) {
    ICommand* command = command_stack.top();
    command_stack.pop();
    delete command;
  }
  return 0;
}