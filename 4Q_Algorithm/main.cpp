#include <iostream>
#include <unordered_map>
#include <Windows.h>
#include <random>
#include <functional>

const int HASH_DATA_SIZE = 50000;
const int HASH_MAP_SIZE = SHRT_MAX * 2;

#include "Hash.h"
#include "HashData.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));


	// �ؽ� �ʿ� ���� �ؽ� ������ �迭 ����
	vector<HashData> hashData;
	hashData.reserve(HASH_DATA_SIZE);

	// ������ �ؽ������� ����
	for (int i = 0; i < HASH_DATA_SIZE; i++)
	{
		HashData hashDataTemp;

		int stringSize = (rand() % 10) + 3;
		int tempValue = rand() % MAXINT16;
		float tempSpeed = rand() % 100;
		string tempString;
		tempString.resize(stringSize + 1);

		for (int j = 0; j < stringSize; j++)
		{
			char tempChar = rand() % ('z' - 'A');

			tempString[j] = tempChar + 'A';
		}

		hashDataTemp.DataSetting(tempString, tempValue, tempSpeed);
		hashData.push_back(hashDataTemp);
	}

	// �ؽø� ����
	HashMap<string, HashData> hash(HASH_MAP_SIZE);
	unordered_map<string, HashData> hashmap(HASH_MAP_SIZE);

	// ���� ���� �ؽ� ��
	{
		LARGE_INTEGER timer, start, end;
		float deltaTime;

		QueryPerformanceFrequency(&timer);
		QueryPerformanceCounter(&start);

		// �ؽøʿ� �� �ֱ�
		for (int i = 0; i < HASH_DATA_SIZE; i++)
			hash.Insert(hashData[i].GetName(), hashData[i]);

		QueryPerformanceCounter(&end);

		deltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

		cout << "�ؽ� ������ �ִµ� �ɸ� �ð�(s) : " << deltaTime << endl;
	}

	// STL �ؽ� ��
	{
		LARGE_INTEGER timer, start, end;
		float deltaTime;

		QueryPerformanceFrequency(&timer);
		QueryPerformanceCounter(&start);

		// �ؽøʿ� �� �ֱ�
		for (int i = 0; i < HASH_DATA_SIZE; i++)
			hashmap.insert(make_pair(hashData[i].GetName(), hashData[i]));

		QueryPerformanceCounter(&end);

		deltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

		cout << "STL �ؽ� ������ �ִµ� �ɸ� �ð�(s) : " << deltaTime << endl;
	}
	
	// �ؽ� ������ ã��
	{
		//int findhashdata = 0;
		//for (auto data : hashData)
		//{
		//	if (hash.Find(data.GetName()))
		//	{
		//		cout << data.GetName() << " : " << hash.GetHash(data.GetName()) << endl;
		//		findhashdata++;
		//	}
		//}

		//cout << "ã�� �ؽ� ������ ���� : " << findhashdata << endl;
	}

	// �ؽ� ���� �浹 �ؽ� ��� �� ���
	hash.PrintCollisionHash();

	return 0;
}
