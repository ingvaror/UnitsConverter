#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <optional>
#include <memory>

namespace Units
{
    enum UnitsQuantity
    {
        Length
    };

    enum UnitsType
    {
        M = 0,
        MM,
        MICRON,
        NM
    };

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
        // \return Instance of Units converter
        static std::shared_ptr<UnitsConverter> GetInstance();

        // \return std::nullopt in case of unsuccesfull convertation 
        std::optional<double> GetDoubleFromString(const std::wstring& input, UnitsQuantity quantity, std::optional<UnitsType> inputType = std::nullopt);

        // \param input Value in SI which will be converted in string
        // \param type Output units
        // \param showUnits Append units to the string
        std::wstring GetStringFromDouble(const double input, UnitsType type, bool showUnits);
    private:
        void AddUnitsQuantity(UnitsQuantity unitsQuantity, const std::vector<UnitsType>& units);
        void AddUnitsDescription(UnitsType unitsType, const UnitsDescription& description);
    private:
        UnitsSet m_quantityData;
        UnitsDescriptionSet m_desciptionData;
    };
}