#Embedded_developer
# Embedded JSON Serialization Library for w-M-Bus Gateways

## Project Overview
This project implements an embedded-friendly software library that serializes
structured smart-meter measurement data into a predefined JSON format.

The library represents a realistic firmware component in a smart-meter / w-M-Bus
data pipeline:

Measurement data → internal C structures → JSON serialization → gateway/backend interface

w-M-Bus radio communication, OMS, encryption, and real meter interaction are
explicitly out of scope.

The focus of this project is on:
- Clean software architecture
- Clear and simple API design
- Embedded-oriented implementation
- Deterministic and safe memory usage

---

## Platform & Programming Language

### Platform
- **STM32CubeIDE (STM32 microcontrollers)**

STM32CubeIDE was chosen because it reflects real-world embedded gateway firmware
development environments and toolchains commonly used in industry.

### Programming Language
- **C**

C was selected due to its suitability for embedded systems, predictable memory
usage, and fine-grained control over performance and resources.

No external JSON libraries are used.

---

## Project Structure

