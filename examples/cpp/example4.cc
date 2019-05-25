#include <stdexcept>

enum class Homing { NegativeLimit };

enum class Position { Park };

class MotorError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};
class HomingError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

class Motor {
public:
  void home(Homing) {
  }
  void move(Position) {
  }
};

class Table {
public:
  void home() {
    try {
      tool.home(Homing::NegativeLimit);
      tool.move(Position::Park);
      x_axis.home(Homing::NegativeLimit);
      x_axis.move(Position::Park);
      y_axis.home(Homing::NegativeLimit);
      y_axis.move(Position::Park);
    } catch(MotorError const & e) {
      throw HomingError{"..."};
    }
  }

private:
  Motor tool;
  Motor x_axis;
  Motor y_axis;
};

int main() {
  Table table;
  table.home();
}
