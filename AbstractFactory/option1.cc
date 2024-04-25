#include <iostream>
#include <memory>

class Knight {
 public:
  virtual std::string getName() = 0;
};

class Mage {
 public:
  virtual std::string getName() = 0;
};

class Archer {
 public:
  virtual std::string getName() = 0;
};

class IUnitFactory {
 public:
  virtual ~IUnitFactory() = default;
  virtual std::string getName() = 0;
  virtual std::unique_ptr<Knight> CreateKnight() = 0;
  virtual std::unique_ptr<Mage> CreatMage() = 0;
  virtual std::unique_ptr<Archer> CreateArcher() = 0;
};

class FireKnight : public Knight {
 public:
  std::string getName() override {
    return "Fire Knight";
  }
};

class IceKnight : public Knight {
 public:
  std::string getName() override {
    return "Ice Knight";
  }
};

class FireMage : public Mage {
 public:
  std::string getName() override {
    return "Fire Mage";
  }
};

class IceMage : public Mage {
 public:
  std::string getName() override {
    return "Ice Mage";
  }
};

class FireArcher : public Archer {
 public:
  std::string getName() override {
    return "Fire Archer";
  }
};

class IceArcher : public Archer {
 public:
  std::string getName() override {
    return "Ice Archer";
  }
};

class FireUnitFactory : public IUnitFactory {
 public:
  std::string getName() override {
    return "Fire Unit Factory";
  }
  std::unique_ptr<Knight> CreateKnight() override {
    return std::make_unique<FireKnight>();
  }
  std::unique_ptr<Mage> CreatMage() override {
    return std::make_unique<FireMage>();
  }
  std::unique_ptr<Archer> CreateArcher() override {
    return std::make_unique<FireArcher>();
  }
};

class IceUnitFactory : public IUnitFactory {
 public:
  std::string getName() override {
    return "Ice Unit Factory";
  }
  std::unique_ptr<Knight> CreateKnight() override {
    return std::make_unique<IceKnight>();
  }
  std::unique_ptr<Mage> CreatMage() override {
    return std::make_unique<IceMage>();
  }
  std::unique_ptr<Archer> CreateArcher() override {
    return std::make_unique<IceArcher>();
  }
};

class Game {
 public:
  void CreateUnit() {
    std::cout << "Unit Factory: " << factory_->getName() << std::endl;
    std::unique_ptr<Knight> knight(factory_->CreateKnight());
    std::cout << "Knight: " << knight->getName() << std::endl;
    std::unique_ptr<Mage> mage(factory_->CreatMage());
    std::cout << "Mage: " << mage->getName() << std::endl;
    std::unique_ptr<Archer> archer(factory_->CreateArcher());
    std::cout << "Archer: " << archer->getName() << std::endl;
  }

  void setFactory(std::unique_ptr<IUnitFactory>&& factory) {
    factory_ = std::move(factory);
  }

 private:
  std::unique_ptr<IUnitFactory> factory_;
};

int main() {
  Game game;
  game.setFactory(std::make_unique<FireUnitFactory>());
  game.CreateUnit();
  std::cout << std::endl;
  game.setFactory(std::make_unique<IceUnitFactory>());
  game.CreateUnit();
  return 0;
}