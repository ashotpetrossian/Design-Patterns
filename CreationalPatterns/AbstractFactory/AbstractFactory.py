from abc import ABC, abstractmethod

# =========================
# Abstract Products
# =========================

class Window(ABC):
    @abstractmethod
    def render(self) -> str:
        pass


class Button(ABC):
    @abstractmethod
    def render(self) -> str:
        pass

    @abstractmethod
    def click_inside(self, window: Window) -> str:
        pass

# =========================
# Concrete Products
# =========================

class WindowsWindow(Window):
    def render(self) -> str:
        return "Rendering a Windows-style window."


class MacWindow(Window):
    def render(self) -> str:
        return "Rendering a macOS-style window."


class WindowsButton(Button):
    def render(self) -> str:
        return "Rendering a Windows-style button."

    def click_inside(self, window: Window) -> str:
        return f"WindowsButton clicked inside → ({window.render()})"


class MacButton(Button):
    def render(self) -> str:
        return "Rendering a macOS-style button."

    def click_inside(self, window: Window) -> str:
        return f"MacButton clicked inside → ({window.render()})"

# =========================
# Abstract Factory
# =========================

class GuiFactory(ABC):
    @abstractmethod
    def create_window(self) -> Window:
        pass

    @abstractmethod
    def create_button(self) -> Button:
        pass

# =========================
# Concrete Factories
# =========================

class WindowsGuiFactory(GuiFactory):
    def create_window(self) -> Window:
        return WindowsWindow()

    def create_button(self) -> Button:
        return WindowsButton()


class MacGuiFactory(GuiFactory):
    def create_window(self) -> Window:
        return MacWindow()

    def create_button(self) -> Button:
        return MacButton()

# =========================
# Client code
# =========================

def run_gui(factory: GuiFactory) -> None:
    window = factory.create_window()
    button = factory.create_button()

    print(window.render())
    print(button.render())
    print(button.click_inside(window))

# =========================
# Main execution
# =========================

if __name__ == "__main__":
    print("Running GUI with Windows style:")
    run_gui(WindowsGuiFactory())

    print("\nRunning GUI with macOS style:")
    run_gui(MacGuiFactory())
