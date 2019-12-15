#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class Task {
private:
  string title;
  int knowlege, health, energy, mood, food, money, time;

public:
  Task() {
    title = "NONE";
    knowlege = 0;
    health = 0;
    energy = 0;
    mood = 0;
    food = 0;
    money = 0;
    time = 0;
  };
  Task(string t, int k, int h, int e, int m, int f, int mon, int tm)
      : title(t), knowlege(k), health(h), energy(e), mood(m), food(f),
        money(mon), time(tm){};
  Task(const Task &t) {
    title = t.title;
    knowlege = t.knowlege;
    health = t.health;
    energy = t.energy;
    mood = t.mood;
    food = t.food;
    money = t.money;
    time = t.time;
  };
  string getTitle() { return title; };
  int getKnowlege() { return knowlege; };
  int getHealth() { return health; };
  int getEnergy() { return energy; };
  int getMood() { return mood; };
  int getFood() { return food; };
  int getMoney() { return money; };
  int getTime() { return time; };
  friend ostream &operator<<(ostream &out, Task t) {
    return out << t.getTitle() << '\n'
               << "Знания " << t.getKnowlege() << '\n'
               << "Health " << t.getHealth() << '\n'
               << "Energy " << t.getEnergy() << '\n'
               << "Mood " << t.getMood() << '\n'
               << "Food " << t.getFood() << '\n'
               << "Money " << t.getMoney() << '\n'
               << "Time spent " << t.getTime() << endl;
  };
};
class Event : public Task {
private:
  int probability;

public:
  Event() : Task(), probability(0){};
  Event(string t, int k, int h, int e, int m, int f, int mon, int p, int tm)
      : Task(t, k, h, e, m, f, mon, tm), probability(p){};
  int getProbability() { return probability; };
  Task getTask() {
    return Task(this->getTitle(), this->getKnowlege(), this->getHealth(),
                this->getEnergy(), this->getMood(), this->getFood(),
                this->getMoney(), this->getTime());
  };
  friend ostream &operator<<(ostream &out, Event e) {
    return out << e.getTitle() << '\n'
               << "Knowlege " << e.getKnowlege() << '\n'
               << "Health " << e.getHealth() << '\n'
               << "Energy " << e.getEnergy() << '\n'
               << "Mood " << e.getMood() << '\n'
               << "Food " << e.getFood() << '\n'
               << "Money " << e.getMoney() << '\n'
               << "Probability " << e.getProbability() << '\n'
               << "Time spent " << e.getTime() << endl;
  };
};
class Location {
private:
  vector<Task> posibilities;
  vector<Event> enter_events;
  vector<Event> exit_events;
  string title;

public:
  Location() {
    title = "NONE";
  };
  Location(string n, vector<Task> pos, vector<Event> enter,
           vector<Event> exit) {
    this->title = n;
    this->posibilities.clear();
    this->enter_events.clear();
    this->exit_events.clear();
    for (long unsigned int i = 0; i < pos.size(); i++) {
      this->posibilities.push_back(pos[i]);
    };
    for (long unsigned int i = 0; i < enter.size(); i++) {
      this->enter_events.push_back(enter[i]);
    };
    for (long unsigned int i = 0; i < exit.size(); i++) {
      this->exit_events.push_back(exit[i]);
    };
  };
  Location(const Location &l) {
    this->title = l.title;
    this->posibilities.clear();
    this->enter_events.clear();
    this->exit_events.clear();
    for (unsigned long int i = 0; i < l.posibilities.size(); i++) {
      this->posibilities.push_back(l.posibilities[i]);
    };
    for (unsigned long int i = 0; i < l.enter_events.size(); i++) {
      this->enter_events.push_back(l.enter_events[i]);
    }
    for (unsigned long int i = 0; i < l.exit_events.size(); i++) {
      this->exit_events.push_back(l.exit_events[i]);
    }
  };
  vector<Task> getPosibilities() { return posibilities; };
  vector<Event> getEnter() { return enter_events; };
  vector<Event> getExit() { return exit_events; };
  string getTitle() { return title; };
  friend ostream &operator<<(ostream &out, Location l) {
    out << l.getTitle() << endl;
    out << "Possiblilities " << endl;
    for (unsigned int i = 0; i < l.getPosibilities().size(); i++) {
      out << l.getPosibilities()[i] << endl;
    };
    out << "Events on enter " << endl;
    for (unsigned int i = 0; i < l.getEnter().size(); i++) {
      out << l.getEnter()[i] << endl;
    };
    out << "Events on exit " << endl;
    for (unsigned int i = 0; i < l.getExit().size(); i++) {
      out << l.getExit()[i] << endl;
    };
    return out;
  };

};
class Human {
private:
  int knowlege, health, mood, energy, food, money;
  int day;
  int hours, minutes;
  Location position;

public:
  Human() {
    knowlege = 0;
    health = 0;
    mood = 0;
    energy = 0;
    food = 0;
    money = 0;
    day = 0;
    hours = 0;
    minutes = 0;
    position = Location();
  }
  Human(int c_k, int c_h, int c_m, int c_e, int c_f, int c_mon, Location pos, int d, int h, int m) {
    knowlege = c_k;
    health = c_h;
    mood = c_m;
    energy = c_e;
    food = c_f;
    money = c_mon;
    position = pos;
    day = d;
    hours = h;
    minutes = m;
  };
  int getKnowlege() { return knowlege; };
  int getHealth() { return health; };
  int getMood() { return mood; };
  int getEnergy() { return energy; };
  int getFood() { return food; };
  int getMoney() { return money; };
  int getDay() { return day; };
  int getHours() { return hours; };
  int getMinutes() { return minutes; };
  Location getPosition() { return position; };
  void setPosition(Location pos){
    this->position=pos;
  };
  Human operator+(Task t1) {
    int new_knowlege = this->getKnowlege() + t1.getKnowlege();
    int new_health = this->getHealth() + t1.getHealth();
    if (new_health <= 0) {
      cout << "Вы настолько увлеклись учёбой, что абсолютно перестали следить "
              "за здоовьем, что в конце-концов очутились в больнице. Game over "
              ":-("
           << endl;
      exit(0);
    };
    if (new_health >= 100){new_health = 100;};
    int new_mood = this->getMood() + t1.getMood();
    if (new_mood <= 0) {
      cout << "Вы устали от этой жизни, и фраза suIASAde кажется вполне "
              "воплотимой"
           << endl;
      exit(0);
    };
    if (new_mood >= 100) {new_mood = 100; };
    int new_energy = this->getEnergy() + t1.getEnergy();
    if (new_energy <= 0) {
      cout
          << "Недосып дал о себе знать. Упав в обморок, вы очнулись уже в "
             "больнице, в которой проведёте долгий восстановительный период :-("
          << endl;
      exit(0);
    };
    if (new_energy >= 100) {new_energy = 100;};
    int new_food = this->getFood() + t1.getFood();
    if (new_food <= 0) {
      cout << "Кажется, кто-то слишком мало ел. Вас госпитализировали с сильным недовесом" << endl;
    };
    if (new_food >= 100) {new_food = 100;};
    int new_money = this->getMoney() + t1.getMoney();
    int new_minutes = this->getMinutes() + t1.getTime();
    int new_hours = this->getHours() + new_minutes / 60;
    new_minutes %= 60;
    int new_day = this->getDay() + new_hours / 24;
    if (new_day == this->getDay() + 1) {
      cout << 90 - new_day << " дней отсталось до сессии" << endl;
    };
    new_hours %= 24;
    if ((new_day == 90) && (new_hours >= 8)){
      cout << "СЕССИЯ НАЧАЛАСЬ" << endl;
      int r = rand() % 1000;
      if(r <= new_knowlege){
        cout << "ВЫ ВЫЖИЛИ" << endl;
      }
      else{
        cout << "Ваше существование не будет прежним после изгнания вас из ИПСА" << endl;
      };
      exit(0);
    }

    return Human(new_knowlege, new_health, new_mood, new_energy, new_food,
                 new_money, this->getPosition(), new_day, new_hours,
                 new_minutes);
  };
  Human operator+(Event e1){
    return (*this + e1.getTask());
  };
};

