#pragma once

class MainController;


class OptionsPanel {
public:
    explicit OptionsPanel(MainController& controller);

    void Render() const;

    [[nodiscard]]
    static const char* WindowName()
        { return "Options"; }

private:
    MainController& controller;

    void RenderChainOptions() const;
};
