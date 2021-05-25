#include<iostream>
#include<array>
#include<QDebug>

class Circle;
class Square;

class Visitor
{
public:
    virtual void VisitCircle(const Circle *element) const = 0;
    virtual void VisitSquare(const Square *elemente) const = 0;
};

class Figure
{
public:
    virtual ~Figure(){};
    virtual void Accept(Visitor *visitor) const = 0;
    virtual double getArea() const = 0;
};

class Circle : public Figure
{
public:
  Circle(double radius)
  {
      _radius = radius;
  }
  void Accept(Visitor *visitor) const override
  {
    visitor->VisitCircle(this);
  }
  double getArea() const override
  {
      return 3.14 * _radius*_radius;
  }
  void setRadius(double radius)
  {
      _radius = radius;
  }
  double getRadius()
  {
      return _radius;
  }
private:
  double _radius;
};

class Square : public Figure
{
public:
    Square(double side)
    {
        _side = side;
    }
    void Accept(Visitor * visitor) const override
    {
        visitor->VisitSquare(this);
    }
    double getArea() const override
    {
        return _side*_side;
    }
    void setSide(double side)
    {
        _side = side;
    }
    double getSide()
    {
        return _side;
    }
private:
    double _side;
};

class ConcreteVisitor1 : public Visitor
{
public:
    void VisitCircle(const Circle *element) const override
    {
        qDebug() << "Circle Area: " << element->getArea();
    }
    void VisitSquare(const Square *element)const override
    {
        qDebug() << "Square Area:" << element->getArea();
    }
};

class ConcreteVisitor2 : public Visitor
{
public:
    void VisitCircle(const Circle *element) const override
    {
        qDebug() << "Circle perimeter:" << ((Circle*)element)->getRadius() * 2 * 3.14;
    }
    void VisitSquare(const Square *element) const override
    {
        qDebug() << "Square perimeter:" << 4 * ((Square*)element)->getSide();
    }
};

void ClientCode(std::array<const Figure*, 4> figures, Visitor *visitor)
{
    for(const Figure *figure : figures)
    {
        figure->Accept(visitor);
    }
}

int main() {
    std::array<const Figure*, 4> figures = {new Circle(3), new Square(5.3), new Circle(0.5), new Square(0.5)};

    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    ClientCode(figures, visitor1);

    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    ClientCode(figures, visitor2);

    for(const Figure *figure : figures)
    {
        delete figure;
    }
    delete visitor1;
    delete visitor2;


    return 0;
}
