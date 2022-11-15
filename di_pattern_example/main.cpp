#include "main.h"

#include <iostream>

template <class T>
using sptr = std::shared_ptr<T>;

class IAnimal {
 public:
  // void virtual eat() { std::cout << "IAnimal : eat() fuction" << std::endl;
  // };

  virtual ~IAnimal(){};
  void virtual eat() abstract = 0;
};

class Human : public IAnimal {
 public:
  void test() { std::cout << "test() fuction" << std::endl; }

  virtual void eat() override {
    std::cout << "HumanClass : eat() fuction" << std::endl;
  }

  virtual ~Human() { std::cout << "Human deconstructor" << std::endl; };
};

class MockHuman : public IAnimal {
 public:
  virtual void eat() override {
    std::cout << "MockClass : eat() fuction" << std::endl;
  }
  virtual ~MockHuman() { std::cout << "MockHuman deconstructor" << std::endl; };
};

class Controller {
 public:
  sptr<IAnimal> animal;

 public:
  // Controller() = delete;
  Controller(sptr<IAnimal> p_animal) { animal = p_animal; }

  void doEat() { animal->eat(); }
};

int main() {
  Controller* c1;
  // sptr<IAnimal> asdf = std::make_shared<Human>(); // this is an error
  {
    sptr<Human> actualInstace = std::make_shared<Human>();
    sptr<MockHuman> mockInstance = std::make_shared<MockHuman>();
    // sptr<IAnimal> va = std::dynamic_pointer_cast<IAnimal>(actualInstace);

    // implicit casting 이 일어나 sptr<Human>의 ref count + 1 된다.
    c1 = new Controller(actualInstace);
    c1->doEat();
  }
  std::cout << "after block end" << std::endl;

  delete c1;
  std::cout << "the end" << std::endl;
  return 0;
}