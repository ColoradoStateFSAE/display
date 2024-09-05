#include <functional>
#include <limits>

class MenuItem {
  public:
    const int id, fast;
	std::function<void()> action;
	const int min, max;
    MenuItem* previous;
	MenuItem* next;
	
	int value = 0;
	bool selected = false;

    MenuItem(int id, int fast, std::function<void()> action, int min = 0, int max = std::numeric_limits<int>::max()) :
		id(id), fast(fast), action(action), min(min), max(max), previous(nullptr), next(nullptr) {

    }

	MenuItem heading();
	bool isHeading();
	void change(int amount) {
		if(amount > 1) {
			value += fast;
		} else if(amount < -1) {
			value -= fast;
		} else {
			value += amount;
		}

		if(value < min) value = min;
		if(value > max) value = max;
	}

  private:
	bool _heading = false;
};
