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

	// �Ʒ��� ���� ���ͷ� ���̻� j �Ǵ� ���� �ٿ� �����ϰ� ����� ���� �ֽ��ϴ�.
	cout << str + "�� �ƴմϴ�."j << endl;
	cout << str + "�� �̰� �� ������"�� << endl;

	// C++ 23���� �߰� �� format ������ ����ϸ�, �̷������ε� ����� �� �ֽ��ϴ�.
	//cout << format("{}�� {}�� �ƴմϴ�."j, str, "������") << endl;

	return 0;
}
