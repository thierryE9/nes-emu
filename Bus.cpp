#include "Bus.h"

Bus::Bus() {
    for (auto& i : cpuRam) i = 0x00;

    cpu.ConnectBus(this);
}

Bus::~Bus() {

}

// first 2kb mirrored over 8kb (addr % 2048) for ram
// 0x2000 to 0x3FFF mirrored first 8 bytes (addr & 8)
void Bus::cpuWrite(uint16_t addr, uint8_t data) {
    if (addr >= 0x0000 && addr <= 0x1FFF)
        cpuRam[addr & 0x07FF] = data;
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        ppu.cpuWrite(addr & 0x0007, data); 
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly) {
    uint8_t data = 0x00;
    if (addr >= 0x0000 && addr <= 0x1FFF) //8kb
        data =  cpuRam[addr & 0x07FF];
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        data = ppu.cpuRead(addr & 0x0007, bReadOnly);
    return data;
}

void Bus::insertCardtridge(const std::shared_ptr<Cartridge>& cartridge)
{
    this->cart = cartridge;
    ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{
    cpu.reset();
    nSystemClockCounter = 0;
}

void Bus::clock()
{
}

