# cpp-josa-UTF-8
C++ 에서 사용할 수 있는 UTF-8 기반의 한글 조사 처리 라이브러리입니다.

## 예제
```cpp
int main() {
	string str{ };
	cin >> str;
	// 은/는, 이/가, 을/를, 과/와, 아/야, 이여/여, 이랑/랑, 으로/로
	// 등의 조사를 두번째, 세번째 인자로 넣어서 조사를 원본 str 뒤에 붙여 반환해줍니다.
	
	// 이런식으로 직접 josaProcess를 호출하여 조사를 붙여 줄 수도 있고,
	cout << josaProcess(str, "으로", "로") << endl;

	// 또는 이런식으로 간단하게 조사를 붙여 줄 수도 있습니다.
	cout << str + josa("를") << endl;

	return 0;
}
```

## 사용법
josa.h를 필요한 코드에서 가져다 include 하여 사용하면 됩니다.

## 참고
- 본 라이브러리는 Visual Studio 2022를 통해 테스트 되었습니다.

