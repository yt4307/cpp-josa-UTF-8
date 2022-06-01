#pragma once
// 스트링 리터럴 접미사에 _ 안붙었다는 경고 해제
#pragma warning( disable : 4455 )

#ifdef _MSC_VER
// CW2A 및 CA2W를 쓰기 위한 헤더
#include <atlstr.h>
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <exception>

using std::string;

using std::vector;

using std::for_each;

using std::pair;

vector<pair<string, string>> josaList{
	{ "은", "는" },
	{ "이", "가" },
	{ "을", "를" },
	{ "과", "와" },
	{ "아", "야" },
	{ "이여", "여" },
	{ "이랑", "랑" },
	{ "으로", "로" }
};

pair<string, string> josa(string str) {
	// 다른 글자를 조사로 착각하지 않도록 0번 인덱스부터 첫번째 " " 범위 까지 탐색
	str = str.substr(0, str.find(" "));

	for (const auto& josa : josaList)
		if ((str.find(josa.first) != string::npos) or (str.find(josa.second) != string::npos))
			return josa;

	return { };
}


// 은/는, 이/가, 을/를, 과/와, 아/야, 이여/여, 이랑/랑, 으로/로
// 받침이 있으면 앞쪽, 받침이 없으면 뒤쪽
// 단, 으로/로는 ㄹ받침일때도 으로가 아닌 로 사용
string josaProcess(string str, string firstPostposition, string secondPostposition) {
	string sourceString{ str };

	// 비주얼 스튜디오에서 컴파일한다면 십중팔구 CP_949를 쓸테니 이를 UTF-8로 변환해준다.
#ifdef _MSC_VER
	auto toUTF8{ [](string& multibyte_string) {
		multibyte_string = string{ CW2A{ CA2W{ multibyte_string.c_str() }, CP_UTF8 } };
	} };
	toUTF8(str);
#endif

	// 한글 UTF-8 인코딩 규칙: 1110xxxx 10xxxxxx 10xxxxxx
	// 이것(1110 0000 1000 0000 1000 0000)을 16진수로 바꾸면 E0 8080

	// UTF-8 -> UNICODE
	// 위의 한글 UTF-8 인코딩 규칙에 따라 한글은 3바이트를 차지하게 된다.
	// 따라서 각각의 바이트를 저장할 변수들을 선언한다.
	char firstPart{ };
	char secondPart{ };
	char thirdPart{ };

	// 범위 검사를 위해 try-catch문 사용
	try {
		firstPart = (str.at(str.length() - 3) ^ 0xE0); // 끝의 4비트가 유효한 비트
		secondPart = (str.at(str.length() - 2) ^ 0x80); // 끝의 6비트가 유효한 비트
		thirdPart = (str.at(str.length() - 1) ^ 0x80); // 끝의 6비트가 유효한 비트
	}
	catch (std::exception err) {
		return sourceString;
	}

	// 부호 없는 2바이트 변수를 0으로 초기화 후 비트를 채워준다.
	// 다른 자료형으로 하게 되면 비트가 꼬여서 아래 if문이 제대로 동작하지 않음.
	unsigned short lastLetter{ };
	lastLetter = ((lastLetter bitor firstPart << 12) bitor secondPart << 6) bitor thirdPart;

	// 들어온 문자열이 한글의 제일 처음과 끝의 범위 밖일 경우
	// 해당 값은 한글이 아니므로 원본 문자열을 그대로 반환
	if (lastLetter < 0xAC00 or lastLetter > 0xD7A3)
		return sourceString;

	// 유니코드 상 '가'의 코드값이 0xAC00이고 받침이 28글자마다 반복되기 때문에
	// 28로 나눈 나머지 값이 0이면 받침이 없는 경우, 그 이외의 경우는 받침이 있는 경우
	// 으로/로의 처리를 위해 받침이 ㄹ인 경우, 즉 나머지가 8인 경우도 추가
	string selected{ };
	if (secondPostposition.find("로") != string::npos)
		selected = (lastLetter - 0xAC00) % 28 != 0
		? ((lastLetter - 0xAC00) % 28 != 8 ? firstPostposition : secondPostposition)
		: secondPostposition;
	else
		selected = (lastLetter - 0xAC00) % 28 > 0 ? firstPostposition : secondPostposition;

	// 원본 문자열에 선택된 조사를 붙여서 반환해준다.
	return sourceString + selected;
}

