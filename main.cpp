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
	
	// �̷������� ���� josaProcess�� ȣ���Ͽ� ���縦 �ٿ� �� ���� �ְ�,
	cout << josaProcess(str, "����", "��") << endl;

	// �Ǵ� �̷������� �����ϰ� ���縦 �ٿ� �� ���� �ֽ��ϴ�.
	cout << str + josa("��") << endl;

	return 0;
}
