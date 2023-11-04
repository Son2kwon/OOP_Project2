#include "inf_int.h"
#include<iostream>
#include<string>
#include<utility>
#include<sstream>
using namespace std;

// calculator for the problem 2
void calculator() {
	string input;
	string a, b;
	char op;

	while (true) {
		cout << "Input: ";
		getline(cin, input);
		stringstream s(input);

		if (input[0] == '0') break;

		s >> a >> op >> b;

		inf_int input_a(a);
		inf_int input_b(b);

		if (op == '+') {
			cout << "Output: " <<  input_a + input_b << endl;
		}

		else if(op == '-') {
			cout << "Output: " << input_a - input_b << endl;
		}

		else if (op == '*') {
			cout << "Output: " << input_a * input_b << endl;
		}
	}
}

/* default constructor는 0으로 설정 */ 
inf_int::inf_int() {
	digits = '0' + '\0';
	length = 1;
	thesign = true; // 0은 양수로 가정
}

/* 사용자 지정 constructor, 매개변수로 정수가 들어왔을 때 */ 
inf_int::inf_int(int integer) {
	thesign = (integer >= 0) ? true : false; // a가 0보다 작거나 크면 true, 작으면 false
	if (integer < 0) integer = integer * -1;	// 음수라면 -1 곱해서 양수로 만둘어줌
	digits = to_string(integer) + '\0';
	length = digits.length() - 1;
}

/* 사용자 지정 constructor, 매개변수로 string이 들어왔을 때 */
inf_int::inf_int(const string str) {
	if (str[0] == '-') {	// 첫 문자가 -면 음수.
		digits = str.substr(1, length - 1) + '\0';	// 첫 문자 빼고 나머지 + null 문자
		thesign = false;	// 부호는 false로 설정
	}

	else {
		digits = str + '\0';	// str + null 문자
		thesign = true;	// 부호는 true
	}

	length = digits.length() - 1;	// 길이는 (숫자 + null문자) - 1
}

/* copy constructor */
inf_int::inf_int(const inf_int& other) {
	digits = '0' + '\0';	// 복제하기 전 초기화
	digits = other.digits;	// 다음부턴 뭐... 그냥 넣기
	length = other.length;
	thesign = other.thesign;
}

/* destructor */
inf_int::~inf_int(){}

/*  연산자 overloading*/
inf_int& inf_int::operator=(const inf_int& other) {
	this->digits = '0' + '\0';	// 대입연산 하기 전에 초기화
	this->digits = other.digits;	// copy constructor랑 마찬가지로...
	this->length = other.length;
	this->thesign = other.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b){
	if(a.digits == b.digits && a.thesign == b.thesign) return true;	// 둘이 digits가 같고, 부호가 같다면 true
	
	return false;	// 아니라면 false
}

bool operator!=(const inf_int& a, const inf_int& b){
	if(a.digits == b.digits && a.thesign == b.thesign) return false;	// digits가 같고 부호가 같다면 false
	
	return true;	// 아니라면 true
}

