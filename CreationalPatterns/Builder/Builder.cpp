#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Sandwich
{
public:
    void listParts()
    {
        for (const auto& part : parts) {
            std::cout << part << std::endl;
        }
    }

    void addPart(std::string part)
    {
        parts.push_back(std::move(part));
    }

private:
    std::vector<std::string> parts;
};

class Builder
{
public:
    virtual ~Builder() = default;
    virtual void makeBread() = 0;
    virtual void makeSauce() = 0;
    virtual void makeIngredients() = 0;
};

class VegSandwichBuilder : public Builder
{
public:
    VegSandwichBuilder() { reset(); }
    ~VegSandwichBuilder() = default;

    void reset() {
        sandwich = std::make_unique<Sandwich>();
    }

    std::unique_ptr<Sandwich> getProduct() {
        auto res{std::move(sandwich)};
        reset();
        return res;
    }

    void makeBread() override
    {
        sandwich->addPart("Non-Gluten Bread");
    }

    void makeSauce() override 
    {
        sandwich->addPart("Low Callories Sause");
    }

    void makeIngredients() override
    {
        sandwich->addPart("Low Fat Mozarella, Tomatoes and Basil");
    }
private:
    std::unique_ptr<Sandwich> sandwich;
};

class Director
{
public:
    void setBuilder(Builder* b) {
        builder = b;
    }

    void buildProduct()
    {
        if (!builder) throw std::runtime_error("Builder is not set");

        builder->makeBread();
        builder->makeSauce();
        builder->makeIngredients();
    }
private:
    Builder* builder{nullptr};
};

class ChickenBurgerBuilder : public Builder {
public:
    ChickenBurgerBuilder() { reset(); }

    void reset() { sandwich = std::make_unique<Sandwich>(); }

    std::unique_ptr<Sandwich> getProduct() {
        auto res = std::move(sandwich);
        reset();
        return res;
    }

    void makeBread() override {
        sandwich->addPart("Sesame Bun");
    }

    void makeSauce() override {
        sandwich->addPart("Spicy Mayo");
    }

    void makeIngredients() override {
        sandwich->addPart("Grilled Chicken, Lettuce, Tomato");
    }

private:
    std::unique_ptr<Sandwich> sandwich;
};

class BeefBurgerBuilder : public Builder {
public:
    BeefBurgerBuilder() { reset(); }

    void reset() { sandwich = std::make_unique<Sandwich>(); }

    std::unique_ptr<Sandwich> getProduct() {
        auto res = std::move(sandwich);
        reset();
        return res;
    }

    void makeBread() override {
        sandwich->addPart("Classic Bun");
    }

    void makeSauce() override {
        sandwich->addPart("BBQ Sauce");
    }

    void makeIngredients() override {
        sandwich->addPart("Beef Patty, Cheddar, Pickles, Onion");
    }

private:
    std::unique_ptr<Sandwich> sandwich;
};


void clientSide() {
    Director director;

    // Veg Sandwich
    VegSandwichBuilder vegBuilder;
    director.setBuilder(&vegBuilder);
    director.buildProduct();
    auto vegSandwich = vegBuilder.getProduct();
    std::cout << "Veg Sandwich:\n";
    vegSandwich->listParts();
    std::cout << std::endl;

    // Chicken Burger
    ChickenBurgerBuilder chickenBuilder;
    director.setBuilder(&chickenBuilder);
    director.buildProduct();
    auto chickenBurger = chickenBuilder.getProduct();
    std::cout << "Chicken Burger:\n";
    chickenBurger->listParts();
    std::cout << std::endl;

    // Beef Burger
    BeefBurgerBuilder beefBuilder;
    director.setBuilder(&beefBuilder);
    director.buildProduct();
    auto beefBurger = beefBuilder.getProduct();
    std::cout << "Beef Burger:\n";
    beefBurger->listParts();
    std::cout << std::endl;
}


int main()
{
    clientSide();
}