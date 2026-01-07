/*
 * Prototype Design Pattern
 * ------------------------
 * Purpose:
 *   The Prototype pattern allows creating new objects by copying an existing object
 *   (the "prototype") rather than constructing from scratch. This is useful when
 *   object creation is expensive or when you need to duplicate objects polymorphically.
 *
 * Key Idea:
 *   - Define a common interface (Shape) with a virtual clone() method.
 *   - Each concrete class (e.g., Circle) implements clone() to return a new copy
 *     of itself.
 *   - Clients use clone() to create copies without knowing the concrete class.
 *
 * Advantages:
 *   - Avoids repetitive initialization code.
 *   - Supports polymorphic object duplication.
 *   - Simplifies creation of complex objects or object graphs.
 *
 * Example Usage:
 *   std::unique_ptr<Shape> s1 = std::make_unique<Circle>(1.05);
 *   auto s2 = s1->clone(); // Creates a new Circle with the same radius
 */


#include <iostream>
#include <string>
#include <memory>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;
protected:
    std::string _name;
};

class Circle : public Shape
{
public:
    explicit Circle(float rad) : _radius{rad} { }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
private:
    float _radius{};
};

int main()
{
    std::unique_ptr<Shape> s1 = std::make_unique<Circle>(1.05);
    auto s2 = s1->clone();
}