#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab07.3(rec)/Lab07.3(rec).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const int rowCount = 3;
            const int colCount = 4;
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                a[i] = new int[colCount];

            a[0][0] = 0; a[0][1] = 1; a[0][2] = 0; a[0][3] = 3; 
            a[1][0] = 4; a[1][1] = 5; a[1][2] = 6; a[1][3] = 7; 
            a[2][0] = 0; a[2][1] = 0; a[2][2] = 0; a[2][3] = 8; 

            int maxRowIndex = -1;
            int maxZeroes = 0;
            RowWithMostZeroes(a, rowCount, colCount, 0, maxZeroes, maxRowIndex);
            Assert::AreEqual(maxRowIndex, 2); 

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
		}
	};
}
