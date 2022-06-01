#pragma once
// ��Ʈ�� ���ͷ� ���̻翡 _ �Ⱥپ��ٴ� ��� ����
#pragma warning( disable : 4455 )

#ifdef _MSC_VER
// CW2A �� CA2W�� ���� ���� ���
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
	{ "��", "��" },
	{ "��", "��" },
	{ "��", "��" },
	{ "��", "��" },
	{ "��", "��" },
	{ "�̿�", "��" },
	{ "�̶�", "��" },
	{ "����", "��" }
};

pair<string, string> josa(string str) {
	// �ٸ� ���ڸ� ����� �������� �ʵ��� 0�� �ε������� ù��° " " ���� ���� Ž��
	str = str.substr(0, str.find(" "));

	for (const auto& josa : josaList)
		if ((str.find(josa.first) != string::npos) or (str.find(josa.second) != string::npos))
			return josa;

	return { };
}


// ��/��, ��/��, ��/��, ��/��, ��/��, �̿�/��, �̶�/��, ����/��
// ��ħ�� ������ ����, ��ħ�� ������ ����
// ��, ����/�δ� ����ħ�϶��� ���ΰ� �ƴ� �� ���
string josaProcess(string str, string firstPostposition, string secondPostposition) {
	string sourceString{ str };

	// ���־� ��Ʃ������� �������Ѵٸ� �����ȱ� CP_949�� ���״� �̸� UTF-8�� ��ȯ���ش�.
#ifdef _MSC_VER
	auto toUTF8{ [](string& multibyte_string) {
		multibyte_string = string{ CW2A{ CA2W{ multibyte_string.c_str() }, CP_UTF8 } };
	} };
	toUTF8(str);
#endif

	// �ѱ� UTF-8 ���ڵ� ��Ģ: 1110xxxx 10xxxxxx 10xxxxxx
	// �̰�(1110 0000 1000 0000 1000 0000)�� 16������ �ٲٸ� E0 8080

	// UTF-8 -> UNICODE
	// ���� �ѱ� UTF-8 ���ڵ� ��Ģ�� ���� �ѱ��� 3����Ʈ�� �����ϰ� �ȴ�.
	// ���� ������ ����Ʈ�� ������ �������� �����Ѵ�.
	char firstPart{ };
	char secondPart{ };
	char thirdPart{ };

	// ���� �˻縦 ���� try-catch�� ���
	try {
		firstPart = (str.at(str.length() - 3) ^ 0xE0); // ���� 4��Ʈ�� ��ȿ�� ��Ʈ
		secondPart = (str.at(str.length() - 2) ^ 0x80); // ���� 6��Ʈ�� ��ȿ�� ��Ʈ
		thirdPart = (str.at(str.length() - 1) ^ 0x80); // ���� 6��Ʈ�� ��ȿ�� ��Ʈ
	}
	catch (std::exception err) {
		return sourceString;
	}

	// ��ȣ ���� 2����Ʈ ������ 0���� �ʱ�ȭ �� ��Ʈ�� ä���ش�.
	// �ٸ� �ڷ������� �ϰ� �Ǹ� ��Ʈ�� ������ �Ʒ� if���� ����� �������� ����.
	unsigned short lastLetter{ };
	lastLetter = ((lastLetter bitor firstPart << 12) bitor secondPart << 6) bitor thirdPart;

	// ���� ���ڿ��� �ѱ��� ���� ó���� ���� ���� ���� ���
	// �ش� ���� �ѱ��� �ƴϹǷ� ���� ���ڿ��� �״�� ��ȯ
	if (lastLetter < 0xAC00 or lastLetter > 0xD7A3)
		return sourceString;

	// �����ڵ� �� '��'�� �ڵ尪�� 0xAC00�̰� ��ħ�� 28���ڸ��� �ݺ��Ǳ� ������
	// 28�� ���� ������ ���� 0�̸� ��ħ�� ���� ���, �� �̿��� ���� ��ħ�� �ִ� ���
	// ����/���� ó���� ���� ��ħ�� ���� ���, �� �������� 8�� ��쵵 �߰�
	string selected{ };
	if (secondPostposition.find("��") != string::npos)
		selected = (lastLetter - 0xAC00) % 28 != 0
		? ((lastLetter - 0xAC00) % 28 != 8 ? firstPostposition : secondPostposition)
		: secondPostposition;
	else
		selected = (lastLetter - 0xAC00) % 28 > 0 ? firstPostposition : secondPostposition;

	// ���� ���ڿ��� ���õ� ���縦 �ٿ��� ��ȯ���ش�.
	return sourceString + selected;
}

