#include <iostream>
#include <memory>

class Car {
 public:
  virtual ~Car(){};
  virtual void outInfo() = 0;
};

class Jeep : public Car {
 public:
  void outInfo() override {
    std::cout << "Jeep" << std::endl;
  }
};

class Porsche : public Car {
 public:
  void outInfo() override {
    std::cout << "Porsche" << std::endl;
  }
};

class FactoryCar {
 public:
  virtual ~FactoryCar(){};
  virtual Car* create() = 0;
};

class FactoryPorsche : public FactoryCar {
 public:
  Car* create() override {
    return new Porsche();
  }
};

class FactoryJeep : public FactoryCar {
 public:
  Car* create() override {
    return new Jeep();
  }
};

int main() {
  // Если нужно чтобы код работал не для Porsche, а для Jeep, нужно изменить только фабрику
  FactoryPorsche factory;
  std::unique_ptr<Car> car(factory.create());
  car->outInfo();
  
  std::unique_ptr<Car> car2(factory.create());
  car2->outInfo();
  return 0;
}