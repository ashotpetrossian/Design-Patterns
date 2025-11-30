import abc
import typing

class Logger(abc.ABC):
    @abc.abstractmethod
    def log(self, message: str) -> None:
        pass
        
class FileLogger(Logger):
    def log(self, message: str):
        print(f"[File] {message}")
        
class ConsoleLogger(Logger):
    def log(self, message: str):
        print(f"[Console] {message}")
        

class LoggerCreator(abc.ABC):
    @abc.abstractmethod
    def factory_method(self) -> Logger:
        pass
    
    def log_something(self):
        self.factory_method().log("Hello World")

class FileLoggerCreator(LoggerCreator):
    def factory_method(self) -> Logger:
        return FileLogger()
    
class ConsoleLoggerCreator(LoggerCreator):
    def factory_method(self) -> Logger:
        return ConsoleLogger()
    
def client_code(creator: LoggerCreator) -> None:
    creator.log_something()
    
if __name__ == "__main__":
    file_creator = FileLoggerCreator()
    console_creator = ConsoleLoggerCreator()
    
    client_code(file_creator)
    client_code(console_creator)