#include "josa.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

using std::string;

int main() {
	string str{ };
	cin >> str;
	// ��/��, ��/��, ��/��, ��/��, ��/��, �̿�/��, �̶�/��, ����/��
	// ���� ���縦 �ι�°, ����° ���ڷ� �־ ���縦 ���� str �ڿ� �ٿ� ��ȯ���ݴϴ�.
	cout << josa(str, "����", "��") << endl;

	return 0;
}