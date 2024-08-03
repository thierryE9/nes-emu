#pragma once
#include <cstdint>
#include <memory>
#include "Cartridge.h"


class olc2C02
{
public:
	olc2C02();
	~olc2C02();

private:
	// vram nametable
	uint8_t tblName[2][1024];
	uint8_t tblPalette[32];
	//uint8_t tblPattern[2][4096];

	// Main bus
	uint8_t cpuRead(uint16_t addr, bool rdonly = false);
	void cpuWrite(uint16_t addr, uint8_t data);

	// PPU bus
	uint8_t ppuRead(uint16_t addr, bool rdonly = false);
	void ppuWrite(uint16_t addr, uint8_t data);

private:
	std::shared_ptr<Cartridge> cart;

public:
	//interface
	void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void clock();

};

