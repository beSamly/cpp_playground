#include <iostream>
#include <vector>
#include <ranges>
#include <functional>

using std::vector;
using std::function;

class People {
public:
	int id;
	People(int p_id) {
		id = p_id;
		std::cout << "People constructed with id " << id << std::endl;
	};

	People(const People& p) {
		std::cout << "People copied constructor with id " << p.id << std::endl;
	};
};

class Animal {
public:
	int id;
	Animal(int p_id) {
		id = p_id;
		std::cout << "Animal constructed with id " << id << std::endl;
	};

	Animal(const Animal& p) {
		std::cout << "Animal copied constructor with id " << p.id << std::endl;
	};
};


template <typename T, typename RT, typename LAM>
vector<RT> Mapping(const vector<T>& container, LAM transform) {

	vector<RT> returnVector;
	for (auto& elem : container) {
		auto p = transform(elem);
		returnVector.push_back(p);
	}

	std::cout << "before returning" << std::endl;
	return returnVector;
}

void filterUsingViews(vector<People>& pepVector) {
	pepVector | std::views::filter([](People& p) { return true; });
}

int main()
{
	std::cout << "Hello World!\n";

	vector<People> pepVector;
	for (int i = 0; i < 10; i++) {
		pepVector.push_back(People(i));
	}

	//filterUsingViews(pepVector);

	vector<Animal> animalVector = Mapping<People, Animal>(pepVector, [](People const& p) {
		return Animal(p.id);
	/*	auto a = Animal(p.id);
		return a;*/
		}
	);

	unsigned char year = 1993;
	unsigned char month = 'A';
	unsigned char day = 2;
	if (month == 31) {
		std::cout << "month is " << month << std::endl;
	}
}

