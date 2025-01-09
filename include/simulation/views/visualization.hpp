#pragma once


class Visualization {
public:
    Visualization(int xResolution, int yResolution);

    void Render() const;


    [[nodiscard]]
    static const char* WindowName()
        { return "Visualization options"; }

private:

};