string josaProcess(string str, string postposition) {
	string sourceString{ str };

	// �Էµ� postposition�� josaList���� ã�´�
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

	// ���־� ��Ʃ������� �������Ѵٸ� �����ȱ� CP_949�� ���״� �̸� UTF-8�� ��ȯ���ش�.
#ifdef _MSC_VER
	auto toUTF8{ [](string& multibyte_string) {
		multibyte_string = string{ CW2A{ CA2W{ multibyte_string.c_str() }, CP_UTF8 } };
	} };
	toUTF8(str);
#endif

	// �ѱ� UTF-8 ���ڵ� ��Ģ: 1110xxxx 10xxxxxx 10xxxxxx
	// �̰�(1110 0000 1000 0000 1000 0000)�� 16������ �ٲٸ� E0 8080

	// UTF-8 -> UNICODE
	// ���� �ѱ� UTF-8 ���ڵ� ��Ģ�� ���� �ѱ��� 3����Ʈ�� �����ϰ� �ȴ�.
	// ���� ������ ����Ʈ�� ������ �������� �����Ѵ�.
	char firstPart{ };
	char secondPart{ };
	char thirdPart{ };

	// ���� �˻縦 ���� try-catch�� ���
	try {
		firstPart = (str.at(str.length() - 3) ^ 0xE0); // ���� 4��Ʈ�� ��ȿ�� ��Ʈ
		secondPart = (str.at(str.length() - 2) ^ 0x80); // ���� 6��Ʈ�� ��ȿ�� ��Ʈ
		thirdPart = (str.at(str.length() - 1) ^ 0x80); // ���� 6��Ʈ�� ��ȿ�� ��Ʈ
	}
	catch (std::exception err) {
		return sourceString;
	}

	// ��ȣ ���� 2����Ʈ ������ 0���� �ʱ�ȭ �� ��Ʈ�� ä���ش�.
	// �ٸ� �ڷ������� �ϰ� �Ǹ� ��Ʈ�� ������ �Ʒ� if���� ����� �������� ����.
	unsigned short lastLetter{ };
	lastLetter = ((lastLetter bitor firstPart << 12) bitor secondPart << 6) bitor thirdPart;

	// ���� ���ڿ��� �ѱ��� ���� ó���� ���� ���� ���� ���
	// �ش� ���� �ѱ��� �ƴϹǷ� ���� ���ڿ��� �״�� ��ȯ
	if (lastLetter < 0xAC00 or lastLetter > 0xD7A3)
		return sourceString;

	// �����ڵ� �� '��'�� �ڵ尪�� 0xAC00�̰� ��ħ�� 28���ڸ��� �ݺ��Ǳ� ������
	// 28�� ���� ������ ���� 0�̸� ��ħ�� ���� ���, �� �̿��� ���� ��ħ�� �ִ� ���
	// ����/���� ó���� ���� ��ħ�� ���� ���, �� �������� 8�� ��쵵 �߰�
	string selected{ };
	if (secondPostposition.find("��") != string::npos)
		selected = (lastLetter - 0xAC00) % 28 != 0
		? ((lastLetter - 0xAC00) % 28 != 8 ? firstPostposition : secondPostposition)
		: secondPostposition;
	else
		selected = (lastLetter - 0xAC00) % 28 > 0 ? firstPostposition : secondPostposition;

	// ���õ� ���縦 ��ȯ���ش�.
	return selected;
}



string operator+(string str, pair<string, string> josa) {
	return josaProcess(str, josa.first, josa.second);
}


// ���簡 ���� �� string
class Jstring {
public:
	Jstring(const char* value, size_t length)
		: value{ value, length }, pos{ } { }

	Jstring(string str)
		: value{ str }, pos{ } {
		// ������� �ε��� Ž��
		for (int i{ }; i < str.length(); ++i) {
			// ���簡 �ִ� ���
			if ((josa(this->value.substr(i)).first != "")) {
				// �׸��� ���� �ٷ� ������ ���Ⱑ �ִ� ���
				for (const auto& josa : josaList) {
					// �� ���� ã�Ҵ� ���� �������� Ž���ؼ�, ���� �ٷ� ���� ���� ' ' �� �ƴ� ���
					if (this->value.at(this->value.find_first_not_of(josa.first, i)) == ' ') {
						// �ش� ��ġ�� pos�� ���
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

		// ���� �ڿ� ������ �Ǵ� �ٸ� ���簡 ���� �ʴ´ٴ� ����
		// �׷� ��� ���� �ڿ��� �ݵ�� ���Ⱑ �´�.
		return result + jstr.value.substr(jstr.value.find(" "));;
	}

	string value;
	vector<pair<string, int>> pos; // �ش� ���ڿ� ���� ������ �� �ش� ������� �ε���
};

inline namespace josa_literals {
	// cout << name + "�� �ݴϴ�."j;
	// �ش� ���ͷ��� ����:
	// "�� �¾ƿ�."j
	// "�� �� �� �־�!"j
	// "�� ���ϴ�."j
	// ���� ����ó�� ���簡 �پ�� �ϴ� ���� �ٷ� �ڿ� �̾ ���ִ� ������ ���.
	_NODISCARD inline Jstring operator"" j(const char* _Str, size_t _Len) {
		return Jstring{ _Str, _Len };
	}

	// cout << name + "�� �ݴϴ�."��;
	// �ش� ���ͷ��� ����:
	// "�� �¾ƿ�."��
	// "�� �� �� �־�!"��
	// "�� ���ϴ�."��
	// ���� ����ó�� ���簡 �پ�� �ϴ� ���� �ٷ� �ڿ� �̾ ���ִ� ������ ���.
	_NODISCARD inline Jstring operator"" ��(const char* _Str, size_t _Len) {
		return Jstring{ _Str, _Len };
	}
} // namespace josa_literals

// C++23�� �߰� �� format ����
// ����! ���� ǥ�ؿ� �������� �߰��� ������ �ƴմϴ�.
// ���־� ��Ʃ��� �������� ����� ���ؼ���
// ���� �ַ�� ���콺 ������ Ŭ�� -> �Ӽ� -> C++ ��� ǥ��: �̸� ���� - �ֽ� C++ �ʾ��� ���(/std:c++latest)
// ���� �ٲ��� ��, �Ʒ� �ּ��� �����Ͽ� ������ֽø� �˴ϴ�. 
//#include <format>
//using std::format;
//
//template <class... _Types>
//_NODISCARD string format(const Jstring jstr, const _Types&... _Args) {
//	Jstring temp{ vformat(std::string_view{ jstr.value }, make_format_args(_Args...)) };
//	// first: �ش� ���ڿ� ���� ����
//	// second: �ش� ������ �ε���
//	for (const auto& elem : temp.pos)
//		temp.value.replace(elem.second, elem.first.length(), josaProcess(temp.value.substr(0, elem.second), elem.first));
//	
//	return temp.value;
//}
