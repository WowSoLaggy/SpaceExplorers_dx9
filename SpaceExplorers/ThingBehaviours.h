#pragma once

#ifndef INC_THINGBEHAVIOURS_H
#define INC_THINGBEHAVIOURS_H


enum class ThingBehaviour
{
	None = 0,
	Door,

	End
};


namespace
{
	static std::vector<std::string> behaviourStrings = {
		"None",
		"Door",
	};
}


static std::string ConvertBehaviourToString(ThingBehaviour pBehaviour)
{
	return behaviourStrings[(int)pBehaviour];
}


static ThingBehaviour ConvertStringToBehaviour(const std::string& pBehaviourString)
{
	LOG("ConvertStringToBehaviour()");

	auto& it = std::find_if(behaviourStrings.begin(), behaviourStrings.end(), [&](const auto& str) { return pBehaviourString == str; });
	if (it == behaviourStrings.end())
	{
		echo("ERROR: Can't convert \"", pBehaviourString, "\" to ThingBehaviour.");
		return ThingBehaviour::None;
	}

	return (ThingBehaviour)(std::distance(behaviourStrings.begin(), it));
}


#endif // INC_THINGBEHAVIOURS_H
