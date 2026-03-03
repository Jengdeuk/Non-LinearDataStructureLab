#pragma once

template <typename KeyType, typename ValueType>
struct Pair
{
	KeyType key;
	ValueType value;

	Pair()
		: key(), value()
	{
	}

	Pair(const KeyType& key, const ValueType& value)
		: key(key), value(value)
	{
	}

	bool operator==(const Pair& other)
	{
		return key == other.key && value == other.value;
	}

	bool operator!=(const Pair& other)
	{
		return !(*this == other);
	}

	bool operator>(const Pair& other)
	{
		return key > other.key;
	}

	bool operator>=(const Pair& other)
	{
		return key >= other.key;
	}

	bool operator<(const Pair& other)
	{
		return key < other.key;
	}

	bool operator<=(const Pair& other)
	{
		return key <= other.key;
	}
};
