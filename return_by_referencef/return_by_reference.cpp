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
���� ����
Wallet w1 = GetWallet() ��� GetWallet()�� ���� ���� w1�� �Ҵ��ϳ� GetWallet()��
ȣ���ϳ� �����ϰ� copy constructor ȣ��ȴ�. �� �����ϴ� ������ ���纻��
���ϵȴ�.

Wallet GetWallet()�Լ��� Wallet ������ ��ü�� �����ؼ� �����Ѵ�.
Wallet& GetWallet()�Լ��� ���纻�� �ƴ� ��ü ��ü�� �����Ѵ�. ������ �Լ���
ȣ���ϴ� �κп��� Wallet w1 = GetWallet()�� �Ͽ� w1 ������ ���縦 �Ѵٸ� w1��
Person ��ü ������ Wallet ��ü�� �ƴϰԵȴ�.
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
    wallet.balance = 15;  // Person ��ü�� Wallet �ɹ� ��ü�� ���� ����
    p1.PrintBalance();  // 15�� ����Ʈ �Ѵ�.
  }
  cout << "================Test1 End=================" << endl;

  // Test 2
  cout << "================Test2 Start===============" << endl;
  {
    Person p1;
    Wallet wallet = p1.GetWalletAsRef();  // copy constructor called
    wallet.balance = 15;  // ����� Wallet ��ü�� �ɹ� ���� ����
    p1.PrintBalance();    // 0�� ����Ʈ �Ѵ�.
  }
  cout << "================Test2 End=================" << endl;

  // Test 3
  cout << "================Test3 Start===============" << endl;
  {
    Person p1;
    Wallet wallet = p1.GetWalletAsValue();  // copy constructor called
    wallet.balance = 15;  // ����� Wallet ��ü�� �ɹ� ���� ����
    p1.PrintBalance();    // 0�� ����Ʈ �Ѵ�.
  }
  cout << "================Test3 End=================" << endl;

  // Test 4 �̰� ���ʿ� �Ұ���
  cout << "================Test4 Start===============" << endl;
  {
    Person p1;
    const Wallet& wallet = p1.GetWalletAsValue();  // copy constructor called
    //wallet.SetBalance(15);  // ����� Wallet ��ü�� �ɹ� ���� ����
    p1.PrintBalance();    // 0�� ����Ʈ �Ѵ�.
  }
  cout << "================Test4 End=================" << endl;

  return 0;
}