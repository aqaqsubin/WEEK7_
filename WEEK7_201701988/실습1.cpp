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
/* (�ǽ� 1-1) �м����:
	main �Լ����� funcA�� ȣ���ϸ� Test r('A') ��ü�� ������ �Ǹ� funcB�� ȣ���Ѵ�.
	Test r('B') ��ü�� �����Ǹ� "Executed in B" ������ ��µȴ�.
	funcB �Լ��� ����Ǳ� ������ Test r('B') ��ü�� �Ҹ�Ǿ� �Ҹ��ڸ� ȣ���Ѵ�.
	"Destructor execution : B" ������ ��µȴ�.
	funcA�� �����Ͽ� "Executed in A" ������ ��µ� �� funcA �Լ��� ����Ǿ� Test r('A') ��ü�� �Ҹ�ȴ�.
	"Destructor execution : A" ������ ��µǸ� ���α׷��� �����Ѵ�.
	

*/
/* (�ǽ� 1-2) �м���� :	main �Լ����� funcA�� ȣ���ϸ� Test r('A') ��ü�� ������ �Ǹ� funcB�� ȣ���Ѵ�.
	Test r('B') ��ü�� ������ �� runtime_error�� �߻��Ǹ� funcB �Լ��� ����ȴ�
	���� Test r('B') ��ü�� �Ҹ�Ǿ� �Ҹ��ڸ� ȣ���ϱ� �Ŵ��� "Destructor execution : B" ������ ��µȴ�.
	������ ���� funcA �Լ��� ����Ǿ� Test r('A') ��ü�� �Ҹ�ȴ�.	"Destructor execution : A" ������ ��µȴ�.	�߻��� runtime_error�� Stack Unwinding ������ ���� main�� Exception Handler���� ó���Ǹ� 	"Exception : Exception from funcB!" ������ ��µ� �� ���α׷��� �����Ѵ�.	*/