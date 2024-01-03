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


	// 해시 맵에 넣을 해시 데이터 배열 생성
	vector<HashData> hashData;
	hashData.reserve(HASH_DATA_SIZE);

	// 무작위 해쉬데이터 생성
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

	// 해시맵 생성
	HashMap<string, HashData> hash(HASH_MAP_SIZE);
	unordered_map<string, HashData> hashmap(HASH_MAP_SIZE);

	// 직접 만든 해쉬 맵
	{
		LARGE_INTEGER timer, start, end;
		float deltaTime;

		QueryPerformanceFrequency(&timer);
		QueryPerformanceCounter(&start);

		// 해시맵에 값 넣기
		for (int i = 0; i < HASH_DATA_SIZE; i++)
			hash.Insert(hashData[i].GetName(), hashData[i]);

		QueryPerformanceCounter(&end);

		deltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

		cout << "해쉬 데이터 넣는데 걸린 시간(s) : " << deltaTime << endl;
	}

	// STL 해쉬 맵
	{
		LARGE_INTEGER timer, start, end;
		float deltaTime;

		QueryPerformanceFrequency(&timer);
		QueryPerformanceCounter(&start);

		// 해시맵에 값 넣기
		for (int i = 0; i < HASH_DATA_SIZE; i++)
			hashmap.insert(make_pair(hashData[i].GetName(), hashData[i]));

		QueryPerformanceCounter(&end);

		deltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

		cout << "STL 해쉬 데이터 넣는데 걸린 시간(s) : " << deltaTime << endl;
	}
	
	// 해시 데이터 찾기
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

		//cout << "찾은 해쉬 데이터 개수 : " << findhashdata << endl;
	}

	// 해시 맵의 충돌 해시 계산 및 출력
	hash.PrintCollisionHash();

	return 0;
}
