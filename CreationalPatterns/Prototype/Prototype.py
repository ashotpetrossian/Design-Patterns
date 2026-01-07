from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def clone(self) -> "Shape":
        pass
    
class Circle(Shape):
    def __init__(self, radius: float) -> None:
        self.radius = radius
        
    def clone(self) -> "Circle":
        return Circle(self.radius)
    
if __name__ == '__main__':
    s1: Shape = Circle(1.05)
    s2 = s1.clone()    
    