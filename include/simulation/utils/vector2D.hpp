#pragma once

#include <vector>


template <typename T>
class Vector2D {
public:
    constexpr Vector2D(const size_t columns, const size_t rows):
        columnsCnt(columns), rowsCnt(rows), data(columns*rows) {}

    constexpr T& At(const size_t col, const size_t row)
        { return data.at(columnsCnt*row + col); }

    constexpr const T& At(const size_t x, const size_t y) const
        { return data.at(columnsCnt*y + x); }

    [[nodiscard]]
    constexpr size_t Columns() const
        { return columnsCnt; }

    [[nodiscard]]
    constexpr size_t Rows() const
        { return rowsCnt; }

    const std::vector<T>& ToVector() const
        { return data; }

    std::vector<T>& ToVector()
        { return data; }

private:
    size_t columnsCnt;
    size_t rowsCnt;
    std::vector<T> data;
};
