#pragma once

#include <numbers>
#include <cmath>


class Angle {
public:
    static constexpr Angle FromDegrees(const float degrees)
        { return Angle(degrees * degreeToRadiansConst); }

    static constexpr Angle FromRadians(const float radians)
        { return Angle(radians); }

    [[nodiscard]]
    constexpr float ToDegrees() const
        { return radians * radiansToDegreesConst; }

    [[nodiscard]]
    constexpr float ToRadians() const
        { return radians; }

    constexpr bool operator==(const Angle& other) const
        { return radians == other.radians; }

    Angle operator+(const Angle& other) const
        { return Angle(radians + other.radians); }

    Angle operator-(const Angle& other) const
        { return Angle(radians - other.radians); }

private:
    explicit constexpr Angle(const float radians): radians(radians) {}

    static constexpr float degreeToRadiansConst = std::numbers::pi_v<float> / 180.f;
    static constexpr float radiansToDegreesConst = 1.f / degreeToRadiansConst;

    float radians;
};


inline float Sin(const Angle angle)
    { return std::sin(angle.ToRadians()); }


inline float Cos(const Angle angle)
    { return std::cos(angle.ToRadians()); }

inline Angle Atan2(const float y, const float x)
    { return Angle::FromRadians(std::atan2(y, x)); }

inline Angle Acos(const float val)
    { return Angle::FromRadians(std::acos(val)); }
