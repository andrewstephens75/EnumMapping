// This is just an example, all you need is the enum_mapping.h file
// set the README.md for details

#include <iostream>
#include <array>
#include <string>

#include "enum_mapping.h"
#include "dumb_test_helpers.h"

// We have some strongly typed enums to deal with
enum class ParkingPolicy {NoParking, OnlyPublicHolidays, OnlyWeekends, OnlyWeekdays, SevenDays};
enum class ColorOptions {Transparent, Red, Yellow, Green, Blue, White, Black};

namespace {
    
using namespace EnumMapping;

// Initialise the arrays. Any container that supports find_if will work but std::array is very light
// Not that brace-elision doesn't work here (at least in zcode), the opening {{ braces
// are required (std::array is secretly an aggregate)
const std::array<const NameValuePair<ParkingPolicy>, 5 > ValidParkingPolicies{{
    {ParkingPolicy::NoParking, "NoParking"},
    {ParkingPolicy::OnlyPublicHolidays, "OnlyPublicHolidays"},
    {ParkingPolicy::OnlyWeekends, "OnlyWeekends"},
    {ParkingPolicy::OnlyWeekdays, "OnlyWeekdays"},
    {ParkingPolicy::SevenDays, "Sevendays"}
}};

const std::array<const NameValuePair<ColorOptions>, 7> ValidColorOptions = {{
    {ColorOptions::Transparent, "Transparent"},
    {ColorOptions::Red, "Red"},
    {ColorOptions::Yellow, "Yellow"},
    {ColorOptions::Green, "Green"},
    {ColorOptions::Blue, "Blue"},
    {ColorOptions::White, "White"},
    {ColorOptions::Black, "Black"}
}};
    
} // anonymous namespace

int main(int argc, const char * argv[]) {
    
    // Usage for input:
    std::string inputString = "OnlyPublicHolidays";
    ParkingPolicy policy;
    try {
        policy = EnumMapping::getValueForName(ValidParkingPolicies, inputString);
    } catch (const EnumMapping::UnknownValueException& e) {
        std::cerr << "Something went wrong: " << e.what() << std::endl;
        std::abort();
    }
    // policy is set to something valid here
    
    // Usage for output:
    ColorOptions colorChoice = ColorOptions::Yellow;
    std::string outputString = EnumMapping::getNameForValue(ValidColorOptions, colorChoice);
    
    // Some test cases:
    // The static_cast<int>s are needed because my dumb TestExpected function can't handle the strongly typed enums
    TestExpected("getValueForName (ParkingPolicy)",
                 static_cast<int>(ParkingPolicy::OnlyWeekends),
                 static_cast<int>(getValueForName(ValidParkingPolicies, "OnlyWeekends")));
    
    TestExpected("getValueForName (Colors)",
                 static_cast<int>(ColorOptions::White),
                 static_cast<int>(getValueForName(ValidColorOptions, "White")));

    TestExpected("getNameForValue (ParkingPolicy)",
                 std::string("Sevendays"),
                 getNameForValue(ValidParkingPolicies, ParkingPolicy::SevenDays));
                 
    TestExpected("getNameForValue (Colors)",
                 std::string("Red"),
                 getNameForValue(ValidColorOptions, ColorOptions::Red));
    
    TestException<UnknownValueException>("getValueForName with illegal name",
                                         [](){getValueForName(ValidParkingPolicies, "NoTaxis");});

    TestException<UnknownValueException>("getNameForValue with illegal value",
                                         [](){getNameForValue(ValidColorOptions, ColorOptions(27));});

    
    // Does not compile because getValueForName enforces types
    // ParkingPolicy parking = getValueForName(ValidParkingPolicies, ColorOptions::Red);
    
    return 0;
}
