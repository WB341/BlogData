#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    int positionX;
    int positionY;

private:
    string shapeName;

public:
    int publicNumber;

    virtual float area() {
        return 0.0f;
    }

    void setName(string name) {
        shapeName = name;
    }

    void draw() {
        cout << "我不知道怎么画" << endl;
    }
};

const float PI = 3.1415926f;

class Circle : public Shape {
private:
    float radius;

public:
    Circle(float r = 0.0f) : radius(r) {
        positionX = 0;
        positionY = 0;
    }

    void draw() {
        cout << "半径为：" << radius << endl;
        cout << "圆心为(" << positionX << ", " << positionY << ")" << endl;
        cout << "publicNumber = " << publicNumber << endl;
    }

    float area() override {
        return PI * radius * radius;
    }
};

class BaseClass {
public:
    virtual void greet() {
        cout << "这是基类" << endl;
    }
};

class SubClass : public BaseClass {
public:
    void greet() override {
        cout << "这是子类" << endl;
    }
};

int main() {
    Circle c(5.0f);
    c.publicNumber = 10;
    cout << "面积：" << c.area() << endl;
    c.draw();

    SubClass obj;
    BaseClass* pBase = &obj;
    BaseClass& refBase = obj;

    obj.greet();
    pBase->greet();
    refBase.greet();
    return 0;
}
