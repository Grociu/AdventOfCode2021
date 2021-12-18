#include "pch.h"
#include "CppUnitTest.h"
#include "sum-of-id.cpp"
#include "Packet.h"
#include "Packet.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Day16Unittest
{
	
	TEST_CLASS(TestInputParsing)
	{
	public:
		const std::string path = "../Day16-PacketDecoder/";
		const std::string filename2 = path + "TestInput2.txt";
		const std::string filename3 = path + "TestInput3.txt";

		TEST_METHOD(TestCanReadInputFile1)
		{
			std::string output;
			read_input_file(filename2, output);
			Assert::AreEqual(std::string{ "EE00D40C823060" }, output);
		}
		
		TEST_METHOD(TestCanReadInputFile2)
		{
			std::string output;
			read_input_file(filename3, output);
			Assert::AreEqual(std::string{ "8A004A801A8002F478" }, output);
		}
	};

	TEST_CLASS(TestHexToBinaryConversion)
	{
	public:
		TEST_METHOD(TestConversion0)
		{
			Assert::AreEqual(std::string{ "0000" }, hex_to_binary('0'));
		}

		TEST_METHOD(TestConversion1)
		{
			Assert::AreEqual(std::string{ "0001" }, hex_to_binary('1'));
		}
		
		TEST_METHOD(TestConversion4)
		{
			Assert::AreEqual(std::string{ "0100" }, hex_to_binary('4'));
		}
		
		TEST_METHOD(TestConversion9)
		{
			Assert::AreEqual(std::string{ "1001" }, hex_to_binary('9'));
		}

		TEST_METHOD(TestConversionA)
		{
			Assert::AreEqual(std::string{ "1010" }, hex_to_binary('A'));
		}

		TEST_METHOD(TestConversionF)
		{
			Assert::AreEqual(std::string{ "1111" }, hex_to_binary('F'));
		}
	};

	TEST_CLASS(TestReadLiteralPackets)
	{
	public:
		TEST_METHOD(TestCanReadLiteralPacket)
		{
			const std::string hex_string = "D2FE28";
			std::vector<Packet> packets;
			decode_packets(hex_string, packets);
			int result = packets[0].values[0];
			Assert::AreEqual(2021, result);
		}
	};


	TEST_CLASS(TestReadOperatorPackets)
	{
	public:
		const std::string hex_string = "38006F45291200";
		std::vector<Packet> packets;
		
		TEST_METHOD_INITIALIZE(methodName)
		{
			decode_packets(hex_string, packets);
		}

		TEST_METHOD(TestCanReadSimpleOperatorVersion)
		{
			int result = packets[0].version;
			Assert::AreEqual(1, result);
		}
		
		TEST_METHOD(TestCanReadSimpleOperatorId)
		{
			int result = packets[0].id;
			Assert::AreEqual(6, result);
		}

		TEST_METHOD(TestCanReadSimpleOperatorFirstLiteralId)
		{
			int result = packets[0].subpackets[0].id;
			Assert::AreEqual(4, result);
		}

		TEST_METHOD(TestCanReadSimpleOperatorFirstLiteral)
		{
			int result = packets[0].subpackets[0].values[0];
			Assert::AreEqual(10, result);
		}

		TEST_METHOD(TestCanReadSimpleOperatorSecondLiteralId)
		{
			int result = packets[0].subpackets[1].id;
			Assert::AreEqual(4, result);
		}

		TEST_METHOD(TestCanReadSimpleOperatorSecondLiteral)
		{
			int result = packets[0].subpackets[1].values[0];
			Assert::AreEqual(20, result);
		}

	};

}

