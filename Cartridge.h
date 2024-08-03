#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

#include "Mapper_000.h"

class Cartridge
{
public:
	Cartridge(const std::string& sFileName);
	~Cartridge();

private:
	std::vector<uint8_t> vPRGMemory;
	std::vector<uint8_t> vCHRMemory;

public:
	bool ImageValid();

	enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;

private:
	bool bImageValid = false;

	uint8_t nMapperID = 0;
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;

	std::shared_ptr <Mapper> pMapper;

public:
	bool cpuRead(uint16_t addr, uint8_t & data);
	bool cpuWrite(uint16_t addr, uint8_t data);

	// PPU bus
	bool ppuRead(uint16_t addr, uint8_t& data);
	bool ppuWrite(uint16_t addr, uint8_t data);
};

