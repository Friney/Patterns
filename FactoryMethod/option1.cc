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
  enum ETerrain {
    city,
    off_road
  };

  Car* createCar(ETerrain terrain) {
    if (terrain == city) {
      return new Porsche;
    }
    if (terrain == off_road) {
      return new Jeep;
    }
    return nullptr;
  }
};

int main() {
  FactoryCar factory;
  std::unique_ptr<Car> car_in_city(factory.createCar(FactoryCar::city));
  car_in_city->outInfo();
  std::unique_ptr<Car> car_in_off_road(factory.createCar(FactoryCar::off_road));
  car_in_off_road->outInfo();
  return 0;
}