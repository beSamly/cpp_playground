#pragma once

/*-------------------------
|		  ∏≈≈©∑Œ		      |
--------------------------*/
#define USE_MUL_LOCK(count) std::shared_mutex _locks[count];
#define USE_LOCK USE_MUL_LOCK(1)


#define	READ_LOCK_IDX(idx)		SharedMutexReadLockGuard readLockGuard_##idx(_locks[idx]);
#define	WRITE_LOCK_IDX(idx)		SharedMutexWriteLockGuard writeLockGuard_##idx(_locks[idx]);

#define WRITE_LOCK WRITE_LOCK_IDX(0)
#define READ_LOCK READ_LOCK_IDX(0)
