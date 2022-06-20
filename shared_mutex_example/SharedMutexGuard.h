#pragma once

#include <shared_mutex>
using std::shared_mutex;

class SharedMutexWriteLockGuard {
public:
	SharedMutexWriteLockGuard(shared_mutex& lock);
	~SharedMutexWriteLockGuard();

private:
	shared_mutex& _lock;
};

class SharedMutexReadLockGuard {
public:
	SharedMutexReadLockGuard(shared_mutex& lock);
	~SharedMutexReadLockGuard();

private:
	shared_mutex& _lock;
};