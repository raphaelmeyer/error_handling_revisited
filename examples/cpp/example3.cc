enum class Homing { NegativeLimit };

enum class Position { Park };

class Motor {
public:
  bool home(Homing) {
    return true;
  }
  bool move(Position) {
    return true;
  }
};

class Table {
public:
  bool home() {
    if(not x_axis.home(Homing::NegativeLimit)) {
      return false;
    }
    if(not x_axis.move(Position::Park)) {
      return false;
    }
    if(not y_axis.home(Homing::NegativeLimit)) {
      return false;
    }
    if(not y_axis.move(Position::Park)) {
      return false;
    }
    return true;
  }

private:
  Motor x_axis;
  Motor y_axis;
};

int main() {
  Table table;
  table.home();
}
