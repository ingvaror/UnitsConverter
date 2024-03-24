#include "UnitsConverter.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace Units;

std::shared_ptr<UnitsConverter> UnitsConverter::GetInstance()
{
    auto instance = std::make_shared<UnitsConverter>();
    instance->AddUnitsDescription(Units::M, {1, L"m"});
    instance->AddUnitsDescription(Units::MM, {1e-3, L"mm"});
    instance->AddUnitsDescription(Units::MICRON, {1e-6, L"μm"});    
    instance->AddUnitsDescription(Units::NM, {1e-9, L"nm"});
    
    instance->AddUnitsQuantity(Units::Length, { Units::M, Units::MM, Units::MICRON, Units::NM });
    return instance;
}

void UnitsConverter::AddUnitsQuantity(UnitsQuantity unitsQuantity, const std::vector<UnitsType>& units)
{
    m_quantityData[unitsQuantity] = units;
}

void UnitsConverter::AddUnitsDescription(UnitsType unitsType, const UnitsDescription& description)
{
    m_desciptionData[unitsType] = description;
}

std::optional<double> UnitsConverter::GetDoubleFromString(const std::wstring& input, UnitsQuantity quantity, std::optional<UnitsType> inputType)
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

std::wstring UnitsConverter::GetStringFromDouble(const double input, UnitsType type, bool showUnits)
{
    assert(m_desciptionData.count(type));
    const auto& description = m_desciptionData.at(type);
    std::wstring value = boost::lexical_cast<std::wstring>(input / description.m_coeff);
    if (showUnits)
        return value + L" " + description.m_name;
    else
        return value;
}