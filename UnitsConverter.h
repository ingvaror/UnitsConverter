#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <optional>
#include <memory>

#include "UnitsType.h"

namespace Units
{
    struct UnitsDescription
    {
        double m_coeff;
        std::wstring m_name; 
    };

    using UnitsSet = std::unordered_map<UnitsQuantity, std::vector<UnitsType>>;
    using UnitsDescriptionSet = std::unordered_map<UnitsType, UnitsDescription>;

    class UnitsConverter
    {
    public:
        UnitsConverter();
        static std::shared_ptr<UnitsConverter> GetInstance();
        void AddUnitsQuantity(UnitsQuantity unitsQuantity, const std::vector<UnitsType>& units);
        void AddUnitsDescription(UnitsType unitsType, const UnitsDescription& description);
        std::optional<double> GetDoubleFromString(const std::wstring& input, UnitsQuantity quantity, std::optional<UnitsType> inputType = std::nullopt);

        // \param input Value in SI which will be converted in string
        // \param type Output units
        // \param showUnits Append units to the string
        std::wstring GetStringFromDouble(const double input, UnitsType type, bool showUnits);
    private:
        UnitsSet m_quantityData;
        UnitsDescriptionSet m_desciptionData;
    };
}