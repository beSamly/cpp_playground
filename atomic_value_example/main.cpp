#include <atomic>
#include <iostream>
#include <map>
#include <string>
using std::atomic;

atomic<bool> resetStateFlag(true);

void Process_DB2S_RESET_RES() {
  //메모리 초기화
  resetStateFlag.store(false);
}

bool TimerThreadWork() {
  bool expected = false;
  bool isOnProgress = resetStateFlag.compare_exchange_strong(expected, true);
  //선요청에 의해 먼저 초기화되고 있는 유저는 패스
  if (!isOnProgress) {
    // DBSystem->pushPakcet(...)
  }
  return true;
}

bool NeedToReset() {
  //일일미션 초기화 시간과 현재 시간을 비교
  return false;
}

void Process() {
  bool expected = false;

  //리셋이 필요하다면
  if (NeedToReset()) {
    //리셋 중이 아니라면 리셋 패킷 보내기
    bool isOnProgress = resetStateFlag.compare_exchange_strong(expected, true);
    if (!isOnProgress) {
      // DBSystem->pushPakcet(...)
    }
    //유저에게 현재는 이용할 수 없다는 메세지 표시
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