bool operator>(const inf_int& a, const inf_int& b){
	if (a == b) return false;	// 혹시 같다면 false

	else if (a.thesign == true && b.thesign == false) return true;	// 양수는 음수보다 큼
	else if (a.thesign == false && b.thesign == true) return false;	// 음수는 양수보다 작음

	else if (a.thesign == true && b.thesign == true) {	// 둘 다 양수라면
		if (a.length != b.length) return a.length > b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 큼

		else { // 길이가 같다면...
			int length = a.length;	// 같으니까 아무거나 대입
			for (int i = 0; i < length; i++) {	// 가장 큰 숫자부터 비교해야 함
				if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
				else return (a.digits[i] - '0') > (b.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
			}
		}
	}

	else if (a.thesign == false && b.thesign == false) {	// 둘 다 음수라면 양수일 때와 결과 반대
		if (a.length != b.length) return a.length < b.length; // 길이가 다르다면, 길이가 긴 것이 더 작음

		else { // 길이가 같다면...
			int length = a.length;
			for (int i = 0; i < length; i++) {
				if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
				else return (a.digits[i] - '0') < (b.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
			}
		}
	}
}

bool operator<(const inf_int& a, const inf_int& b){
	if (a == b) return false;	// 혹시 같다면 false

	else if (a.thesign == false && b.thesign == true) return true;	// 음수 < 양수
	else if (a.thesign == true && b.thesign == false) return false;	// 양수 > 음수

	else if (a.thesign == true && b.thesign == true) {	// 둘 다 양수라면
		if (a.length != b.length) return a.length < b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 큰 정수

		else { // 길이가 같다면...
			int length = a.length;	// 길이 같으니까 아무거나 대입
			for (int i = 0; i < length; i++) {	// 가장 큰 숫자부터 비교
				if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
				else return (b.digits[i] - '0') > (a.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
			}
		}
	}
	
	else if (a.thesign == false && b.thesign == false) {	// 둘 다 음수라면
		if (a.length != b.length) return a.length > b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 작은 정수

		else { // 길이가 같다면...
			int length = b.length;	// 길이 같으니까 아무거나 대입
			for (int i = 0; i < length; i++) {
				if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
				else return (b.digits[i] - '0') < (a.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
			}
		}
	}
}

inf_int operator+(const inf_int& a, const inf_int& b){
	/*
	* 1. a > 0, b > 0
		문제 없음

	* 2. 둘 중 하나라도 음수
		빼기 연산

	* 3. 둘 다 음수
		result의 sign만 바꾼 후 더하기 연산



	덧셈 연산

		각 문자열의 마지막 index(1의 자리)부터 차례대로 옮겨가며 계산함
		carry가 생긴다면, 다음 자릿수 계산할 때 더할 것. 기본 carry는 0. (carry는 1이 최대)
		char를 int로 바꿔 계산 후 char형 변수 digit에 저장
		result.digit의 앞에 붙여주는 형태로 덧셈
		가장 마지막 자리 계산에서 carry가 발생하면 추가적으로 1을 붙여줌
	*/


	inf_int result; // return할 object
	result.digits = '\0'; // 문자열의 마지막에 null을 미리 넣어줌

	int index_a = a.length - 1, index_b = b.length - 1;	// 각 index 생성
	int carry = 0;	// carry 기본 = 0
	
	// 1번 or 3번 케이스
	if (a.thesign == b.thesign) {
		while (index_a >= 0 && index_b >= 0) { // 둘 중 하나라도 끝날 때까지
			int int_a = a.digits[index_a] - '0'; // 자릿수를 int형으로
			int int_b = b.digits[index_b] - '0';

			if (carry + int_a + int_b >= 10) { // carry까지 고려했을 때, 최대값은 19
				char digit = (carry + int_a + int_b - 10) + '0';	// 연산 결과에서 10 빼주고 char형에 맞게.
				result.digits = digit + result.digits;	// result 앞에 연산 결과(1의 자리) 붙여줌
				carry = 1;	// carry 발생했으니까 1로 설정
			}

			else {
				char digit = (carry + int_a + int_b) + '0';	// 10이 안 넘어가므로 그냥 계산
				result.digits = digit + result.digits;
				carry = 0;
			}
			index_a--; index_b--;// 다음 자릿수 계산
		}

		while (index_a >= 0) { //만약 b가 끝났다면,
			int int_a = a.digits[index_a] - '0';	// a만 고려해서 그냥 붙여줌
			if (carry + int_a >= 10) {	// 만약 위 while 문에서 carry가 있어 연산 결과 10이 넘어가는 경우
				char digit = (carry + int_a - 10) + '0';	// 위에서 한 것과 동일하게 연산
				result.digits = digit + result.digits;
				carry = 1;
				index_a--;	// 다음 자릿수 계산
			}

			else {
				char digit = (carry + int_a) + '0';	// carry가 있을 수 있으니, 감안하여 계산. 이 부분은 carry 포함해서 계산해도 10이 안 넘어가는 경우.
				result.digits = digit + result.digits; 
				index_a--;	// 다음 자릿수 계산
				carry = 0;	// carry는 발생하지 않음
			}
		}
		
		while (index_b >= 0) {	// a가 끝났다면, a가 끝난 경우와 동일
			int int_b = b.digits[index_b] - '0';
			if (carry + int_b >= 10) {
				char digit = (carry + int_b - 10) + '0';
				result.digits = digit + result.digits;
				carry = 1;
				index_b--;
			}

			else {
				char digit = (carry + int_b) + '0';
				result.digits = digit + result.digits;
				index_b--;
				carry = 0;
			}
		}

		if (carry == 1) 	// 모든 자릿수 연산이 끝난 후에 carry가 남아있는 경우
			result.digits = '1' + result.digits;	// result 앞에 1을 붙여줌
		
		if (a.thesign == false && b.thesign == false) result.thesign = false; // 둘 다 음수일 경우, 똑같이 계산 후 sign만 바꿔줌
																			  // 양수일 경우에는 그대로
		result.length = result.digits.length() - 1;	// 계산 다 끝난 후에 자릿수 계산
		return result;
	}

	else {	// 둘 중 하나라도 음수라면
		return a - b;
	}
}

inf_int operator-(const inf_int& a, const inf_int& b){
	/*
	1. a > 0, b > 0
		그냥 연산
	2. a > 0, b < 0
		더하기 연산
	3. a < 0, b > 0
		음수라 치고 더하기 연산
	4. a < 0, b < 0
		1번과 같은 케이스, 부호만 반대.
	*/

	// 2번 케이스
	if (a.thesign == true && b.thesign == false) {
		inf_int temp = b;	// b를 양수 취급하는 변수 temp
		temp.thesign = true;
		return a + temp;	// a + temp = a + (-b) = a - b;
	}
	// 3번 케이스
	else if (a.thesign == false && b.thesign == true) {
		inf_int temp = b;	// b를 음수 취급하는 변수 temp
		temp.thesign = false;

		return a + temp;	// a + temp = a + (-b) = a - b;
	}

	// 1번 케이스
	else if(a.thesign == true && b.thesign == true) {
		inf_int result;	// 결과를 저장할 object
		result.digits = '\0';	// 미리 null 문자를 넣어줌

		if (b > a) {	// b가 a보다 크다면, a와 b만 바꾼 후 sign만 negative로 설정
						// 항상 a가 b보다 큰 상태를 가정하려고 함
			result = b - a;
			result.thesign = false;
			return result;
		}

		int index_a = a.length - 1, index_b = b.length - 1;
		int borrow = 0;	// borrow는 -1 or 0

		while (index_b >= 0) {
			int int_a = a.digits[index_a] - '0', int_b = b.digits[index_b] - '0';	// 각 자릿수 integer 형태로 만듦
			int digit = int_a - int_b + borrow;	// 뺄셈 후 borrow 까지 연선

			if (digit < 0) {	// 연산 결과가 0보다 작으면 borrow 필요, 연산 결과에 10 더해야 함
				digit = digit + 10;
				borrow = -1;
			}

			else borrow = 0;	// 연산 결과가 0보다 크면 borrow 필요 없음

			result.digits = (char)(digit + '0') + result.digits;	// result에 update
			index_a--; index_b--;	// 다음 자릿수 보기
		}

		while (index_a >= 0) {	// 항상 a > b 이므로 b가 더 먼저 끝나거나 같이 끝남
			int digit = a.digits[index_a] - '0' + borrow;
			
			if (digit < 0) {	// 마찬가지로 계산
				digit += 10;
				borrow = -1;
			}

			else borrow = 0;

			result.digits = (char)(digit + '0') + result.digits;

			index_a--;	// 다음 자릿수
		}

		while (result.digits[0] == '0') {	// 혹시 불필요한 0이 나오면 0을 제거해주기 위함
			if (result.digits[0] = '0') {
				result.digits = result.digits.substr(1, result.digits.length() - 1);	// 0번재 index에 있는 0 빼고 나머지 string만 저장
			}
		}

		if (result.digits[0] == '\0') result.digits = '0' + '\0';	// 만약 연산 결과가 0이라 digits에 null 문자만 남았을 경우, 0을 저장

		result.length = result.digits.length() - 1;	// length 설정
		return result;
	}

	else if (a.thesign == false && b.thesign == false) {
		inf_int result;	// 결과를 저장할 object
		result.digits = '\0';	// 미리 null 문자를 넣어줌

		if (a > b) {	// 음수에서 a가 더 크다는 건, 절댓값이 더 크다는 것
						//  그 결과는 양수
			inf_int temp_a = a, temp_b = b;	// a와 b를 양수로 취급하기 위한 변수 temp_a, temp_b
			temp_a.thesign = true; temp_b.thesign = true;

			result = temp_b - temp_a;
			result.thesign = true;
			return result;
		}

		// b가 더 크다는 것은 절댓값이 더 작다는 것
		// ex) -123, -45 뺄셈 연산 -> -123 + 45 -> -(123 - 45)

		int index_a = a.length - 1, index_b = b.length - 1;
		int borrow = 0;

		while (index_b >= 0) {
			int int_a = a.digits[index_a] - '0', int_b = b.digits[index_b] - '0';
			int digit = int_a - int_b + borrow;

			if (digit < 0) {	// 연산 결과가 0보다 작으면 borrow 필요, 연산 결과에 10 더해야 함
				digit = digit + 10;
				borrow = -1;
			}

			else borrow = 0;

			result.digits = (char)(digit + '0') + result.digits;
			index_a--; index_b--;
		}

		while (index_a >= 0) {
			int digit = a.digits[index_a] - '0' + borrow;
			result.digits = (char)(digit + '0') + result.digits;

			borrow = 0;
			index_a--;
		}

		while (result.digits[0] == '0') {
			if (result.digits[0] = '0') {
				result.digits = result.digits.substr(1, result.digits.length() - 1);
			}
		}
		result.thesign = false;

		if (result.digits[0] == '\0') result.digits = '0' + '\0';

		result.length = result.digits.length() - 1;
		return result;
	}
}

inf_int operator*(const inf_int& a, const inf_int& b){
	/* 
	1. 부호가 같은 경우
		multiplication 후에 sign positive
	2. 부호가 다른 경우
		multiplication 후에 sign negative

	Multiplication
		a전체 * b의 각 자리
			각 자리 곱셈, carry는 10으로 나눴을 때 몫, 나머지는 그대로 쓰기
			다음 자리 곱셈하고 carry더한 후 10으로 나누기
		자릿수에 맞게 0 붙이기
		덧셈

	*/

	inf_int result;	// 결과를 저장할 object

	if (a.thesign == b.thesign) result.thesign = true;	// 부호가 같으면 양수
	else result.thesign = false;	// 다르면 음수
	
	if (b.length > a.length) return b * a;	// 항상 a의 길이가 더 길도록 하기 위해

	int index_b = b.length - 1, index = 0;	// b의 각 자리를 표현하기 위한 index_b


	while (index_b >= 0) {	// 각 자리 loop
		int int_b = b.digits[index_b] - '0';
		int carry = 0;

		inf_int temp; temp.digits = '\0';	// b 각 자릿수 곱셈을 저장할 변수 temp
		int index_a = a.length - 1;	// a의 각 자리를 표현하기 위한 index_a

		while (index_a >= 0) {
			int int_a = a.digits[index_a] - '0';
			int digit = int_a * int_b + carry; carry = digit / 10; digit = digit % 10;	// carry = 연산 결과의 10의 자리 이상, digit = 연산 결과의 1의 자리

			temp.digits = (char)(digit + '0') + temp.digits;	// temp에 b 이번 자리 연산 결과 저장
			index_a--;	// a의 다음 자리를 보기 위함
		}

		if (carry > 0) temp.digits = (char)(carry + '0') + temp.digits;	// 연산 다 끝난 후에 carry가 있다면 올려줌

		for (int i = 0; i < index; i++) {
			temp.digits.insert(temp.digits.length() - 1, 1, '0');	// b의 자릿수에 맞게 0을 붙여줌 ex) 123 * 45 = 123 * 4 * 10 + 123 * 5 에서 10에 해당하는 연산
		}

		temp.length = temp.digits.length() - 1;	// + 연산을 위한 length update
		result.length = result.digits.length() - 1;	// + 연산을 위한 length update
		result = result + temp;	// result에 저장
		index_b--; index++;	// b의 다음 자릿수, 0의 개수 1 증가
	}

	return result;
}

ostream& operator<<(ostream& o, const inf_int& value) {
	char sign = value.thesign ? '+' : '-';	// 양수인지 음수인지

	if (sign == '+') o << value.digits << endl;	// 양수라면 digit만 출력
	else o << sign <<  value.digits << endl;	// 음수라면 앞에 - 출력하고 digit 출력

	return o;
}