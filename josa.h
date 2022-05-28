#pragma once

#ifdef _MSC_VER
// CW2A 및 CA2W를 쓰기 위한 헤더
#include <atlstr.h>
#endif

#include <string>

using std::string;

// 은/는, 이/가, 을/를, 과/와, 아/야, 이여/여, 이랑/랑, 으로/로
// 받침이 있으면 앞쪽, 받침이 없으면 뒤쪽
// 단, 으로/로는 ㄹ받침일때도 으로가 아닌 로 사용
string josa(string str, string firstPostposition, string secondPostposition) {
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