#pragma once
#include <cstdint>
#include <memory>
#include "Cartridge.h"
#include "olcPixelGameEngine.h"


class olc2C02
{
public:
	olc2C02();
	~olc2C02();

private:
	// vram nametable
	uint8_t tblName[2][1024];
	uint8_t tblPalette[32];
	uint8_t tblPattern[2][4096];

public:
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

private:
	olc::Pixel  palScreen[0x40];
	// In Video
	// olc::Sprite sprScreen = olc::Sprite(256, 240);
	// olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
	// olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

	// Changed To for API breaking subsequent PGE Update
	olc::Sprite* sprScreen;
	olc::Sprite* sprNameTable[2];
	olc::Sprite* sprPatternTable[2];

public:
	// Debugging Utilities
	olc::Sprite& GetScreen();
	olc::Sprite& GetNameTable(uint8_t i);
	olc::Sprite& GetPatternTable(uint8_t i, uint8_t palette);
	olc::Pixel& GetColourFromPaletteRam(uint8_t palette, uint8_t pixel);

	bool frame_complete = false;

private:
	int16_t scanline = 0;
	int16_t cycle = 0;

	union {
		struct {
			uint8_t unused : 5;
			uint8_t sprite_overflow : 1;
			uint8_t sprize_zero_hit : 1;
			uint8_t vertical_black : 1;
		};
		uint8_t reg;
	} status;

	union {
		struct {
			uint8_t grayscale : 1;
			uint8_t render_background_left : 1;
			uint8_t render_sprited_left : 1;
			uint8_t render_background : 1;
			uint8_t render_sprites : 1;
			uint8_t enhance_red : 1;
			uint8_t enhance_green : 1;
			uint8_t enhance_blue : 1;
		};
		uint8_t reg;
	} mask;

	union PPUCTRL {
		struct {
			uint8_t nametable_x : 1;
			uint8_t nametable_y : 1;
			uint8_t increment_mode : 1;
			uint8_t pattern_sprite : 1;
			uint8_t pattern_background : 1;
			uint8_t sprite_size : 1;
			uint8_t slave_mode : 1;
			uint8_t enable_nmi : 1;
		};
		uint8_t reg;
	} control;
};




