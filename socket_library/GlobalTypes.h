#pragma once

#include <mutex>
#include <atomic>
#include <vector>
#include <iostream>
#include <deque>
#include <queue>
#include <utility>
#include <set>

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

template<typename T>
using Atomic = std::atomic<T>;
using Mutex = std::mutex;
using CondVar = std::condition_variable;
using UniqueLock = std::unique_lock<std::mutex>;
using LockGuard = std::lock_guard<std::mutex>;

// shared_ptr
using IocpCoreRef = std::shared_ptr<class IocpCore>;
using IocpObjectRef = std::shared_ptr<class IocpObject>;
using SessionRef = std::shared_ptr<class Session>;
using ClientSessionRef = std::shared_ptr<class ClientSession>;
using BaseSocketServerRef = std::shared_ptr<class BaseSocketServer>;
using SocketServerRef = std::shared_ptr<class SocketServer>;
using ClientServiceRef = std::shared_ptr<class ClientService>;
using SendBufferRef = std::shared_ptr<class SendBuffer>;
using SendBufferChunkRef = std::shared_ptr<class SendBufferChunk>;

#define size16(val)		static_cast<int16>(sizeof(val))
#define size32(val)		static_cast<int32>(sizeof(val))
#define len16(arr)		static_cast<int16>(sizeof(arr)/sizeof(arr[0]))
#define len32(arr)		static_cast<int32>(sizeof(arr)/sizeof(arr[0]))

using std::enable_shared_from_this;
using std::cout;
using std::endl;
using std::weak_ptr;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;
using std::thread;
using std::wstring;
using std::make_shared;
using std::this_thread::sleep_for;

template<typename type, typename... Args>
std::shared_ptr<type> MakeShared(Args&&... args)
{
	//return std::shared_ptr<type>{ new<type>(forward<args>(args)...), xdelete<type> };
	//return std::shared_ptr<type>(std::forward<args>(args)...);
	return std::make_shared<type>(std::forward<Args>(args)...);
}



//Container
template<typename Type>
using Vector = std::vector<Type>;

template<typename Type, typename Container = std::deque<Type>>
using Queue = std::queue<Type, Container>;

template<typename Key, typename Pred = std::less<Key>>
using Set = std::set<Key, Pred>;
