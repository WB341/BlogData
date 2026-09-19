// #include <cmath>：引入 cmath 头文件，提供 sqrt()（平方根）等数学函数。
#include<cmath>
// #include <iostream>：引入输入输出流，支持 cin / cout。
#include<iostream>
// #define PI 3.1415926：定义一个常量 PI，方便后面计算圆的面积和周长。
#define PI 3.1415926

// 这是一个演示“多态”和“工厂模式”的 C++ 程序。
// 通过不同的图形类，统一使用 area() 和 perimeter() 这两个接口。

// class：定义一个类，表示“图形”这个抽象概念。
// Shape 是基类（父类），后面所有图形都继承它。
class Shape {
 public:
    // virtual：声明虚函数，允许子类重写，实现多态。
    // = 0：这是纯虚函数，表示这个函数必须由子类实现。
    virtual float area()=0;
    // perimeter()：计算周长，所有图形都需要这个功能。
    virtual float perimeter()=0; 
    // virtual ~Shape(){}：虚析构函数，确保释放对象时不会出错。
    virtual ~Shape(){};

};


// class Rectangle：定义长方形类，继承自 Shape。
// 它专门负责计算长方形的面积和周长。
class Rectangle:public Shape{
private:
    // width：长方形的宽
    float width;
    // height：长方形的高
    float height;     
public:
    // area()：重写父类的方法，返回面积。
    virtual float area(){
        // 矩形面积 = 长 × 宽
        return width*height;
    }
    // perimeter()：重写父类的方法，返回周长。
    virtual float perimeter(){
        // 矩形周长 = 2 × (长 + 宽)
        return 2*(width+height);
    }
    // Rectangle(float width,float height)：构造函数，用来初始化对象。
    Rectangle(float width,float height)
    {
        // this->width：当前对象的 width；等号右边是传入参数。
        this->width = width;
        this->height = height;
    }
};

// class Circle：定义圆类，继承自 Shape。
// 它专门负责计算圆的面积和周长。
class Circle:public Shape{
private:
    // m_r：圆的半径
    float m_r;
public:
    // Circle(float r)：构造函数，初始化半径。
    Circle(float r) {
        m_r = r;
    }
    // area()：计算圆面积，公式 = πr²
    virtual float area(){
        return PI*m_r*m_r;    
    }
    // perimeter()：计算圆周长，公式 = 2πr
    virtual float perimeter(){
        return 2*PI*m_r;
    }
};

// class triangle：定义三角形类，继承自 Shape。
// 注意：类名小写 t，后面用 triangle 作为类名。
class triangle:public Shape{
private:
    // a、b、c：三角形三条边的长度
    float a;
    float b;
    float c;
public:
    // area()：计算三角形面积。
    virtual float area(){
        // p 是半周长，公式是 (a+b+c)/2
        float p = (a+b+c)/2;
        // sqrt() 是平方根函数，来自 <cmath>
        // 海伦公式：面积 = sqrt(p*(p-a)*(p-b)*(p-c))
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
    // perimeter()：计算三角形周长。
    virtual float perimeter(){
        return a+b+c;
    }
    // triangle(float a,float b,float c)：构造函数，初始化三边。
    triangle(float a,float b,float c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
}; 


// class ShapeGenerator：定义抽象生成器基类。
// 作用：规定“生成图形对象”的统一接口。
class ShapeGenerator{
public:
    // generate()：纯虚函数，告诉所有子类必须实现生成对象的方法。
    virtual Shape* generate()=0;
};

// RectangleGenerator：长方形生成器，继承自 ShapeGenerator。
class RectangleGenerator:public ShapeGenerator{
public:
    // generate()：让用户输入长方形数据，并返回一个 Rectangle 对象。
    virtual Shape* generate(){
        // width、height：用户输入的长方形长和宽
        float width,height;
        // std::cout：标准输出流，用于输出提示语。
        std::cout<<"Please input the width and height of the rectangle:"<<std::endl;
        // std::cin：标准输入流，用于读取用户输入。
        std::cin>>width>>height;
        // new：在堆区动态创建对象。返回一个 Rectangle 指针。
        return new Rectangle(width,height);
    }
};

// CircleGenerator：圆形生成器，继承自 ShapeGenerator。
class CircleGenerator:public ShapeGenerator{
public:
    // generate()：让用户输入半径，并返回一个 Circle 对象。
    virtual Shape* generate(){
        // r：半径
        float r;
        std::cout<<"Please input the radius of the circle:"<<std::endl;
        std::cin>>r;
        // new Circle(r)：动态创建圆对象
        return new Circle(r);
    }
 };

 // TriangleGenerator：三角形生成器，继承自 ShapeGenerator。
 class TriangleGenerator:public ShapeGenerator{
 public:
    // generate()：让用户输入三角形三边，并返回一个 triangle 对象。
    virtual Shape* generate(){
        // a、b、c：三角形三边
        float a,b,c;
        std::cout<<"Please input the three sides of the triangle:"<<std::endl;
        std::cin>>a>>b>>c;
        // new triangle(a,b,c)：动态创建三角形对象
        return new triangle(a,b,c);
    }
 };



// int main()：C++ 程序的主函数，程序从这里开始运行。
 int main(){
    // ShapeGenerator* generator：定义一个“生成器指针”，用于指向不同的生成器对象。
    ShapeGenerator* generator;
    // choice：用户选择的图形编号
    int choice;
    // 输出菜单，让用户选择要生成哪种图形
    std::cout<<"Please choose the shape to generate:"<<std::endl;
    std::cout<<"1. Rectangle"<<std::endl;
    std::cout<<"2. Circle"<<std::endl;
    std::cout<<"3. Triangle"<<std::endl;
    // 读取用户选择的编号
    std::cin>>choice;
    // switch：根据 choice 分支执行不同的代码。
    switch(choice){
        case 1:
            // 选择长方形生成器
            generator = new RectangleGenerator();
            break;
        case 2:
            // 选择圆形生成器
            generator = new CircleGenerator();
            break;
        case 3:
            // 选择三角形生成器
            generator = new TriangleGenerator();
            break;
        default:
            // 输入错误时输出提示并退出程序
            std::cout<<"Invalid choice!"<<std::endl;
            return 0;
    }
    // shape：指向具体图形对象的指针，使用统一的 Shape 接口来调用面积和周长。
    Shape* shape = generator->generate();
    // 输出面积
    std::cout<<"Area: "<<shape->area()<<std::endl;
    // 输出周长
    std::cout<<"Perimeter: "<<shape->perimeter()<<std::endl;
    // delete：释放堆区内存，避免内存泄漏
    delete shape;
    delete generator;
    // return 0：程序正常结束
    return 0;
 }