#  enum_mapping.h

## A Typesafe way to convert c++ enum class values to strings and back

We have all faced the problem of serializing our beautifully typesafe enum classes from and to the murky soups of text that are json, xml, ymal, or ini. Perhaps you have looked longingly at other languages that make this easy, with their fancy-pants reflection and annotations.

But we are C++ programmers - we solve our own problems. Or search github for solutions, which is the next best thing. We get paid either way.

Say you have a some enum classes:

```C++
enum class ParkingPolicy {NoParking, OnlyPublicHolidays, OnlyWeekends, OnlyWeekdays, SevenDays};
enum class ColorOptions {Transparent, Red, Yellow, Green, Blue, White, Black};
```
And you want to deserialise this:

```json
{
"name" : "Elm Street", 
"parking" : "OnlyWeekends", 
"signage" : "Green"
}
```
You could do this:

```C++
std::string parkingString = jsonObject["parking"];
ParkingPolicy parking;
if (parkingString == "NoParking")
parking = ParkingPolicy::NoParking; break;
else if ((parkingString == "OnlyPublicHolidays")
parking = ParkingPolicy::OnlyPublicHolidays; break;
else if ((parkingString == "OnlyWeekends")
parking = ParkingPolicy::OnlyWeekends; break;
... etc, etc ...
```

But code like that makes my eye twitch. Too long, too easy to make a mistake.

EnumMapping allows you do set up a static array, like so:

```C++
const std::array<const NameValuePair<ParkingPolicy>, 5 > ValidParkingPolicies{{
{ParkingPolicy::NoParking, "NoParking"},
{ParkingPolicy::OnlyPublicHolidays, "OnlyPublicHolidays"},
{ParkingPolicy::OnlyWeekends, "OnlyWeekends"},
{ParkingPolicy::OnlyWeekdays, "OnlyWeekdays"},
{ParkingPolicy::SevenDays, "SevenDays"}
}};
```

and then the above code shrinks to:

```C++
ParkingPolicy parking = EnumMapping::getValueFromName(ValidParkingPolicies, jsonObject["parking"]);
```

And it works the other way as well:

```C++
std::cout << "The parking policy is " << EnumMapping::getNameFromValue(ValidParkingPolicies, parking) << std::endl;
```

No mess. No fuss. Plus added type safety and exceptions will be thrown incorrect input.

### Usage

See main.cpp for some usage examples and test cases. There is no need to build a library, the only file you need to include is enum_mapping.h.

You don't have to include every value in the enum in the mapping array if there are some values that cannot be serialised.

Likewise, you can include the same value with different names if you want to have synonyms for some of your values.

EnumMapping uses operator== to compare the value names, you might want to change this if you need a case-insensitive  comparison.

### Performance

EnumMapping is designed to work on enums with only a few values. It uses a linear search to perform the lookups to avoid the overhead of setting up two maps. This is fine for a few values but if you need to serialize enums with dozens of valid values then a map-based solution would be better.

### Exceptions

EnumMapping throws a subclass of std::runtime_error called UnknownValueException if asked to de/serialize an invalid value. I find exceptions useful in dealing with IO boundaries. Perhaps you disagree - feel free to modify that part of the code.


