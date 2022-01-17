#include <iostream>

// Each distict product of a product family must have a base interface 
// All variants of the product must inplement this interface

// Abstruct Product CHAIR
class Chair {
public:
    virtual ~Chair() { }
    virtual std::string sitOn() const  = 0;
};

class ModernChair : public Chair {
public:
    std::string sitOn() const override {
        return "You can sit on MODERN chair\n";
    }
};

class VictorianChair : public Chair {
public:
    std::string sitOn() const override {
        return "You can sit on VICTORIAN chair\n";
    }
};

class ArtDecoChair : public Chair {
public: 
    std::string sitOn() const override {
        return "You can sit on ARTDECO chair\n";
    }
};

// Abstract Product SOFA
// This product can collaborate with the Chair, but
// The Abstract Factory makes sure that all products it creates are of the
// same variant and thus, compatible.
class Sofa {
public:
    virtual ~Sofa() { }
    virtual std::string layOn() const  = 0;
    virtual std::string putAside(const Chair& collaborator) const = 0; 
};

class ModernSofa : public Sofa {
public:
    std::string layOn() const override {
        return "You can lie on MODERN Sofa\n";
    }
    std::string putAside(const Chair& collaboratorChair) const override {
        const std::string result = collaboratorChair.sitOn();
        return "Now you can lie on Modern Sofa and " + result;
    }
};

class VictorianSofa : public Sofa {
public:
    std::string layOn() const override {
        return "You can lie on VICTORIAN Sofa\n";
    }
    std::string putAside(const Chair& collaboratorChair) const override {
        const std::string result = collaboratorChair.sitOn();
        return "Now you can lie on Victorian sofa and " + result;
    }
};

class ArtDecoSofa : public Sofa {
public: 
    std::string layOn() const override {
        return "You can lie on ARTDECO Sofa\n";
    }
    std::string putAside(const Chair& collaboratorChair) const override {
        const std::string result = collaboratorChair.sitOn();
        return "Now you can lie on ArdDeco sofa and " + result;
    }
};

class CoffeeTable {
public:
    virtual ~CoffeeTable() { }
    virtual std::string coffeeOnMe() const = 0;
    virtual std::string sittingOn(const Sofa& collaboratorSofa) const = 0;
};

class ModernCoffeeTable : public CoffeeTable {
public:
    std::string coffeeOnMe() const override {
        return "You're enjoying a cup of coffee on Modern Coffee Table\n";
    }
    std::string sittingOn(const Sofa& collaboratorSofa) const override {
        std::string result = collaboratorSofa.layOn();
        return result + "Enjoy your coffee on Modern Coffee Table\n";
    }
};

class VictorianCoffeeTable : public CoffeeTable {
public:
    std::string coffeeOnMe() const override {
        return "You're enjoying a cup of coffee on Victorian Coffee Table\n";
    }
    std::string sittingOn(const Sofa& collaboratorSofa) const override {
        std::string result = collaboratorSofa.layOn();
        return result + "Enjoy your coffee on Victorian Coffee table\n";
    }
};

class ArtDecoCoffeeTable : public CoffeeTable {
public:
    std::string coffeeOnMe() const override {
        return "You're enjoying a cup of coffee on ArtDeco coffee table\n";
    }
    std::string sittingOn(const Sofa& collaboratorSofa) const override {
        std::string result = collaboratorSofa.layOn();
        return result + "Enjoy your coffee on ArtDeco coffee table\n";
    }
};

// Abstract Factory interface declares a set of methods that return different abstract products
class FurnitureFactory {
public:
    virtual Chair* createChair() const = 0;
    virtual Sofa* createSofa() const = 0;
    virtual CoffeeTable* createCoffeeTable() const = 0;
};

// Concrete Factories produce a family of products that belong to a single variant!
// The factory guarantees that resulting products are compatible. Note
// that signatures of the Concrete Factory's methods return an abstract product,
// while inside the method a concrete product is instantiated.
class ModernFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() const override {
        return new ModernChair;
    }
    Sofa* createSofa() const override {
        return new ModernSofa;
    }
    CoffeeTable* createCoffeeTable() const override {
        return new ModernCoffeeTable;
    }
};

class VictorianFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() const override {
        return new VictorianChair;
    }
    Sofa* createSofa() const override {
        return new VictorianSofa;
    }
    CoffeeTable* createCoffeeTable() const override {
        return new VictorianCoffeeTable;
    }
};

class ArtDecoFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() const override {
        return new ArtDecoChair;
    }
    Sofa* createSofa() const override {
        return new ArtDecoSofa;
    }
    CoffeeTable* createCoffeeTable() const override {
        return new ArtDecoCoffeeTable;
    }
};

void ClientCode(const FurnitureFactory& factory) {
    const Chair* chair = factory.createChair();
    const Sofa* sofa = factory.createSofa();
    const CoffeeTable* coffeetable = factory.createCoffeeTable();
    std::cout<<chair->sitOn();
    std::cout<<sofa->layOn();
    std::cout<<sofa->putAside(*chair);
    std::cout<<coffeetable->coffeeOnMe();
    std::cout<<coffeetable->sittingOn(*sofa);
    delete chair;
    delete sofa;
    delete coffeetable;
}

int main()
{
    std::cout<<"Client's code testing with the Modern Furniture factory\n";
    FurnitureFactory* modernFurnitureFactory = new ModernFurnitureFactory;
    ClientCode(*modernFurnitureFactory);
    delete modernFurnitureFactory;
    std::cout<<"\nTesting Victorian Furniture factory\n";
    FurnitureFactory* victorianFurnitureFactory = new VictorianFurnitureFactory;
    ClientCode(*victorianFurnitureFactory);
    delete victorianFurnitureFactory;
    std::cout<<"\nTesting ArtDeco Furniture factory\n";
    FurnitureFactory* artDecoFurnitureFactory = new ArtDecoFurnitureFactory;
    ClientCode(*artDecoFurnitureFactory);
    delete artDecoFurnitureFactory;
    return 0;
}