void game(Human hum, vector<Location> map) {
  int answer, banned;
  Human h = hum;
  srand(time(NULL));
  while (1 == 1) {
    cout << "Текущая локация:" << h.getPosition().getTitle() << endl;
    cout << "Знания - " << h.getKnowlege() << ", Здоровье - " << h.getHealth() << ", Настроение - " << h.getMood() << ", Енергия - " << h.getEnergy() << ", Еда - " << h.getFood() << ", Деньги - " << h.getMoney() << endl;
    cout << "День " << h.getDay() << ", " << h.getHours() << ":";
    if (h.getMinutes() == 0) {
      cout << "00" << endl;
    }
    else{
      cout << h.getMinutes() << endl;
    };
    for (unsigned short int i = 0; i < h.getPosition().getPosibilities().size(); i++) {
      cout << i + 1 << ". " << h.getPosition().getPosibilities()[i].getTitle()
           << '\n' << h.getPosition().getPosibilities()[i].getTime() << " минут" << endl;
    };
    cout << h.getPosition().getPosibilities().size() + 1
         << ". Перейти на другую локацию" << endl;
    cin >> answer;
    if ((answer <= h.getPosition().getPosibilities().size()) && (h.getPosition().getPosibilities().size() >= 0)) {
      h = h + h.getPosition().getPosibilities()[answer - 1];
    }
    else if (answer == h.getPosition().getPosibilities().size() + 1) {
      for (long unsigned int i = 0, f = 0; i < h.getPosition().getExit().size(); i++) {
        int r = rand() % 101 + 1;
        if ((h.getPosition().getExit()[i].getProbability() <= r) && (f == 0)) {
          cout << h.getPosition().getExit()[i].getTitle() << endl;
          f = 1;
        };
      };
      cout << "Выберите локацию для перехода: " << endl;

      for (long unsigned int i = 0; i < map.size(); i++){
        if (map[i].getTitle() != h.getPosition().getTitle()) {
          cout << i + 1 << ". " << map[i].getTitle() << endl;
        }
        else if(map[i].getTitle() == h.getPosition().getTitle()){
          banned = i;
        };
      };
      cin >> answer;
      if((answer >= 1) && (answer != banned) && (answer <= map.size())){
        Location new_ln = map[answer - 1];
        h.setPosition(new_ln);
        for (long unsigned int i = 0, f = 0; i < h.getPosition().getEnter().size(); i++) {
          int r = rand() % 101 + 1;
          if ((h.getPosition().getEnter()[i].getProbability() <= r) && (f == 0)) {
            cout << h.getPosition().getEnter()[i].getTitle() << endl;
            f = 1;
          };
        };
      };
    };
  };
};

