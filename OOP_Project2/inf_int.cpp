#include "inf_int.h"
#include<string>
using namespace std;

/* default constructor는 0으로 설정 */ 
inf_int::inf_int() {
	digits = '0' + '\0';
	length = 1;
	thesign = true; // 0은 양수로 가정
}

/* 사용자 지정 constructor, 매개변수로 정수가 들어왔을 때 */ 
inf_int::inf_int(int integer) {
	if (integer <= 0) integer = integer * -1;
	digits = to_string(integer) + '\0';
	length = digits.length();
	thesign = (integer >= 0) ? true : false; // a가 0보다 작거나 크면 true, 작으면 false
}

/* 사용자 지정 constructor, 매개변수로 string이 들어왔을 때 */
inf_int::inf_int(const string str) {
	length = digits.length();

	if (str[0] == '-') {
		digits = str.substr(1, length - 1);
		length--;
	}

	digits = str;
	thesign = (str[0] == '-') ? false : true; // 가장 첫 문자가 -면 false, 외에는 true
}

/* copy constructor */
inf_int::inf_int(const inf_int& other) {
	digits = other.digits;
	length = other.length;
	thesign = other.thesign;
}

/* destructor */
inf_int::~inf_int(){}

/*  연산자 overloading*/
inf_int& inf_int::operator=(const inf_int& other) {
	inf_int ret_value;
	ret_value.digits = other.digits;
	ret_value.length = other.length;
	ret_value.thesign = other.thesign;

	return ret_value;
}

bool operator==(const inf_int& a, const inf_int& b){
	if(a.digits == b.digits && a.thesign == b.thesign) return true;
	
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b){
	if(a.digits == b.digits && a.thesign == b.thesign) return false;
	
	return true;
}

