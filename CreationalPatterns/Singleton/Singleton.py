"""
Singleton Pattern in Python using a Metaclass (thread-safe).

- The Singleton pattern ensures that a class has only one instance
  and provides a global point of access to it.

- This implementation uses a metaclass to control instance creation:
  the metaclass's __call__ method ensures only one instance is created.

- Thread-safety is guaranteed using a class-level threading.Lock. 
  Even if multiple threads attempt to create the singleton simultaneously,
  only the first thread will initialize it, others will get the same instance.

- Initialization arguments (e.g., 'value') are only applied on the first creation.
  Subsequent calls with different arguments will return the same instance with the
  first value.

Pros:
- Guarantees single instance
- Thread-safe

Cons:
- Slightly more complex than simpler singleton implementations
- First initialization argument is fixed; later calls cannot modify it

"""

import threading
from typing import Any

class SingletonMeta(type):
    instances_ = {}
    lock_ = threading.Lock() # type: ignore
    
    def __call__(cls, *args: Any, **kwargs: Any) -> Any:
        with cls.lock_:
            if cls not in cls.instances_:
                instance = super().__call__(*args, **kwargs)
                cls.instances_[cls] = instance
            return cls.instances_[cls]
    
class Singleton(metaclass=SingletonMeta):
    def __init__(self, value: str):
        self.value = value
        
    def some_logic(self):
        pass
    
def thread_foo():
    s = Singleton("foo")
    print(f"Thread foo: {s.value}, id: {id(s)}")
    
def thread_bar():
    s = Singleton("bar")
    print(f"Thread bar: {s.value}, id: {id(s)}")

if __name__ == "__main__":
    t1 = threading.Thread(target=thread_foo)
    t2 = threading.Thread(target=thread_bar)
    
    t1.start()
    t2.start()
    
    t1.join()
    t2.join()