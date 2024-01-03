#include "HashData.h"

HashData::HashData()
	: m_Name()
	, m_Value()
	, m_Speed()
{
}

HashData::~HashData()
{
}

void HashData::DataSetting(string name, int value, float speed)
{
	m_Name = name;
	m_Value = value;
	m_Speed = speed;
}

const string& HashData::GetName()
{
	return m_Name;
}

const int& HashData::GetValue()
{
	return m_Value;
}
