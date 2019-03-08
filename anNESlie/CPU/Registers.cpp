#include "Registers.h"

using namespace CPU;

inline void Registers::setFlag_N_V(Byte val)
{
	if (val == 0)
		registerP |= 0b01000000;
	if (val < 0)
		registerP |= 0b10000000;
}

inline bool CPU::Registers::getFlag_N()
{
	return registerP & 0b10000000;
}

inline void CPU::Registers::setFlag_N(bool val)
{
	if (val)
		registerP |= 0b10000000;
	else
		registerP &= 0b01111111;
}

inline bool CPU::Registers::getFlag_V()
{
	return registerP & 0b01000000;
}

inline void CPU::Registers::setFlag_V(bool val)
{
	if (val)
		registerP |= 0b01000000;
	else
		registerP &= 0b10111111;
}

inline bool CPU::Registers::getFlag_Unused()
{
	return registerP & 0b00100000;
}

inline void CPU::Registers::setFlag_Unused(bool val)
{
	if (val)
		registerP |= 0b00100000;
	else
		registerP &= 0b11011111;
}

inline bool CPU::Registers::getFlag_B()
{
	return registerP & 0b00010000;
}

inline void CPU::Registers::setFlag_B(bool val)
{
	if (val)
		registerP |= 0b00010000;
	else
		registerP &= 0b11101111;
}

inline bool CPU::Registers::getFlag_D()
{
	return registerP & 0b00001000;
}

inline void CPU::Registers::setFlag_D(bool val)
{
	if (val)
		registerP |= 0b00001000;
	else
		registerP &= 0b11110111;
}

inline bool CPU::Registers::getFlag_I()
{
	return registerP & 0b00000100;
}

inline void CPU::Registers::setFlag_I(bool val)
{
	if (val)
		registerP |= 0b00000100;
	else
		registerP &= 0b11111011;
}

inline bool CPU::Registers::getFlag_Z()
{
	return registerP & 0b00000010;
}

inline void CPU::Registers::setFlag_Z(bool val)
{
	if (val)
		registerP |= 0b00000010;
	else
		registerP &= 0b11111101;
}

inline bool CPU::Registers::getFlag_C()
{
	return registerP & 0b00000001;
}

inline void CPU::Registers::setFlag_C(bool val)
{
	if (val)
		registerP |= 0b00000001;
	else
		registerP &= 0b11111110;
}


inline Byte CPU::Registers::getA()
{
	return registerA;
}

inline void CPU::Registers::setA(Byte val)
{
	registerA = val;
}

inline Byte CPU::Registers::getX()
{
	return registerX;
}

inline void CPU::Registers::setX(Byte val)
{
	registerX = val;
}

inline Byte CPU::Registers::getY()
{
	return registerY;
}

inline void CPU::Registers::setY(Byte val)
{
	registerY = val;
}

inline Byte CPU::Registers::getSP()
{
	return registerSP;
}

inline void CPU::Registers::setSP(Byte val)
{
	registerSP = val;
}

inline Byte CPU::Registers::getPC()
{
	return registerPC;
}

inline void CPU::Registers::setPC(Byte val)
{
	registerPC = val;
}

inline Byte CPU::Registers::getP()
{
	return registerP;
}

inline void CPU::Registers::setP(Byte val)
{
	registerP = val;
}
