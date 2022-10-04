#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::wcout;
using std::string;

typedef wchar_t CustomType;
using SecondCustomType = wchar_t;

struct DBInfo {
	string Name;
	string Id;
};

class DBInfoWrapper {
private:
	DBInfo dbinfoArr[3];
};

enum LOG_TYPE {
	FIRST = 0X01,
	SECOND = 0X02,
};

void c_style_func_test() {
	wchar_t wchar[] = L"Hello world";
	wprintf_s(wchar);

	cout << "Bit operation test : " << FIRST << " " << SECOND << " " << (FIRST | SECOND) << endl;

	DBInfo adf[3];
}

void built_in_func_test(...) {
	cout << "Function name : " << __FUNCTION__ << " File Name : " << __FILE__ << " Line : " << __LINE__ << " ARGS : " << endl;
}

void ifstream_test() {

}

void test_string_func() {
	string test_str("//asdf//brwef");
	size_t rfind_pos = test_str.rfind("//");
	size_t find_pos = test_str.find("//");
	cout << "after rfind : " << test_str << endl;
	cout << "rfind_pos : " << rfind_pos << endl;
	cout << "find_pos : " << find_pos << endl;

	string anoter = test_str.substr(0, 3) + "//substr_test";
	cout << "anoter : " << anoter << endl;

	const char* char_ptr = test_str.c_str();

}

void test_wchar_t() {
	std::cout << "hello world" << std::endl;
	char first_char('A');
	wchar_t first_wchar('A');
	CustomType first_custom_type('B');
	SecondCustomType second_custom_type('C');
	cout << "cout char : " << first_char << endl;
	cout << "cout wchar_t : " << first_wchar << endl;
	wcout << "wcout wchar_t : " << first_wchar << endl;
	wcout << "wcout CustomType : " << first_custom_type << endl;
	wcout << "wcout SecondCustomType : " << second_custom_type << endl;
	test_string_func();
	built_in_func_test();
}

int main() {
	test_wchar_t();
	ifstream_test();
	c_style_func_test();
	return 1;
}