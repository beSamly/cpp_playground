#include <atomic>
#include <iostream>
#include <map>
#include <string>
using std::atomic;

atomic<bool> resetStateFlag(true);

void Process_DB2S_RESET_RES() {
  //�޸� �ʱ�ȭ
  resetStateFlag.store(false);
}

bool TimerThreadWork() {
  bool expected = false;
  bool isOnProgress = resetStateFlag.compare_exchange_strong(expected, true);
  //����û�� ���� ���� �ʱ�ȭ�ǰ� �ִ� ������ �н�
  if (!isOnProgress) {
    // DBSystem->pushPakcet(...)
  }
  return true;
}

bool NeedToReset() {
  //���Ϲ̼� �ʱ�ȭ �ð��� ���� �ð��� ��
  return false;
}

void Process() {
  bool expected = false;

  //������ �ʿ��ϴٸ�
  if (NeedToReset()) {
    //���� ���� �ƴ϶�� ���� ��Ŷ ������
    bool isOnProgress = resetStateFlag.compare_exchange_strong(expected, true);
    if (!isOnProgress) {
      // DBSystem->pushPakcet(...)
    }
    //�������� ����� �̿��� �� ���ٴ� �޼��� ǥ��
    // pUser->SendPacket(...)
  }
}

int main() {
  // bool expected = false;
  // bool currentState = isOnProgress.compare_exchange_strong(expected, true);

  bool expected = false;
  bool isOnProgress = resetStateFlag.compare_exchange_strong(expected, true);

  std::map<int, std::string> test_map;
  test_map.insert(std::make_pair(1, std::string("first element")));
  test_map.insert(std::make_pair(6, std::string("sixth element")));
  test_map.insert(std::make_pair(2, std::string("second element")));
  test_map.insert(std::make_pair(4, std::string("fourth element")));
  test_map.insert(std::make_pair(3, std::string("third element")));
  std::map<int, std::string>::iterator a = test_map.begin();

  a++;
  std::cout << "value after a ++" << a->second << std::endl;

  std::cout << "isOnProgress is " << isOnProgress << std::endl;

  return 1;
}