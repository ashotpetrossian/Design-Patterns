/**
 * @file SandwichBuilder.cpp
 * @brief Example of the Builder design pattern in C++.
 *
 * This example demonstrates the Builder pattern, which separates the construction
 * of a complex object (Sandwich) from its representation. Different builders
 * (Veg, Chicken, Beef) construct different types of sandwiches step by step.
 * The Director controls the building process using a Builder interface, allowing
 * clients to obtain the finished Sandwich without knowing the construction details.
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>

/**
 * @class Sandwich
 * @brief The Product class representing a sandwich.
 */
class Sandwich
{
public:
    /// List all the parts of the sandwich
    void listParts()
    {
        for (const auto& part : parts) {
            std::cout << part << std::endl;
        }
    }

    /// Add a part to the sandwich
    void addPart(std::string part)
    {
        parts.push_back(std::move(part));
    }

private:
    std::vector<std::string> parts; ///< List of sandwich parts
};

/**
 * @class Builder
 * @brief Abstract Builder interface defining steps to build a sandwich.
 */
class Builder
{
public:
    virtual ~Builder() = default;
    virtual void makeBread() = 0;
    virtual void makeSauce() = 0;
    virtual void makeIngredients() = 0;
};

/**
 * @class VegSandwichBuilder
 * @brief Concrete Builder for a vegetarian sandwich.
 */
class VegSandwichBuilder : public Builder
{
public:
    VegSandwichBuilder() { reset(); }
    ~VegSandwichBuilder() = default;

    /// Reset the internal sandwich object
    void reset() {
        sandwich = std::make_unique<Sandwich>();
    }

    /// Return the finished sandwich
    std::unique_ptr<Sandwich> getProduct() {
        auto res{std::move(sandwich)};
        reset();
        return res;
    }

    void makeBread() override
    {
        sandwich->addPart("Whole Grain Bread");
    }

    void makeSauce() override 
    {
        sandwich->addPart("Low Calories Hummus");
    }

    void makeIngredients() override
    {
        sandwich->addPart("Mozzarella, Tomatoes, Cucumber, Lettuce");
    }
private:
    std::unique_ptr<Sandwich> sandwich;
};

/**
 * @class Director
 * @brief Director class that constructs a sandwich using a builder.
 */
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

/**
 * @class ChickenBurgerBuilder
 * @brief Concrete Builder for a chicken burger.
 */
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

/**
 * @class BeefBurgerBuilder
 * @brief Concrete Builder for a beef burger.
 */
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

/**
 * @brief Client code demonstrating the Builder pattern with different sandwiches
 */
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
