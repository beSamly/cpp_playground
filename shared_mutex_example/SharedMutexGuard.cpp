#include "SharedMutexGuard.h"

/*	write lock guard  */
SharedMutexWriteLockGuard::SharedMutexWriteLockGuard(shared_mutex& lock) : _lock(lock) {
	_lock.lock();
}

SharedMutexWriteLockGuard::~SharedMutexWriteLockGuard()
{
	_lock.unlock();
}

/*	read lock guard   */
SharedMutexReadLockGuard::SharedMutexReadLockGuard(shared_mutex& lock) : _lock(lock) {
	_lock.lock_shared();
}

SharedMutexReadLockGuard::~SharedMutexReadLockGuard()
{
	_lock.unlock_shared();
}
