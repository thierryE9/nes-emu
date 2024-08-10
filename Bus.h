#pragma once
#include <cstdint>
#include <array>
#include "olc6502.h"
#include "olc2C02.h"
#include "Cartridge.h"
#include "olc2A03.h"

class Bus {
public:
    Bus();
    ~Bus();

public:
    olc6502 cpu;
    olc2C02 ppu;
    olc2A03 apu;
    std::array<uint8_t, 2 * 1024> cpuRam;

    std::shared_ptr<Cartridge> cart;

    uint8_t controller[2];

public:
    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

    double dAudioSample = 0.0;
    void SetSampleFrequency(uint32_t sample_rate);

private:
    double dAudioTimePerSystemSample = 0.0f;
    double dAudioTimePerNESClock = 0.0;
    double dAudioTime = 0.0;

public:
    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void reset();
    bool clock();

private:
    uint32_t nSystemClockCounter = 0;

    uint8_t controller_state[2];

    uint8_t dma_page = 0x00;
    uint8_t dma_addr = 0x00;
    uint8_t dma_data = 0x00;

    bool dma_transfer = false;
    bool dma_dummy = true;
};