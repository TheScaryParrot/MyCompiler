// Enum of certainty values for look-ahead when looking ahead in the code, whether a certain pattern is present or not.

#pragma once

enum class ELookAheadCertainties
{
    CertainlyNotPresent,
    CertainlyPresent,
    Unknown
};

// Short circuit evaluation is not guaranteed for overloaded operators. Therefore the following operators would be inefficient to use

/*constexpr ELookAheadCertainties operator||(ELookAheadCertainties a, ELookAheadCertainties b)
{
    if (a == ELookAheadCertainties::CertainlyPresent || b == ELookAheadCertainties::CertainlyPresent)
    {
        return ELookAheadCertainties::CertainlyPresent;
    }

    if (a == ELookAheadCertainties::Unknown || b == ELookAheadCertainties::Unknown)
    {
        return ELookAheadCertainties::Unknown;
    }
    
    return ELookAheadCertainties::CertainlyNotPresent;
}

constexpr ELookAheadCertainties operator&&(ELookAheadCertainties a, ELookAheadCertainties b)
{
    if (a == ELookAheadCertainties::Unknown || b == ELookAheadCertainties::Unknown)
    {
        return ELookAheadCertainties::Unknown;
    }

    if (a == ELookAheadCertainties::CertainlyNotPresent || b == ELookAheadCertainties::CertainlyNotPresent)
    {
        return ELookAheadCertainties::CertainlyNotPresent;
    }
    
    return ELookAheadCertainties::CertainlyPresent;
}

constexpr ELookAheadCertainties operator!(ELookAheadCertainties a)
{
    if (a == ELookAheadCertainties::CertainlyNotPresent)
    {
        return ELookAheadCertainties::CertainlyPresent;
    }

    if (a == ELookAheadCertainties::CertainlyPresent)
    {
        return ELookAheadCertainties::CertainlyNotPresent;
    }

    return ELookAheadCertainties::Unknown;
}*/