int main() {
  string temp;
  vector<string> location;
  vector<Task> tasks;
  vector<Event> on_enter;
  vector<Event> on_exit;
  vector<string> temporary;
  vector<string> names;
  fstream f("locations.txt");
  vector<Location> map;
  while (getline(f, temp)) {
    location.push_back(temp);
  };
  f.close();
  for (long unsigned int i = 0; i < location.size(); i++) {
    fstream primary("source/" + location[i] + ".txt");
    while (getline(primary, temp)) {
      temporary.push_back(temp);
    }
    names.push_back(temporary[0]);
    for (long unsigned int j = 2; j < temporary.size(); j += 8) {
      int arr[7];
      for (int l = 0; l < 7; l++) {
        stringstream tss(temporary[j + l]);
        tss >> arr[l];
      }
      tasks.push_back(Task(temporary[j - 1], arr[0], arr[1], arr[2], arr[3],
                           arr[4], arr[5], arr[6]));
    };
    primary.close();
    fstream enter_file("source/" + location[i] + "_on_enter.txt");
    temporary.clear();
    while (getline(enter_file, temp)) {
      temporary.push_back(temp);
    };
    for (long unsigned int j = 0; j < temporary.size(); j += 9) {
      int arr[8];
      for (int l = 0; l < 8; l++) {
        stringstream tss(temporary[j + l + 1]);
        tss >> arr[l];
      };
      on_enter.push_back(Event(temporary[j], arr[0], arr[1], arr[2], arr[3],
                               arr[4], arr[5], arr[6], arr[7]));
    };
    enter_file.close();
    fstream exit_file("source/" + location[i] + "_on_exit.txt");
    temporary.clear();
    while (getline(exit_file, temp)) {
      temporary.push_back(temp);
    }
    for (long unsigned int j = 0; j < temporary.size(); j += 9) {
      int arr[8];
      for (int l = 0; l < 8; l++) {
        stringstream tss(temporary[j + l + 1]);
        tss >> arr[l];
      };
      on_exit.push_back(Event(temporary[j], arr[0], arr[1], arr[2], arr[3],
                              arr[4], arr[5], arr[6], arr[7]));
    };
    exit_file.close();
    temporary.clear();
    map.push_back(Location(names[i], tasks, on_enter, on_exit));
    tasks.clear();
    on_enter.clear();
    on_exit.clear();
  };
  Human h(0, 100, 100, 100, 100, 200, map[0], 0, 12, 0);

  game(h, map);
}
