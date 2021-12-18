#include "pch.h"
#include "CppUnitTest.h"
#include "Snailfish_number.h"
#include <string>

// handle the tostring templte for enum type
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> static std::wstring ToString<Snailfish_number::Sn_type>(const Snailfish_number::Sn_type& t) {
				switch (t) {
				case Snailfish_number::Lit: return L"Literal";
				case Snailfish_number::Und: return L"Undefined";
				case Snailfish_number::Snn: return L"Snailfish number";
				default: throw std::runtime_error("");
				}
			};
		}
	}
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Day18Unittest
{

	TEST_CLASS(Reading_Snailfish_numbers)
	{
	public:
		const std::string example1{ "[1,2]" };
		const std::string example2{ "[[1,2],3]" };
		const std::string example3{ "[9,[8,7]]" };
		const std::string example4{ "[[1,9],[8,5]]" };
		const std::string example5{ "[[[[1,2],[3,4]],[[5,6],[7,8]]],9]" };
		const std::string example6{ "[[[9,[3,8]],[[0,9],6]],[[[3,7],[4,9]],3]]" };
		const std::string example7{ "[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]" };
		Snailfish_number sn;

		TEST_METHOD(Read_Ex1_Rank)
		{
			std::stringstream iss{ example1 };
			iss >> sn;
			Assert::AreEqual(sn.rank, 1);
		}
		TEST_METHOD(Read_Ex1_Ltype)
		{
			std::stringstream iss{ example1 };
			iss >> sn;
			Assert::AreEqual(sn.left, Snailfish_number::Lit);
		}
		TEST_METHOD(Read_Ex1_Rtype)
		{
			std::stringstream iss{ example1 };
			iss >> sn;
			Assert::AreEqual(sn.right, Snailfish_number::Lit);
		}
		TEST_METHOD(Read_Ex1_Lvalue)
		{
			std::stringstream iss{ example1 };
			iss >> sn;
			Assert::AreEqual(sn.nums[0], 1);
		}
		TEST_METHOD(Read_Ex1_Rvalue)
		{
			std::stringstream iss{ example1 };
			iss >> sn;
			Assert::AreEqual(sn.nums[1], 2);
		}

		TEST_METHOD(Read_Ex2_TopRank)
		{
			std::stringstream iss{ example2 };
			iss >> sn;
			Assert::AreEqual(sn.rank, 1);
		}
		TEST_METHOD(Read_Ex2_SubRank)
		{
			std::stringstream iss{ example2 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[0].rank, 2);
		}
		TEST_METHOD(Read_Ex2_Ltype)
		{
			std::stringstream iss{ example2 };
			iss >> sn;
			Assert::AreEqual(sn.left, Snailfish_number::Snn);
		}
		TEST_METHOD(Read_Ex2_Rtype)
		{
			std::stringstream iss{ example2 };
			iss >> sn;
			Assert::AreEqual(sn.right, Snailfish_number::Lit);
		}
		TEST_METHOD(Read_Ex2_L_L_Subvalue)
		{
			std::stringstream iss{ example2 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[0].nums[0], 1);
		}
		TEST_METHOD(Read_Ex2_L_R_Subvalue)
		{
			std::stringstream iss{ example2 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[0].nums[1], 2);
		}
		TEST_METHOD(Read_Ex2_Rvalue)
		{
			std::stringstream iss{ example2 };
			iss >> sn;
			Assert::AreEqual(sn.nums[0], 3);
		}
		
		TEST_METHOD(Read_Ex4_LType)
		{
			std::stringstream iss{ example4 };
			iss >> sn;
			Assert::AreEqual(sn.left, Snailfish_number::Snn);
		}
		TEST_METHOD(Read_Ex4_RType)
		{
			std::stringstream iss{ example4 };
			iss >> sn;
			Assert::AreEqual(sn.right, Snailfish_number::Snn);
		}
		TEST_METHOD(Read_Ex4_L_L_Subvalue)
		{
			std::stringstream iss{ example4 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[0].nums[0], 1);
		}
		TEST_METHOD(Read_Ex4_L_R_Subvalue)
		{
			std::stringstream iss{ example4 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[0].nums[1], 9);
		}
		TEST_METHOD(Read_Ex4_R_L_Subvalue)
		{
			std::stringstream iss{ example4 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[1].nums[0], 8);
		}
		TEST_METHOD(Read_Ex4_R_R_Subvalue)
		{
			std::stringstream iss{ example4 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[1].nums[1], 5);
		}
	
		TEST_METHOD(Read_Ex7_FirstValue)
		{
			std::stringstream iss{ example7 };
			iss >> sn;
			Assert::AreEqual(sn.sn_nums[0].sn_nums[0].sn_nums[0].nums[0], 1);
		}

	};
}
