#include<iostream>
#include<string>
#include<Windows.h>
#include<time.h>
using namespace std;

class Car {
private:
	int speed;
	int gear;
	string color;
	const int MAX_SPEED;
public:
	Car(int s, int g, string c);
	Car() :MAX_SPEED(200){
		cout << "������ ȣ��" << endl;
		speed = 0;
		gear = 1;
		color = "white";
	}
	~Car() {
		cout << "�Ҹ��� ȣ��" << endl;
	}

	int getSpeed();
	void setSpeed(int s);
	int getGear();
	void setGear(int g);
	string getColor();
	void setColor(string c);

	void speedUp();
	void speedDown();

	void init(int s, int g, string c);
	void show();
};

Car::Car(int s, int g, string c) :speed(s),gear(g),color(c) {
}

int Car::getSpeed() {
	return speed;
}
int Car::getGear() {
	return gear;
}

void Car::setSpeed(int s) {
	speed = s;
}

void Car::setColor(string c) {
	color = c;
}

string Car::getColor() {
	return color;
}

void Car::setGear(int g) {
	gear = g;
}

void Car::speedUp() {
	speed += 10;
}

void Car::speedDown() {
	speed -= 10;
}

void Car::show() {
	cout << "==========" << endl;
	cout << "�ӵ�:" << speed << endl;
	cout << "���:" << gear << endl;
	cout << "����:" << color << endl;
	cout << "==========" << endl;
}
int main()
{
	srand(time(NULL));
	Car car1(rand() % 200, 1, "red"), car2(rand() % 200, 1, "red");
	Car* a = new Car();
	car1.show();
	car2.show();

	if (car1.getSpeed() > car2.getSpeed()) {
		cout << "car1�� �¸���" << endl;
	}
	else {
		cout << "car2�� �¸���" << endl;
	}

	return 0;
}