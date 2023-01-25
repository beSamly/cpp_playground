#include <iostream>

using std::cout;
using std::endl;

class Wallet {
 public:
  Wallet() { cout << "Wallet class constructor" << endl; }
  Wallet(const Wallet& p) { cout << "Wallet class copy constructor" << endl; }
  int balance = 0;
  void SetBalance(int value) { balance = value; }
};

/*
요점 정리
Wallet w1 = GetWallet() 경우 GetWallet()의 리턴 값을 w1에 할당하나 GetWallet()만
호출하나 동일하게 copy constructor 호출된다. 즉 리턴하는 시점에 복사본이
리턴된다.

Wallet GetWallet()함수는 Wallet 무조건 객체를 복사해서 리턴한다.
Wallet& GetWallet()함수는 본사본이 아닌 객체 자체를 리턴한다. 하지만 함수를
호출하는 부분에서 Wallet w1 = GetWallet()을 하여 w1 변수에 복사를 한다면 w1은
Person 객체 내부의 Wallet 객체가 아니게된다.
*/
class Person {
 public:
  Person() { cout << "Person class constructor" << endl; }
  Person(const Person& p) { cout << "Person class copy constructor" << endl; }

 private:
  Wallet wallet;

 public:
  Wallet GetWalletAsValue() { return wallet; }
  Wallet& GetWalletAsRef() { return wallet; }
  void PrintBalance() {
    cout << "[PrintBalance] Balance is " << wallet.balance << endl;
  }
};

int main() {
  // Test 1
  cout << "================Test1 Start===============" << endl;
  {
    Person p1;
    Wallet& wallet = p1.GetWalletAsRef();  // copy constructor not called
    wallet.balance = 15;  // Person 객체의 Wallet 맴버 객체의 값을 수정
    p1.PrintBalance();  // 15를 프린트 한다.
  }
  cout << "================Test1 End=================" << endl;

  // Test 2
  cout << "================Test2 Start===============" << endl;
  {
    Person p1;
    Wallet wallet = p1.GetWalletAsRef();  // copy constructor called
    wallet.balance = 15;  // 복사된 Wallet 객체의 맴버 변수 수정
    p1.PrintBalance();    // 0을 프린트 한다.
  }
  cout << "================Test2 End=================" << endl;

  // Test 3
  cout << "================Test3 Start===============" << endl;
  {
    Person p1;
    Wallet wallet = p1.GetWalletAsValue();  // copy constructor called
    wallet.balance = 15;  // 복사된 Wallet 객체의 맴버 변수 수정
    p1.PrintBalance();    // 0을 프린트 한다.
  }
  cout << "================Test3 End=================" << endl;

  // Test 4 이건 애초에 불가능
  cout << "================Test4 Start===============" << endl;
  {
    Person p1;
    const Wallet& wallet = p1.GetWalletAsValue();  // copy constructor called
    //wallet.SetBalance(15);  // 복사된 Wallet 객체의 맴버 변수 수정
    p1.PrintBalance();    // 0을 프린트 한다.
  }
  cout << "================Test4 End=================" << endl;

  return 0;
}