#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

class Cartridge
{
public:
	Cartridge(const std::string& sFileName);
	~Cartridge();

private:
	std::vector<uint8_t> vPRGMemory;
	std::vector<uint8_t> vCHRMemory;

	uint8_t nMapperID = 0;
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;

public:
	bool cpuRead(uint16_t addr, bool rdonly = false);
	bool cpuWrite(uint16_t addr, uint8_t data);

	// PPU bus
	bool ppuRead(uint16_t addr, bool rdonly = false);
	bool ppuWrite(uint16_t addr, uint8_t data);
};

