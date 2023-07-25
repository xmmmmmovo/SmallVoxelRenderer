//
// Created by xmmmmmovo on 2023/7/19.
//

#ifndef VOXEL_RENDERER_CORE_MATH_ANGLE_HPP
#define VOXEL_RENDERER_CORE_MATH_ANGLE_HPP

namespace voxel {

template<typename TScalar>
constexpr TScalar PI = TScalar(3.14159265358979323846);

template<typename TScalar>
constexpr TScalar deg_to_rad(TScalar aDegrees) {
    return aDegrees * PI<TScalar> / TScalar(180);
}
template<typename TScalar>
constexpr TScalar rad_to_deg(TScalar aRadians) {
    return aRadians * TScalar(180) / PI<TScalar>;
}


template<typename TScalar>
class Degrees;
template<typename TScalar>
class Radians;

template<typename TScalar>
class Degrees {
public:
    constexpr explicit Degrees(TScalar aValue = TScalar(0)) noexcept
        : mValue(aValue) {}

    constexpr Degrees(Degrees const &aOther) noexcept : mValue(aOther.mValue) {}
    constexpr Degrees &operator=(Degrees const &aOther) noexcept {
        mValue = aOther.mValue;
        return *this;
    }

    constexpr explicit Degrees(Radians<TScalar> const &aRadians) noexcept
        : mValue(rad_to_deg(aRadians.value())) {}
    constexpr Degrees &operator=(Radians<TScalar> const &aRadians) noexcept {
        mValue = rad_to_deg(aRadians.value());
        return *this;
    }

public:
    [[nodiscard]] constexpr TScalar value() const noexcept { return mValue; }

private:
    TScalar mValue;
};

template<typename TScalar>
class Radians {
public:
    constexpr explicit Radians(TScalar aValue = TScalar(0)) noexcept
        : mValue(aValue) {}

    constexpr Radians(Radians const &aOther) noexcept : mValue(aOther.mValue) {}
    constexpr Radians &operator=(Radians const &aOther) noexcept {
        mValue = aOther.mValue;
        return *this;
    }

    constexpr Radians(Degrees<TScalar> const &aDegrees) noexcept
        : mValue(deg_to_rad(aDegrees.value())) {}
    constexpr Radians &operator=(Degrees<TScalar> const &aDegrees) noexcept {
        mValue = deg(aDegrees.value());
        return *this;
    }

public:
    [[nodiscard]] constexpr TScalar value() const noexcept { return mValue; }

private:
    TScalar mValue;
};


using Degreesf = Degrees<float>;
using Radiansf = Radians<float>;

template<typename TScalar>
constexpr TScalar to_degrees(Degrees<TScalar> aValue) noexcept {
    return aValue.value();
}
template<typename TScalar>
constexpr TScalar to_radians(Radians<TScalar> aValue) noexcept {
    return aValue.value();
}


inline namespace literals {
    constexpr Radiansf operator"" _radf(long double aValue) noexcept {
        return Radiansf(static_cast<float>(aValue));
    }

    constexpr Degreesf operator"" _degf(long double aValue) noexcept {
        return Degreesf(static_cast<float>(aValue));
    }
}// namespace literals

}// namespace voxel

#endif//VOXEL_RENDERER_CORE_MATH_ANGLE_HPP
