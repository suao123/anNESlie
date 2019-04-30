#pragma once
#include "../Types.h"
#include "../ROM/MemoryHandler.h"

namespace PPU
{
	const int GAME_WIDTH = 256;
	const int GAME_HEIGHT = 240;

	const int SCANLINE_COUNT = 261;
	const int CYCLES_PER_LINE = 341;

	class PPUCore
	{
#pragma region Core

	private:
		const static DWord palette[64];

		DWord bufferPos;
		DWord rawBitmap[GAME_WIDTH * GAME_HEIGHT];
		DWord priority[GAME_WIDTH * GAME_HEIGHT];

		int cpuSyncCounter;
		DWord scanlineOAM[8 * 4];
		bool isSprite0[8];
		int spriteCount;

		QWord tileShiftRegister;
		DWord currentNametableByte;
		DWord currentHighTile, currentLowTile;
		DWord currentColor;

		int cpuClocksSinceVBL;
		int ppuClocksSinceVBL;

		void countSpritesOnLine(int scanline);
		void nextNametableByte();
		void nextTileByte(bool hi);
		void nextAttributeByte();
		void shiftTileRegister();
		void processBackgroundForPixel(int cycle, int scanline);
		void processSpritesForPixel(int x, int scanline);

	public:
		PPUCore();

		void ProcessFrame();
		void ProcessScanline(int line);
		void ProcessCycle(int scanline,int cycle);
		void ProcessPixel(int x, int y);
#pragma endregion

#pragma region Memory
	private:
		Byte memory[0x3FFF];
		ROM::MemoryHandler memoryHandler;
		Byte ReadByte(Word adress);
		void WriteByte(Word adress, Byte value);
		Byte ReadWord(Word adress);
		void WriteWord(Word adress, Byte value);


		Byte oam[0x100];
		Byte vram[0x2000];
		Byte paletteRAM[0x20];

		Byte VRAMMirrorLookUp[5][4];

		Byte lastWrittenRegister;

	public:
		void WriteRegister(Byte reg, Byte val);
		Byte ReadRegister(Byte reg);
		Word GetVRAMMirror(Word addr);
		void PerformDMA(Word from);
#pragma endregion


#pragma region Registers
	public:
		struct
		{

			/* PPUCTRL register */
			bool NMIEnabled;
			bool IsMaster;
			bool TallSpritesEnabled;
			DWord PatternTableAddress;
			DWord SpriteTableAddress;
			DWord VRAMIncrement;

			/* PPUMASK register */
			bool GrayscaleEnabled;
			bool DrawLeftBackground;
			bool DrawLeftSprites;
			bool DrawBackground;
			bool DrawSprites;
			// Flipped for PAL/Dendy
			bool EmphasizeRed;
			bool EmphasizeGreen;
			bool EmphasizeBlue;

			/* PPUSTATUS register */
			bool VBlankStarted;
			bool Sprite0Hit;
			bool SpriteOverflow;
			bool AddressLatch;

			/* PPUADDR register */
			inline Word getBusAddress()
			{
				return busAddress;
			}

			inline void setBusAddress(Byte val)
			{
				busAddress = val & 0x3FFF;
			}

			/* PPUDATA register */
			DWord BusData;

			/* OAMADDR register */
			inline Byte getOAMAddress()
			{
				return oamAddress;
			}

			inline void setOAMAddress(Byte val)
			{
				oamAddress = val;
			}

			/* PPUSCROLL registers */
			DWord ScrollX;
			DWord ScrollY;

			inline bool RenderingEnabled()
			{
				return DrawBackground || DrawSprites;
			}
		private:
			Word busAddress;
			Byte oamAddress;
		}Flag;

		Word T, X;

		Word getV();
		void setV(Word val);

		Byte getCoarseX();
		Byte getCoarseY();
		Byte getFineY();

		void ReloadScrollX();
		void ReloadScrollY();
		void IncrementScrollX();
		void IncrementScrollY();

		void setPPUCTRL(Byte val);
		void setPPUMASK(Byte val);

		Byte getPPUSTATUS();

		void setPPUADDR(Word val);
		void setPPUSCROLL(Word val);

		Byte getPPUDATA();
		void setPPUDATA(Byte val);

		Byte getOAMADDR();
		void setOAMADDR(Byte val);

		Byte getOAMDATA();
		void setOAMDATA(Byte val);

		private:
			Word v;
			Byte readBuffer;

#pragma endregion

	};


}