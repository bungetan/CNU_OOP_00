#include <iostream>

class SetValue {
	int x, y;
public :
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
};

void SetValue::setX(int n) {
	x = n;
}

void SetValue::setY(int n) {
	y = n;
}

int SetValue::getX() {
	return x;
}

int SetValue::getY() {
	return y;
}

int main() {
	SetValue obj;
	obj.setX(33);
	obj.setY(44);

	std::cout << "X = " << obj.getX() << " ,Y = " << obj.getY() 
	<< std::endl;
	return 0;
}