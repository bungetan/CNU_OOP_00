#include <iostream>

//Ŭ������ ĸ��ȭ 
class SetValue {
public:
	int x, y;
};

int main() {
	SetValue obj;
	obj.x = 33;
	obj.y = 44;

	std::cout << "X = " << obj.x << " ,Y = " << obj.y << std::endl;
	return 0;
}