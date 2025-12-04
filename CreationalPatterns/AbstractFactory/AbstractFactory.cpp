/**
 * @file GuiAbstractFactory.cpp
 * @brief Demonstrates the Abstract Factory design pattern with a GUI example.
 *
 * This example shows a GUI toolkit that can create platform-specific windows and buttons
 * using an abstract factory. The pattern ensures that products from the same factory
 * are compatible and can collaborate correctly. Concrete factories include WindowsGuiFactory
 * and MacGuiFactory, each producing Windows-style or macOS-style components.
 *
 * Key concepts:
 * - Abstract Product: Window, Button
 * - Concrete Product: WindowsWindow, MacWindow, WindowsButton, MacButton
 * - Abstract Factory: GuiFactory
 * - Concrete Factory: WindowsGuiFactory, MacGuiFactory
 * - Client: runGui function, which works with products only through abstract interfaces
 *
 * Modern C++ features:
 * - std::unique_ptr for automatic memory management
 * - RAII for safe resource handling
 * - Polymorphism with virtual functions and vtables
 *
 * Usage:
 * The client code can accept any GuiFactory-derived instance and use it to create and
 * interact with platform-consistent GUI components without knowing their concrete types.
 */


#include <iostream>
#include <memory>

/**
 * Base interface for a window in a GUI toolkit.
 */
class Window {
public:
    virtual ~Window() = default;
    virtual std::string render() const = 0;
};

/**
 * Concrete Windows for each platform.
 */
class WindowsWindow : public Window {
public:
    std::string render() const override {
        return "Rendering a Windows-style window.";
    }
};

class MacWindow : public Window {
public:
    std::string render() const override {
        return "Rendering a macOS-style window.";
    }
};

/**
 * Base interface for a button in a GUI toolkit.
 */
class Button {
public:
    virtual ~Button() = default;
    virtual std::string render() const = 0;

    // Buttons collaborate with windows (e.g., rendering inside a window)
    virtual std::string clickInside(const Window& window) const = 0;
};

/**
 * Concrete Buttons for each platform.
 */
class WindowsButton : public Button {
public:
    std::string render() const override {
        return "Rendering a Windows-style button.";
    }

    std::string clickInside(const Window& window) const override {
        return "WindowsButton clicked inside → (" + window.render() + ")";
    }
};

class MacButton : public Button {
public:
    std::string render() const override {
        return "Rendering a macOS-style button.";
    }

    std::string clickInside(const Window& window) const override {
        return "MacButton clicked inside → (" + window.render() + ")";
    }
};

/**
 * Abstract Factory that declares creation methods
 * for a family of GUI components.
 */
class GuiFactory {
public:
    virtual ~GuiFactory() = default;

    // MODERN: factories now return smart pointers
    virtual std::unique_ptr<Window> createWindow() const = 0;
    virtual std::unique_ptr<Button> createButton() const = 0;
};

/**
 * Concrete factories producing platform-consistent components.
 */
class WindowsGuiFactory : public GuiFactory {
public:
    std::unique_ptr<Window> createWindow() const override {
        return std::make_unique<WindowsWindow>();
    }

    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
};

class MacGuiFactory : public GuiFactory {
public:
    std::unique_ptr<Window> createWindow() const override {
        return std::make_unique<MacWindow>();
    }

    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }
};

/**
 * Client code that only knows about abstract types.
 */
void runGui(const GuiFactory& factory) {
    auto window = factory.createWindow(); // unique_ptr<Window>
    auto button = factory.createButton(); // unique_ptr<Button>

    std::cout << window->render() << "\n";
    std::cout << button->render() << "\n";
    std::cout << button->clickInside(*window) << "\n";

    // no delete needed — RAII cleans everything up automatically
}

int main() {
    std::cout << "Running GUI with Windows style:\n";
    WindowsGuiFactory windowsFactory;
    runGui(windowsFactory);

    std::cout << "\nRunning GUI with macOS style:\n";
    MacGuiFactory macFactory;
    runGui(macFactory);
}
