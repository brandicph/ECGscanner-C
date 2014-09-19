#include "stdafx.h"
#include "CppUnitTest.h"
#include "filter.h"
#include "sensor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TestFile
{
private:
	FILE *file;

public:
	char *filename;
	int value, reading;

	void loadFile(){
		if (file == NULL)
			file = fopen(filename, "r");
	}

	int getNextData(){

		if (reading = fscanf(file, "%i\n", &value) != EOF)
			return value;
		closeFile();
		return 0;
	}

	void closeFile(){
		fclose(file);
	}

};

namespace ECGScannerTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestFilters)
		{
			// TODO: Your test code here

			TestFile input;
			input.filename = "ECG.txt";
			input.loadFile();

			TestFile low;
			low.filename = "low.txt";
			low.loadFile();

			while (input.reading){
				int next = getNextData();

				int inputT = input.getNextData();
				int lowT = low.getNextData();

				Assert::AreEqual(10, inputT);
			}

		}

	};
}