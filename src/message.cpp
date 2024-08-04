#include <cstring>
#include <iostream>

#include "message.h"

Message::Message(const uint8_t data[] /* = nullptr */, const uint32_t &length /* = 0 */)
    : m_size(length)
{
    if (data) {
        std::memcpy(m_data, data, max_length);
        m_writeMode = false;
    } else {
        m_writeMode = true;
    }
}


uint8_t Message::readU8()
{
    if (!hasU8()) throw std::invalid_argument("does not have u8");

    return m_data[m_pointer++];
}

uint16_t Message::readU16()
{
    if (!hasU16()) throw std::invalid_argument("does not have u16");

    uint16_t value = *reinterpret_cast<uint16_t*>(&m_data[m_pointer]);
    m_pointer += 2;
    return value;
}

uint32_t Message::readU32()
{
    if (!hasU32()) throw std::invalid_argument("does not have u32");

    uint32_t value = *reinterpret_cast<uint32_t*>(&m_data[m_pointer]);
    m_pointer += 4;
    return value;
}

std::string Message::readString()
{
    if (!hasString()) throw std::invalid_argument("does not have string");

    uint32_t size = readU32();
    std::string message(reinterpret_cast<const char*>(&m_data[m_pointer]), size);
    m_pointer += size;
    return message;
}

std::string Message::readRestAsString()
{
    if (m_writeMode) throw std::invalid_argument("wrong mode");

    uint32_t size = max_length - m_pointer;
    std::string message(reinterpret_cast<const char*>(&m_data[m_pointer]), size);
    m_pointer += size;
    return message;
}


bool Message::hasU8() const
{
    return containsBytes(1);
}

bool Message::hasU16() const
{
    return containsBytes(2);
}

bool Message::hasU32() const
{
    return containsBytes(4);
}

bool Message::hasString() const
{
    if (!hasU32()) return false;
    uint32_t value = *reinterpret_cast<const uint32_t*>(&m_data[m_pointer]);
    return containsBytes(value + 4);
}

bool Message::containsBytes(const uint32_t &numberOfBytes) const
{
    if (m_writeMode) throw std::invalid_argument("wrong mode");
    return (m_pointer + numberOfBytes) <= m_size;
}


void Message::writeU8(const uint8_t &byte)
{
    if (!m_writeMode) throw std::invalid_argument("wrong mode");

    m_data[m_pointer++] = byte;
}

void Message::writeU16(const uint16_t &value)
{
    if (!m_writeMode) throw std::invalid_argument("wrong mode");

    *reinterpret_cast<uint16_t*>(&m_data[m_pointer]) = value;
    m_pointer += 2;
}

void Message::writeU32(const uint32_t &value)
{
    if (!m_writeMode) throw std::invalid_argument("wrong mode");

    *reinterpret_cast<uint32_t*>(&m_data[m_pointer]) = value;
    m_pointer += 4;
}

void Message::writeString(const std::string &message)
{
    if (!m_writeMode) throw std::invalid_argument("wrong mode");

    uint32_t size = message.size();

    writeU32(size);
    std::memcpy(&m_data[m_pointer], message.data(), size);
    m_pointer += size;
}
