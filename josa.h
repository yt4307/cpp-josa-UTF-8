#pragma once

#ifdef _MSC_VER
// CW2A �� CA2W�� ���� ���� ���
#include <atlstr.h>
#endif

#include <string>

using std::string;

// ��/��, ��/��, ��/��, ��/��, ��/��, �̿�/��, �̶�/��, ����/��
// ��ħ�� ������ ����, ��ħ�� ������ ����
// ��, ����/�δ� ����ħ�϶��� ���ΰ� �ƴ� �� ���
string josa(string str, string firstPostposition, string secondPostposition) {
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