#include "pch.h"
#include "CppUnitTest.h"
#include "../PRD/Instance.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestPRD
{
	TEST_CLASS(UnitTestInstance)
	{
	public:
		
		TEST_METHOD(TestParseur)
		{
			Instance * instance = new Instance();
			Assert::AreEqual(true, instance->Parse("../UnitTestPRD/instanceTest/I_n5_id0.txt"));
			delete instance;
		}
	};
}
