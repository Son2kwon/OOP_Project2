#include "inf_int.h"
#include<string>
using namespace std;

/* default constructor는 0으로 설정 */ 
inf_int::inf_int() {
	digits = '0';
	length = 1;
	thesign = true; // 0은 양수로 가정
}

/* 사용자 지정 constructor, 매개변수로 정수가 들어왔을 때 */ 
inf_int::inf_int(int integer) {
	digits = to_string(integer);
	length = digits.length();
	thesign = (integer >= 0) ? true : false; // a가 0보다 작거나 크면 true, 작으면 false
}

/* 사용자 지정 constructor, 매개변수로 string이 들어왔을 때 */
inf_int::inf_int(const string str) {
	digits = str;
	length = digits.length();
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
inf_int& inf_int::operator=(const inf_int& other){
	inf_int ret_value;
	ret_value.digits = other.digits;
	ret_value.length = other.length;
	ret_value.thesign = other.thesign;

	return ret_value;
}

bool operator==(const inf_int& a, const inf_int& b){
	if(a.digits == b.digits) return true;
	
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b){
	if(a.digits == b.digits) return false;
	
	return true;
}

bool operator>(const inf_int& a, const inf_int& b){
	if (a.length != b.length) return a.length > b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 큰 정수

	else { // 길이가 같다면...
		int length = a.length;
		for (int i = 0; i < length; i++) {
			if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
			else return (a.digits[i] - '0') > (b.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
		}

		return false;
	}
}

bool operator<(const inf_int& a, const inf_int& b){
	if (a.length != b.length) return a.length < b.length; // 길이가 다르다면, 길이가 더 긴 것이 더 큰 정수

	else { // 길이가 같다면...
		int length = b.length;
		for (int i = 0; i < length; i++) {
			if ((a.digits[i] - '0') == (b.digits[0] - '0')) continue; // 숫자가 같다면 다음 자리 비교
			else return (b.digits[i] - '0') > (a.digits[i] - '0'); // 숫자가 다르다면 비교한 후 return
		}

		return false;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b){
	/*
	각 문자열의 마지막 index(1의 자리)부터 차례대로 옮겨가며 계산함
	carry가 생긴다면, 다음 자릿수 계산할 때 더할 것
		carry는 1이 최대
	char를 int로 바꿔 계산 후 char형 변수 digit에 저장
	result.digit의 앞에 붙여주는 형태로 덧셈
	가장 마지막 자리 계산에서 carry가 발생하면 추가적으로 1을 붙여줌
	*/

	inf_int result; // 결과 class
	result.digits = '\0'; // 문자열의 마지막에 null을 미리 넣어줌

	int index_a = a.length - 1, index_b = b.length - 1;
	int carry = 0;

	while(index_a >= 0 && index_b >= 0) { // 둘 중 하나라도 끝날 때까지
		int int_a = a.digits[index_a] - '0'; // 자릿수를 int형으로
		int int_b = b.digits[index_b] - '0';

		if(carry + int_a + int_b >= 10) { // carry까지 고려했을 때, 최대값은 19
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
		if(carry + int_a >= 10){
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
		if(carry + int_b >= 10){
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
	
	return result;
}

inf_int operator-(const inf_int& a, const inf_int& b){

}

inf_int operator*(const inf_int& a, const inf_int& b){

}

ostream& operator<<(ostream& o, const inf_int& value) {
	o << value.digits << endl;

	return o;
}