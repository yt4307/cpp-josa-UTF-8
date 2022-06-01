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
	
	// 이런식으로 직접 josaProcess를 호출하여 조사를 붙여 줄 수도 있고,
	cout << josaProcess(str, "으로", "로") << endl;

	// 또는 이런식으로 간단하게 조사를 붙여 줄 수도 있습니다.
	cout << str + josa("를") << endl;

	// 아래와 같이 리터럴 접미사 j 또는 조를 붙여 간편하게 사용할 수도 있습니다.
	cout << str + "이 아닙니다."j << endl;
	cout << str + "아 이것 좀 도와줘"조 << endl;

	// C++ 23에서 추가 될 format 문법을 사용하면, 이런식으로도 사용할 수 있습니다.
	//cout << format("{}은 {}가 아닙니다."j, str, "직장인") << endl;

	return 0;
}
