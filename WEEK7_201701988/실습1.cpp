#include <iostream>
#include <stdexcept>
class Test {
public:
	Test(char id) : id_(id) {}
	~Test() {
		std::cout << "Destructor execution: "
			<< id_ << std::endl;
	}
private:
	char id_;
};
int funcB() {
	Test r('B');
	throw std::runtime_error("Exception from funcB!\n");
	std::cout << "Executed in B" << std::endl;
	return 0;
}
int funcA() {
	Test r('A');
	funcB();
	std::cout << "Executed in A" << std::endl;
	return 0;
}
int main() {
	try {
		funcA();
	}
	catch (std::exception& e) {
		std::cout << "Exception : " << e.what();
	}
}
/* (실습 1-1) 분석결과:
	main 함수에서 funcA를 호출하면 Test r('A') 객체가 생성이 되며 funcB를 호출한다.
	Test r('B') 객체가 생성되며 "Executed in B" 문구가 출력된다.
	funcB 함수가 종료되기 때문에 Test r('B') 객체가 소멸되어 소멸자를 호출한다.
	"Destructor execution : B" 문구가 출력된다.
	funcA로 복귀하여 "Executed in A" 문구가 출력된 후 funcA 함수가 종료되어 Test r('A') 객체가 소멸된다.
	"Destructor execution : A" 문구가 출력되며 프로그램이 종료한다.
	

*/
/* (실습 1-2) 분석결과 :	main 함수에서 funcA를 호출하면 Test r('A') 객체가 생성이 되며 funcB를 호출한다.
	Test r('B') 객체가 생성된 후 runtime_error가 발생되며 funcB 함수가 종료된다
	따라서 Test r('B') 객체가 소멸되어 소멸자를 호출하기 매눈에 "Destructor execution : B" 문구가 출력된다.
	에러로 인해 funcA 함수도 종료되어 Test r('A') 객체가 소멸된다.	"Destructor execution : A" 문구가 출력된다.	발생한 runtime_error는 Stack Unwinding 과정을 통해 main의 Exception Handler에서 처리되며 	"Exception : Exception from funcB!" 문구가 출력된 후 프로그램이 종료한다.	*/