string josaProcess(string str, string postposition) {
	string sourceString{ str };

	// 입력된 postposition을 josaList에서 찾는다
	auto it{ find_if(josaList.begin(), josaList.end(), [&postposition](pair<string, string>& josa) {
		if (josa.first == postposition)
			return josa.first == postposition;
		else if (josa.second == postposition)
			return josa.second == postposition;
		else
			return false;
		}
	)
	};

	string firstPostposition{ it->first };
	string secondPostposition{ it->second };

	// 비주얼 스튜디오에서 컴파일한다면 십중팔구 CP_949를 쓸테니 이를 UTF-8로 변환해준다.
#ifdef _MSC_VER
	auto toUTF8{ [](string& multibyte_string) {
		multibyte_string = string{ CW2A{ CA2W{ multibyte_string.c_str() }, CP_UTF8 } };
	} };
	toUTF8(str);
#endif

	// 한글 UTF-8 인코딩 규칙: 1110xxxx 10xxxxxx 10xxxxxx
	// 이것(1110 0000 1000 0000 1000 0000)을 16진수로 바꾸면 E0 8080

	// UTF-8 -> UNICODE
	// 위의 한글 UTF-8 인코딩 규칙에 따라 한글은 3바이트를 차지하게 된다.
	// 따라서 각각의 바이트를 저장할 변수들을 선언한다.
	char firstPart{ };
	char secondPart{ };
	char thirdPart{ };

	// 범위 검사를 위해 try-catch문 사용
	try {
		firstPart = (str.at(str.length() - 3) ^ 0xE0); // 끝의 4비트가 유효한 비트
		secondPart = (str.at(str.length() - 2) ^ 0x80); // 끝의 6비트가 유효한 비트
		thirdPart = (str.at(str.length() - 1) ^ 0x80); // 끝의 6비트가 유효한 비트
	}
	catch (std::exception err) {
		return sourceString;
	}

	// 부호 없는 2바이트 변수를 0으로 초기화 후 비트를 채워준다.
	// 다른 자료형으로 하게 되면 비트가 꼬여서 아래 if문이 제대로 동작하지 않음.
	unsigned short lastLetter{ };
	lastLetter = ((lastLetter bitor firstPart << 12) bitor secondPart << 6) bitor thirdPart;

	// 들어온 문자열이 한글의 제일 처음과 끝의 범위 밖일 경우
	// 해당 값은 한글이 아니므로 원본 문자열을 그대로 반환
	if (lastLetter < 0xAC00 or lastLetter > 0xD7A3)
		return sourceString;

	// 유니코드 상 '가'의 코드값이 0xAC00이고 받침이 28글자마다 반복되기 때문에
	// 28로 나눈 나머지 값이 0이면 받침이 없는 경우, 그 이외의 경우는 받침이 있는 경우
	// 으로/로의 처리를 위해 받침이 ㄹ인 경우, 즉 나머지가 8인 경우도 추가
	string selected{ };
	if (secondPostposition.find("로") != string::npos)
		selected = (lastLetter - 0xAC00) % 28 != 0
		? ((lastLetter - 0xAC00) % 28 != 8 ? firstPostposition : secondPostposition)
		: secondPostposition;
	else
		selected = (lastLetter - 0xAC00) % 28 > 0 ? firstPostposition : secondPostposition;

	// 선택된 조사를 반환해준다.
	return selected;
}



string operator+(string str, pair<string, string> josa) {
	return josaProcess(str, josa.first, josa.second);
}


// 조사가 포함 된 string
class Jstring {
public:
	Jstring(const char* value, size_t length)
		: value{ value, length }, pos{ } { }

	Jstring(string str)
		: value{ str }, pos{ } {
		// 조사들의 인덱스 탐색
		for (int i{ }; i < str.length(); ++i) {
			// 조사가 있는 경우
			if ((josa(this->value.substr(i)).first != "")) {
				// 그리고 조사 바로 다음에 띄어쓰기가 있는 경우
				for (const auto& josa : josaList) {
					// 그 전에 찾았던 영역 다음부터 탐색해서, 조사 바로 다음 값이 ' ' 이 아닌 경우
					if (this->value.at(this->value.find_first_not_of(josa.first, i)) == ' ') {
						// 해당 위치를 pos에 등록
						pos.emplace_back(josa.first, i);
						break;
					}
					else if (this->value.at(this->value.find_first_not_of(josa.second, i)) == ' ') {
						pos.emplace_back(josa.second, i);
						break;
					}
				}
			}
		}
	}

	friend string operator+(string str, Jstring jstr) {
		string result{ josaProcess(str, josa(jstr.value).first, josa(jstr.value).second) };

		// 조사 뒤에 보조사 또는 다른 조사가 오지 않는다는 가정
		// 그럴 경우 조사 뒤에는 반드시 띄어쓰기가 온다.
		return result + jstr.value.substr(jstr.value.find(" "));;
	}

	string value;
	vector<pair<string, int>> pos; // 해당 문자열 내의 조사목록 및 해당 조사들의 인덱스
};

inline namespace josa_literals {
	// cout << name + "이 뜁니다."j;
	// 해당 리터럴의 사용례:
	// "이 맞아요."j
	// "가 할 수 있어!"j
	// "은 쉽니다."j
	// 위의 예시처럼 조사가 붙어야 하는 변수 바로 뒤에 이어서 써주는 식으로 사용.
	_NODISCARD inline Jstring operator"" j(const char* _Str, size_t _Len) {
		return Jstring{ _Str, _Len };
	}

	// cout << name + "이 뜁니다."조;
	// 해당 리터럴의 사용례:
	// "이 맞아요."조
	// "가 할 수 있어!"조
	// "은 쉽니다."조
	// 위의 예시처럼 조사가 붙어야 하는 변수 바로 뒤에 이어서 써주는 식으로 사용.
	_NODISCARD inline Jstring operator"" 조(const char* _Str, size_t _Len) {
		return Jstring{ _Str, _Len };
	}
} // namespace josa_literals

// C++23때 추가 될 format 문법
// 주의! 아직 표준에 정식으로 추가된 문법이 아닙니다.
// 비주얼 스튜디오 기준으로 사용을 위해서는
// 현재 솔루션 마우스 오른쪽 클릭 -> 속성 -> C++ 언어 표준: 미리 보기 - 최신 C++ 초안의 기능(/std:c++latest)
// 으로 바꿔준 뒤, 아래 주석을 해제하여 사용해주시면 됩니다. 
//#include <format>
//using std::format;
//
//template <class... _Types>
//_NODISCARD string format(const Jstring jstr, const _Types&... _Args) {
//	Jstring temp{ vformat(std::string_view{ jstr.value }, make_format_args(_Args...)) };
//	// first: 해당 문자열 내의 조사
//	// second: 해당 조사의 인덱스
//	for (const auto& elem : temp.pos)
//		temp.value.replace(elem.second, elem.first.length(), josaProcess(temp.value.substr(0, elem.second), elem.first));
//	
//	return temp.value;
//}
