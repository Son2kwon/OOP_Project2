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

/* Assign 연산자 overloading*/
inf_int& inf_int::operator=(const inf_int& other){
	digits = other.digits;
	length = other.length;
	thesign = other.thesign;
}

/* 비교 연산자 overloading */
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
	inf_int result; // 결과 class

	int index_a = a.length, index_b = b.length;
	int carry = 0;

	while(index_a >= 0 && index_b >= 0) { // 둘 중 하나라도 끝날 때까지
		int int_a = a.digits[index_a] - '0'; // 자릿수를 int형으로
		int int_b = b.digits[index_b] - '0';

		if(carry + int_a + int_b >= 10) { // carry까지 고려했을 때, 최대값은 19
			result.digits[index_a] = (carry + int_a + int_b - 10) + '0';
			carry = 1;
		}
		
		else {
			result.digits[index_a] = (carry + int_a + int_b) + '0';
			carry = 0;
		}
		index_a--; index_b--; // 다음 자릿수 계산
	}

	while (index_a >= 0) { //만약 b가 끝났다면,
		int int_a = a.digits[index_a] - '0';
		if(carry + int_a >= 10){
			result.digits[index_a] = (carry + int_a - 10) + '0';
			carry = 1; 
		}

		else {
			result.digits[index_a] = carry + int_a; // 혹시 마지막 계산에서 carry가 있었을 수도 있으니 포함해서 계산
			index_a--;
			carry = 0; 
		}
	}

	while (index_b >= 0) {
		int int_b = b.digits[index_b] - '0';
		if(carry + int_b >= 10){
			result.digits[index_b] = (carry + int_b - 10) + '0';
			carry = 1; 
		}

		else {
			result.digits[index_b] = carry + int_b; // 혹시 마지막 계산에서 carry가 있었을 수도 있으니 포함해서 계산
			index_b--;
			carry = 0; 
		}
	}

	if(carry == 1) result.digits = '1' + result.digits;
	
	return result;
}

inf_int operator-(const inf_int& a, const inf_int& b){

}

inf_int operator*(const inf_int& a, const inf_int& b){

}