#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab-7.2.2.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int** arr = new int* [2];
			arr[0] = new int[2]{ 1, 2 };
			arr[1] = new int[2]{ 0, 2 };

			int min_index_v = 0;
			int min_index_h = 0;
			MinInterRows(arr, 0, 2, 0, min_index_h, min_index_v);
			Assert::AreEqual(0, min_index_h);
		}

	};
}