bool operator>(const inf_int& a, const inf_int& b){
	if (a.thesign == true && b.thesign == false) return true;	// 앵수는 음수보다 큼
	else if (a.thesign == false && b.thesign == true) return false;	// 음수는 양수보다 작음

	else if (a.thesign == true && b.thesign == true) {	// 둘 다 양수라면
		if (a.length != b.length) return a.length > b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 큰 정수

		else { // 길이가 같다면...
			int length = a.length;
			for (int i = 0; i < length; i++) {
				if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
				else return (a.digits[i] - '0') > (b.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
			}
		}
	}

	else if (a.thesign == false && b.thesign == false) {	// 둘 다 음수라면 양수일 때와 결과 반대
		if (a.length != b.length) return a.length < b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 큰 정수

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
	//if (a.length != b.length) return a.length < b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 큰 정수

	//else { // 길이가 같다면...
	//	int length = b.length;
	//	for (int i = 0; i < length; i++) {
	//		if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
	//		else return (b.digits[i] - '0') > (a.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
	//	}

	//	return false;
	//}

	// operator > 의 반대

	return !(a > b);
}

inf_int operator+(const inf_int& a, const inf_int& b){
	/*
	* 1. a > 0, b > 0
		문제 없음

		각 문자열의 마지막 index(1의 자리)부터 차례대로 옮겨가며 계산함
		carry가 생긴다면, 다음 자릿수 계산할 때 더할 것
		carry는 1이 최대
		char를 int로 바꿔 계산 후 char형 변수 digit에 저장
		result.digit의 앞에 붙여주는 형태로 덧셈
		가장 마지막 자리 계산에서 carry가 발생하면 추가적으로 1을 붙여줌

	* 2. 둘 중 하나라도 음수
		빼기 연산

	* 3. 둘 다 음수
		result의 sign만 바꾼 후 더하기 연산
	*/


	inf_int result; // 결과 class
	result.digits = '\0'; // 문자열의 마지막에 null을 미리 넣어줌

	int index_a = a.length - 1, index_b = b.length - 1;
	int carry = 0;
	
	// 1번 or 3번 케이스
	if (a.thesign == b.thesign) {
		while (index_a >= 0 && index_b >= 0) { // 둘 중 하나라도 끝날 때까지
			int int_a = a.digits[index_a] - '0'; // 자릿수를 int형으로
			int int_b = b.digits[index_b] - '0';

			if (carry + int_a + int_b >= 10) { // carry까지 고려했을 때, 최대값은 19
				char digit = (carry + int_a + int_b - 10) + '0';
				result.digits = digit + result.digits;
				carry = 1;
			}

			else {
				char digit = (carry + int_a + int_b) + '0';
				result.digits = digit + result.digits;
				carry = 0;
			}
			index_a--; index_b--;// 다음 자릿수 계산
		}

		while (index_a >= 0) { //만약 b가 끝났다면,
			int int_a = a.digits[index_a] - '0';
			if (carry + int_a >= 10) {
				char digit = (carry + int_a - 10) + '0';
				result.digits = digit + result.digits;
				carry = 1;
				index_a--;
			}

			else {
				char digit = (carry + int_a) + '0';
				result.digits = digit + result.digits; // 혹시 마지막 계산에서 carry가 있었을 수도 있으니 포함해서 계산
				index_a--;
				carry = 0;
			}
		}

		while (index_b >= 0) {
			int int_b = b.digits[index_b] - '0';
			if (carry + int_b >= 10) {
				char digit = (carry + int_b - 10) + '0';
				result.digits = digit + result.digits;
				carry = 1;
				index_b--;
			}

			else {
				char digit = (carry + int_b) + '0';
				result.digits = digit + result.digits; // 혹시 마지막 계산에서 carry가 있었을 수도 있으니 포함해서 계산
				index_b--;
				carry = 0;
			}
		}

		if (carry == 1) {
			result.digits = '1' + result.digits;
			result.length++;
		}
		
		if (a.thesign == false && b.thesign == false) result.thesign = false; // 둘 다 음수일 경우, 똑같이 계산 후 sign만 바꿔줌
																			// 양수일 경우에는 그대로

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
		1번과 같은 케이스
	*/

	// 2번 케이스
	if (a.thesign == true && b.thesign == false) {
		inf_int temp = b;	// b를 양수처럼 사용하려 함
		temp.thesign = true;	// temp = -b > 0 인 셈
		return a + temp;	// a + temp = a + (-b) = a - b;
	}
	// 3번 케이스
	else if (a.thesign == false && b.thesign == true) {
		inf_int temp = b;	// b를 음수처럼 사용하려 함
		temp.thesign = false;	// temp = -b < 0 인 셈

		return a + temp;	// a + temp = a + (-b) = a - b;
	}

	else {
		inf_int result;

		if (b > a) {	// b가 a보다 크다면, a와 b만 바꾼 후 sign = negative
			swap(a, b);
			result.thesign = false;
		}

		// 항상 a가 b보다 더 크다. 길이는 a >= b이다.

		int index_a = a.length - 1, index_b = b.length - 1;
		int borrow = 0;

		while (index_b >= 0) {
			int digit = a.digits[index_a] - b.digits[index_b] + borrow;

			if (digit < 0) {	// 연산 결과가 0보다 작으면 borrow 필요, 연산 결과에 10 더해야 함
				digit = digit + 10;
				borrow = -1;
			}

			else borrow = 0;

			result.digits = (char)digit + result.digits;
			index_a--; index_b--;
		}

		while (index_a >= 0) {
			int digit = a.digits[index_a] + borrow;
			result.digits = (char)digit + result.digits;

			borrow = 0;
			index_a--;
		}

		return result;
	}
}

inf_int operator*(const inf_int& a, const inf_int& b){
	/* 
	1. 부호가 같은 경우
		multiplication 후에 sign positive
	2. 부호가 다른 경우
		multiplication 후에 sign negative
	*/

	inf_int result;

	if (a.thesign == b.thesign) result.thesign = true;
	else result.thesign = false;
	
	int index_a = a.length - 1, index_b = b.length - 1;


}

ostream& operator<<(ostream& o, const inf_int& value) {
	char sign = value.thesign ? '+' : '-';
	o << sign <<  value.digits << endl;

	return o;
}