#include "Logger.h"
#include <Windows.h>
#include <string>
#include <iostream>

using std::string;

Logger::Logger()
{
	stdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	stdErr = ::GetStdHandle(STD_ERROR_HANDLE);
}

Logger::~Logger()
{

}

void Logger::Error(const string str, ...)
{
	Log(Color::RED, true, str, "[ERROR]");
}

void Logger::Debug(const string str, ...)
{
	Log(Color::BLUE, false, str, "[INFO]");
}

void Logger::Warn(const string str, ...)
{
	Log(Color::GREEN, false, str, "[WARN]");
}

void Logger::Info(const string str, ...)
{
	Log(Color::YELLOW, false, str, "[INFO]");
}

void Logger::SetColor(Color color, bool isStdOut)
{
	static WORD SColors[]
	{
		0,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		FOREGROUND_RED | FOREGROUND_INTENSITY,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
	};

	::SetConsoleTextAttribute(isStdOut ? stdOut : stdErr, SColors[static_cast<__int32>(color)]);
}

void Logger::Log(Color color, bool isStdOut, const string str, string prefix)
{
	Logger::SetColor(color, isStdOut);

	std::wstring widestr = std::wstring(str.begin(), str.end());
	const wchar_t* widecstr = widestr.c_str();

	std::wstring prefixWstring = std::wstring(prefix.begin(), prefix.end());
	const wchar_t* prefixWchar = prefixWstring.c_str();

	std::wcout << prefixWchar << L" " << widecstr << std::endl;
}
