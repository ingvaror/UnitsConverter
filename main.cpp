#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <optional>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace Units
{

enum UnitsQuantity
{
    Length,
    Power
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
    void AddUnitsQuantity(UnitsQuantity unitsQuantity, const std::vector<UnitsType>& units)
    {
        m_quantityData[unitsQuantity] = units;
    }
    void AddUnitsDescription(UnitsType unitsType, const UnitsDescription& description)
    {
        m_desciptionData[unitsType] = description;
    }
    std::optional<double> GetDoubleFromString(const std::wstring& input, UnitsQuantity quantity, std::optional<UnitsType> inputType = std::nullopt)
    {
        std::optional<double> value;
        std::optional<UnitsDescription> unitsDescription;
        // Parse string 
        std::vector<std::wstring> tokens;
        boost::split(tokens, input, boost::is_any_of(L" "));
        // Find units and double value
        for(const auto& token : tokens)
        {
            try
            {
                if (!token.empty())
                {
                    value = boost::lexical_cast<double>(token);
                    continue;
                }
            }
            catch(...)
            {
                assert(m_quantityData.count(quantity));
                const auto& quantitySet = m_quantityData.at(quantity);
                for (const UnitsType unitType : quantitySet)
                {
                    assert(m_desciptionData.count(unitType));
                    const auto description = m_desciptionData.at(unitType);
                    if(boost::iequals(description.m_name, token))
                    {
                        unitsDescription = description;
                        break;
                    }
                }
            }
        }
        if (value.has_value())
        {
            // Process results
            if (unitsDescription.has_value())
            {
                return (*value) * unitsDescription.value().m_coeff;
            }
            else if (inputType.has_value())
                {
                    assert(m_desciptionData.count(*inputType));
                    const auto& defaultDescription = m_desciptionData.at(*inputType);
                    return (*value) * defaultDescription.m_coeff;
            }
        }
        return value;
    }

    std::wstring GetStringFromDouble(const double input, UnitsType type, bool showUnits)
    {
        assert(m_desciptionData.count(type));
        const auto& description = m_desciptionData.at(type);
        std::wstring value = boost::lexical_cast<std::wstring>(input);
        if (showUnits)
            return value + L" " + description.m_name;
        else
            return value;
    }
private:
    UnitsSet m_quantityData;
    UnitsDescriptionSet m_desciptionData;
};
}

int main(int argc, char **argv)
{
    Units::UnitsConverter unitsConverter;
    unitsConverter.AddUnitsDescription(Units::M, {1, L"m"});
    unitsConverter.AddUnitsDescription(Units::MM, {1e-3, L"mm"});
    unitsConverter.AddUnitsDescription(Units::MICRON, {1e-6, L"μm"});    
    unitsConverter.AddUnitsDescription(Units::NM, {1e-9, L"nm"});
    
    unitsConverter.AddUnitsQuantity(Units::Length, { Units::M, Units::MM, Units::MICRON, Units::NM });

    assert(unitsConverter.GetDoubleFromString(L"1  mm", Units::Length) == 1e-3);
    assert(unitsConverter.GetDoubleFromString(L"ddvf", Units::Length) == std::nullopt);
    assert(unitsConverter.GetStringFromDouble(1.0, Units::M, true) == L"1 m");

    return 0;
}
