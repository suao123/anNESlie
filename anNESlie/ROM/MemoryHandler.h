#pragma once
#include <functional>
#include "..\Types.h"
#include <vector>
#include <string>
//using namespace std;

namespace ROM
{
	/*
		此类的用处：
			1.NES的内存不是简单地线性关系，存在大量内存之间的映射、Mapper，所以创建这一个类来统一处理这类问题
			2.不在此类内直接new出内存而是交给外部管理，是为了简化ROM的Mapper交换过程（本类因此被称为Handler）
	*/

	/*
	NES为典型的八位机，不仅寄存器、内存每一位的长度同样为8bit，所以应该采用Byte
	*/

	/*
	默认的读映射应当为0
	默认的写映射应当直接return，因为一些游戏会通过向未映射地址写值的方法来继续工作
	*/

	class MemoryHandler
	{
	private:
		bool log;
		std::vector<std::string> logs;

		Byte* memory;
		std::function<Byte(int)>* readHandlers;
		std::function<void(int, Byte)>* writeHandlers;

	public:
		MemoryHandler(Byte* memory_address, int memory_size, bool log = false);
		~MemoryHandler();

		Byte* GetMemoryAddress();
		void SetMemoryAddress(Byte* memory_address);

		void SetReadHandler(Word address, Byte(*handler)(int));
		void SetReadHandler(Word address, std::function<Byte(int)> handler);
		void SetReadHandler(Word address_start, int address_end, std::function<Byte(int)> handler);
		void SetWriteHandler(Word address, void (*handler)(int, Byte));
		void SetWriteHandler(Word address, std::function<void(int, Byte)>  handler);
		void SetWriteHandler(Word address_start, int address_end, std::function<void(int, Byte)>  handler);

		Byte ReadByte(Word address);
		void WriteByte(Word address, Byte value);

		Word ReadWord(Word address);
		//void WriteWord(Word address, Word value);

	};
}


