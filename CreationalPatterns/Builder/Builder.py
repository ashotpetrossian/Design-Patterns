from abc import ABC, abstractmethod
from typing import List

# ---------- Product ----------
class Sandwich:
    def __init__(self) -> None:
        self.parts: List[str] = []

    def add_part(self, part: str) -> None:
        self.parts.append(part)

    def list_parts(self) -> None:
        for part in self.parts:
            print(part)

# ---------- Builder ----------
class Builder(ABC):
    @abstractmethod
    def make_bread(self) -> None:
        pass

    @abstractmethod
    def make_sauce(self) -> None:
        pass

    @abstractmethod
    def make_ingredients(self) -> None:
        pass

# ---------- Concrete Builders ----------
class VegSandwichBuilder(Builder):
    def __init__(self) -> None:
        self.reset()

    def reset(self) -> None:
        self.sandwich = Sandwich()

    def get_product(self) -> Sandwich:
        product = self.sandwich
        self.reset()
        return product

    def make_bread(self) -> None:
        self.sandwich.add_part("Non-Gluten Bread")

    def make_sauce(self) -> None:
        self.sandwich.add_part("Low Calories Sauce")

    def make_ingredients(self) -> None:
        self.sandwich.add_part("Mozzarella, Tomatoes, Basil")

class ChickenBurgerBuilder(Builder):
    def __init__(self) -> None:
        self.reset()

    def reset(self) -> None:
        self.sandwich = Sandwich()

    def get_product(self) -> Sandwich:
        product = self.sandwich
        self.reset()
        return product

    def make_bread(self) -> None:
        self.sandwich.add_part("Sesame Bun")

    def make_sauce(self) -> None:
        self.sandwich.add_part("Spicy Mayo")

    def make_ingredients(self) -> None:
        self.sandwich.add_part("Grilled Chicken, Lettuce, Tomato")

class BeefBurgerBuilder(Builder):
    def __init__(self) -> None:
        self.reset()

    def reset(self) -> None:
        self.sandwich = Sandwich()

    def get_product(self) -> Sandwich:
        product = self.sandwich
        self.reset()
        return product

    def make_bread(self) -> None:
        self.sandwich.add_part("Classic Bun")

    def make_sauce(self) -> None:
        self.sandwich.add_part("BBQ Sauce")

    def make_ingredients(self) -> None:
        self.sandwich.add_part("Beef Patty, Cheddar, Pickles, Onion")

# ---------- Director ----------
class Director:
    def __init__(self) -> None:
        self.builder: Builder | None = None

    def set_builder(self, builder: Builder) -> None:
        self.builder = builder

    def build_product(self) -> None:
        if self.builder is None:
            raise RuntimeError("Builder is not set")
        self.builder.make_bread()
        self.builder.make_sauce()
        self.builder.make_ingredients()

# ---------- Client ----------
def client_side() -> None:
    director = Director()

    # Veg Sandwich
    veg_builder = VegSandwichBuilder()
    director.set_builder(veg_builder)
    director.build_product()
    veg_sandwich = veg_builder.get_product()
    print("Veg Sandwich:")
    veg_sandwich.list_parts()
    print()

    # Chicken Burger
    chicken_builder = ChickenBurgerBuilder()
    director.set_builder(chicken_builder)
    director.build_product()
    chicken_burger = chicken_builder.get_product()
    print("Chicken Burger:")
    chicken_burger.list_parts()
    print()

    # Beef Burger
    beef_builder = BeefBurgerBuilder()
    director.set_builder(beef_builder)
    director.build_product()
    beef_burger = beef_builder.get_product()
    print("Beef Burger:")
    beef_burger.list_parts()
    print()

if __name__ == "__main__":
    client_side()
