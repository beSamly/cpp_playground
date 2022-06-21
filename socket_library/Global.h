#pragma once
#include <iostream>
#include <memory>

#include "GlobalMacro.h"
#include "GlobalTypes.h"

/* ws2_32 라이브러리 직접 연결해줘야한다.*/
#pragma comment(lib, "ws2_32.lib")

/* windows 를 winsock2 뒤에 include 해야지 winsock2 에러가 안 난다.*/
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <windows.h>


