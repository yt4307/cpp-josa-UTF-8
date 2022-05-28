#include "josa.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

using std::string;

int main() {
	string str{ };
	cin >> str;
	// 은/는, 이/가, 을/를, 과/와, 아/야, 이여/여, 이랑/랑, 으로/로
	// 등의 조사를 두번째, 세번째 인자로 넣어서 조사를 원본 str 뒤에 붙여 반환해줍니다.
	cout << josa(str, "으로", "로") << endl;

	return 0;
}