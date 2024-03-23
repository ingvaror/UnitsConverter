#include "UnitsConverter.h"

using namespace Units;

UnitsConverter::UnitsConverter()
{
    AddUnitsDescription(Units::M, {1, L"m"});
    AddUnitsDescription(Units::MM, {1e-3, L"mm"});
    AddUnitsDescription(Units::MICRON, {1e-6, L"μm"});    
    AddUnitsDescription(Units::NM, {1e-9, L"nm"});
    
    AddUnitsQuantity(Units::Length, { Units::M, Units::MM, Units::MICRON, Units::NM });
}

