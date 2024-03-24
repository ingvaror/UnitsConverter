#include <iostream>
#include <cassert>
#include "UnitsConverter.h"

int main(int argc, char **argv)
{
    auto unitsConverter = Units::UnitsConverter::GetInstance();

    assert(unitsConverter->GetDoubleFromString(L"1  mm", Units::Length) == 1e-3);
    assert(unitsConverter->GetDoubleFromString(L"ddvf", Units::Length) == std::nullopt);
    assert(unitsConverter->GetDoubleFromString(L"2 mmm", Units::Length) == std::nullopt);
    assert(unitsConverter->GetDoubleFromString(L"1 nm", Units::Length, Units::MICRON) == 1e-9);
    assert(unitsConverter->GetDoubleFromString(L"2", Units::Length, Units::MICRON) == 2e-6);
    assert(unitsConverter->GetDoubleFromString(L"12", Units::Dimensionless) == 12);
    assert(unitsConverter->GetStringFromDouble(1.0, Units::M, true) == L"1 m");
    assert(unitsConverter->GetStringFromDouble(1e-6, Units::MICRON, true) == L"1 μm");

    return 0;
}
