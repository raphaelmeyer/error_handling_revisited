enum class Homing { NegativeLimit };

enum class Position { Park };

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
    x_axis.home(Homing::NegativeLimit);
    x_axis.move(Position::Park);
    y_axis.home(Homing::NegativeLimit);
    y_axis.move(Position::Park);
  }

private:
  Motor x_axis;
  Motor y_axis;
};

int main() {
  Table table;
  table.home();
}
