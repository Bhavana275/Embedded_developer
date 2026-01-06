# Embedded JSON Serialization Library for w-M-Bus Gateways

## Project Overview
This project implements an embedded-friendly software library that serializes
structured smart-meter measurement data into a predefined JSON format.

The library represents a realistic firmware component in a smart-meter / w-M-Bus
data pipeline:

Measurement data → internal C data structures → JSON serialization → gateway / backend interface

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
**STM32CubeIDE (STM32 microcontrollers)**

STM32CubeIDE was chosen because it reflects real-world embedded gateway firmware
development environments and toolchains commonly used in industry.

### Programming Language
**C**

C was selected due to its suitability for embedded systems, predictable memory
usage, and fine-grained control over performance and resources.

No external JSON libraries are used.

---

## Project Structure

Inc/

└── serializer.h // Public API and data structures

Src/

├── serializer.c // JSON serialization logic

└── main.c // Demo / example application


---

## Data Model
The internal data model represents the following information:

### Gateway-level metadata
- gatewayId
- date (format: YYYY-MM-DD)
- deviceType
- interval_minutes
- total_readings

### Measurement data
- Number of devices
- List of device readings
- Each device contains:
  - media type
  - meter type
  - device ID
  - unit
  - one or more data points

Each data point contains:
- timestamp
- meter_datetime
- total meter value
- status

All data structures are defined in `serializer.h` using fixed-size buffers suitable
for embedded systems.

---
### API Characteristics

Transport-agnostic (no UART, MQTT, radio, etc. inside the library)

Serializes data into a caller-provided output buffer

Prevents buffer overflows using snprintf

Returns clear error codes for invalid input or insufficient buffer size

No dynamic memory allocation

---

### Demo / Example Application

A small example application is provided in main.c that:

Creates sample input data using the defined structures

Calls the JSON serialization library

Outputs the generated JSON using printf

Execution on target hardware is not required for this assignment. The successful
build and correct serialization logic demonstrate functional correctness.

---
### Build Instructions

Open the project in STM32CubeIDE

Select the Debug build configuration

Build the project

No external dependencies or target hardware are required.

---

### Design Decisions & Assumptions

Fixed-size buffers are used for deterministic memory usage

No dynamic memory allocation (malloc / free)

No external JSON libraries

Strict adherence to the required JSON schema

Clear separation between data model, serialization logic, and demo application


---

###  Public API & JSON Output
```c
JsonResult serialize_to_json(
    const GatewayPayload *input,
    char *output,
    size_t output_size
);

---



[
  {
    "gatewayId": "gateway_1234",
    "date": "1970-01-01",
    "deviceType": "stromleser",
    "interval_minutes": 15,
    "total_readings": 1,
    "values": {
      "device_count": 1,
      "readings": [
        {
          "media": "water",
          "meter": "waterstarm",
          "deviceId": "stromleser_50898527",
          "unit": "m3",
          "data": [
            {
              "timestamp": "1970-01-01 00:00",
              "meter_datetime": "1970-01-01 00:00",
              "total_m3": 107.752,
              "status": "OK"
            }
          ]
        }
      ]
    }
  }
]
