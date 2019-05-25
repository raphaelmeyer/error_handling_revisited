enum class Homing {
  NegativeLimit
};

enum class Position {
  Park
};

class Motor {
  public:
    void power_on() {}
    void power_off() {}
    void home(Homing) {}
    void move(Position) {}
};

class Table {
  public:
    void home() {
      y_axis.power_off();
      x_axis.power_on();
      x_axis.home(Homing::NegativeLimit);
      x_axis.move(Position::Park);
      y_axis.power_on();
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

