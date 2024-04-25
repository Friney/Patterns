#include <iostream>
#include <memory>

// Базовый класс абстрактной фабрики не абстрактный, его можно вызвать и создать лабиринт, который в данном случае является "базовым"

class Maze {
 public:
  virtual std::string getName() {
    return "Maze";
  }
};

class Room {
 public:
  virtual std::string getName() {
    return "Room";
  }
};

class Door {
 public:
  virtual std::string getName() {
    return "Door";
  }
};

class MazeFactory {
 public:
  virtual ~MazeFactory() = default;
  virtual std::string getName() {
    return "Maze Factory";
  }

  virtual std::unique_ptr<Maze> CreateMaze() {
    return std::make_unique<Maze>();
  }

  virtual std::unique_ptr<Room> CreateRoom() {
    return std::make_unique<Room>();
  }

  virtual std::unique_ptr<Door> CreateDoor() {
    return std::make_unique<Door>();
  }
};

class GlassMaze : public Maze {
 public:
  std::string getName() override {
    return "Glass Maze";
  }
};

class BombedRoom : public Room {
 public:
  std::string getName() override {
    return "Bombed Room";
  }
};

class GlassRoom : public Room {
 public:
  std::string getName() override {
    return "Glass Room";
  }
};

class GlassDoor : public Door {
 public:
  std::string getName() override {
    return "Glass Door";
  }
};

class BomdedMazeFactory : public MazeFactory {
 public:
  std::string getName() override {
    return "Bomded Maze Factory";
  }
  std::unique_ptr<Room> CreateRoom() override {
    return std::unique_ptr<Room>(std::make_unique<BombedRoom>());
  }
};

class GlassMazeFactory : public MazeFactory {
 public:
  std::string getName() override {
    return "Glass Maze Factory";
  }
  std::unique_ptr<Maze> CreateMaze() override {
    return std::make_unique<GlassMaze>();
  }
  std::unique_ptr<Room> CreateRoom() override {
    return std::make_unique<GlassRoom>();
  }
  std::unique_ptr<Door> CreateDoor() override {
    return std::make_unique<GlassDoor>();
  }
};

class MazeGame {
 public:
  void CreateGame() {
    std::cout << "Maze Factory: " << factory_->getName() << std::endl;
    std::unique_ptr<Maze> maze = factory_->CreateMaze();
    std::cout << "Maze: " << maze->getName() << std::endl;
    std::unique_ptr<Room> room = factory_->CreateRoom();
    std::cout << "Room: " << room->getName() << std::endl;
    std::unique_ptr<Door> door = factory_->CreateDoor();
    std::cout << "Door: " << door->getName() << std::endl;
  }
  void setFactory(std::unique_ptr<MazeFactory>&& factory) {
    factory_ = std::move(factory);
  }

 private:
  std::unique_ptr<MazeFactory> factory_;
};

int main() {
  MazeGame maze_game;
  maze_game.setFactory(std::make_unique<MazeFactory>());
  maze_game.CreateGame();
  std::cout << std::endl;
  maze_game.setFactory(std::make_unique<BomdedMazeFactory>());
  maze_game.CreateGame();
  std::cout << std::endl;
  maze_game.setFactory(std::make_unique<GlassMazeFactory>());
  maze_game.CreateGame();
  return 0;
}