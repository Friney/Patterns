#include <iostream>

class Location {
 public:
  void outInfo() {
    std::cout << "Location info:" << std::endl;
    std::cout << "Tree_count = " << tree_count_ << std::endl;
    std::cout << "Mountains count = " << mountains_count_ << std::endl;
    std::cout << "Percentage of easy enemies = " << percentage_of_easy_enemies_ << std::endl;
    std::cout << "Percentage of Normal enemies = " << percentage_of_Normal_enemies_ << std::endl;
    std::cout << "Percentage of hard enemies = " << percentage_of_hard_enemies_ << std::endl;
  }

  void setTreeCount(std::size_t tree_count) {
    tree_count_ = tree_count;
  }

  void setMountainsCount(std::size_t mountains_count) {
    mountains_count_ = mountains_count;
  }

  void setPercentageOfEasyEnemies(std::size_t percentage_of_easy_enemies) {
    percentage_of_easy_enemies_ = percentage_of_easy_enemies;
  }

  void setPercentageOfNormalEnemies(std::size_t percentage_of_Normal_enemies) {
    percentage_of_Normal_enemies_ = percentage_of_Normal_enemies;
  }

  void setPercentageOfHardEnemies(std::size_t percentage_of_hard_enemies) {
    percentage_of_hard_enemies_ = percentage_of_hard_enemies;
  }

 private:
  std::size_t tree_count_;
  std::size_t mountains_count_;
  std::size_t percentage_of_easy_enemies_;
  std::size_t percentage_of_Normal_enemies_;
  std::size_t percentage_of_hard_enemies_;
};

class Park : public Location {
 public:
  Park() {
    setPercentageOfEasyEnemies(0);
    setPercentageOfNormalEnemies(0);
    setPercentageOfHardEnemies(0);
    setTreeCount(33);
    setMountainsCount(5);
  }
};

class FactoryLvl  {
  public:
  virtual ~FactoryLvl(){};
  virtual void create(Location& location) = 0;
};

class FactoryEaseLvl : public FactoryLvl {
 public:
  void create(Location& location) override {
    location.setPercentageOfEasyEnemies(60);
    location.setPercentageOfNormalEnemies(30);
    location.setPercentageOfHardEnemies(10);
  }
};

class FactoryNormalLvl : public FactoryLvl {
 public:
  void create(Location& location) override {
    location.setPercentageOfEasyEnemies(30);
    location.setPercentageOfNormalEnemies(50);
    location.setPercentageOfHardEnemies(20);
  }
};

class FactoryHardLvl : public FactoryLvl {
 public:
  void create(Location& location) override {
    location.setPercentageOfEasyEnemies(15);
    location.setPercentageOfNormalEnemies(25);
    location.setPercentageOfHardEnemies(60);
  }
};

int main() {
  FactoryLvl* factory_lvls[3] = {new FactoryEaseLvl(), new FactoryNormalLvl(), new FactoryHardLvl()};
  enum ELvl { EASY = 0, NORMAL = 1, HARD = 2 };
  Location location = Park();
  std::cout << "Park without difficulty" << std::endl;
  location.outInfo();
  std::cout << std::endl;
  factory_lvls[ELvl::EASY]->create(location);
  std::cout << "Easy level" << std::endl;
  location.outInfo();
  std::cout << std::endl;
  factory_lvls[ELvl::NORMAL]->create(location);
  std::cout << "Normal level" << std::endl;
  location.outInfo();
  std::cout << std::endl;
  factory_lvls[ELvl::HARD]->create(location);
  std::cout << "Hard level" << std::endl;
  location.outInfo();
  return 0;
}