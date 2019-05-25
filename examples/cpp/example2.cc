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
    if(x_axis.home(Homing::NegativeLimit)) {
      if(x_axis.move(Position::Park)) {
        if(y_axis.home(Homing::NegativeLimit)) {
          if(y_axis.move(Position::Park)) {
            return true;
          }
        }
      }
    }
    return false;
  }

private:
  Motor x_axis;
  Motor y_axis;
};

int main() {
  Table table;
  table.home();
}
