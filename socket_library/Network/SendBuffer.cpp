#include "../Global.h"
#include "SendBuffer.h"

/*----------------
	SendBuffer
-----------------*/

SendBuffer::SendBuffer( BYTE* buffer, uint32 allocSize)
	: _buffer(buffer), _allocSize(allocSize)
{
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::Close(uint32 writeSize)
{
	ASSERT_CRASH(_allocSize >= writeSize);
	_writeSize = writeSize;
}

/*--------------------
	SendBufferChunk
--------------------*/
//
//SendBufferChunk::SendBufferChunk()
//{
//}
//
//SendBufferChunk::~SendBufferChunk()
//{
//}
//
//void SendBufferChunk::Reset()
//{
//	_open = false;
//	_usedSize = 0;
//}
//
//SendBufferRef SendBufferChunk::Open(uint32 allocSize)
//{
//	ASSERT_CRASH(allocSize <= SEND_BUFFER_CHUNK_SIZE);
//	ASSERT_CRASH(_open == false);
//
//	if (allocSize > FreeSize())
//		return nullptr;
//
//	_open = true;
//	return ObjectPool<SendBuffer>::make_shared(shared_from_this(), Buffer(), allocSize);
//}
//
//void SendBufferChunk::Close(uint32 writeSize)
//{
//	ASSERT_CRASH(_open == true);
//	_open = false;
//	_usedSize += writeSize;
//}
