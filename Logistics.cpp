#include <iostream>

//The Transport interface declares the "deliver" operation that all contrete Transport must implement
class Transport {
public:
    virtual ~Transport() { }
    virtual std::string deliver() const = 0;
};

//Concrete Products(Transports) provide various implementation of Product(Transport) interface
class Truck : public Transport {
public:
    std::string deliver() const override {
        return "Delivering via Truck\n";
    }
};

class Ship : public Transport {
public: 
    std::string deliver() const override {
        return "Delivering via Ship\n";
    }
};

//The Creator(Logistics) class declares factory method that is supposed to to
//return an object of Product(Transport) class. The Creator's(Logistics) subclasses
//provide the implementation of this method
class Logistics {
public: 
    virtual ~Logistics() { }
    virtual Transport* createTransport() const = 0; // Factory Method
    std::string planDelivery() const {
        //calling Facotry Method to create a Product object
        Transport* transport = this->createTransport();
        std::string result = "The order is " + transport->deliver();
        delete transport;
        return result;
    }
    //other usefull functions for Logistics
};

//Concrete Logistics override the factory method in order to change the delivery type
class RoadLogistics : public Logistics {
public:
    Transport* createTransport() const override {
        return new Truck;
    }
};

class ShipLogistics : public Logistics {
public:
    Transport* createTransport() const override {
        return new Ship;
    }
};

//Client is not aware of the Logistics class        
void ClientCode(const Logistics& logictics) {
    std::cout<<logictics.planDelivery();
}

int main()
{
    Logistics* logistics = new RoadLogistics;
    std::cout<<logistics->planDelivery();
    Logistics* logistics2 = new ShipLogistics;
    std::cout<<logistics2->planDelivery();

    std::cout<<"\nIn Client Code\n";
    ClientCode(*logistics);
    ClientCode(*logistics2);

    delete logistics;
    delete logistics2;
    return 0;
}