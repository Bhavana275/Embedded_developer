/*
 * serializer.h
 *
 *  Created on: 06-Jan-2026
 *      Author: ADMIN
 */
#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <stddef.h>

/* ---------- Configuration limits ---------- */
#define MAX_DEVICES        4
#define MAX_DATA_POINTS   4

/* ---------- Result codes ---------- */
typedef enum {
    JSON_OK = 0,
    JSON_ERR_BUFFER_TOO_SMALL,
    JSON_ERR_INVALID_INPUT
} JsonResult;

/* ---------- Data structures ---------- */

/* One meter data point */
typedef struct {
    char timestamp[20];        /* "YYYY-MM-DD HH:MM" */
    char meter_datetime[20];   /* "YYYY-MM-DD HH:MM" */
    float total_m3;
    char status[8];
} MeterDataPoint;

/* One device reading */
typedef struct {
    char media[16];
    char meter[16];            /* e.g. "waterstarm" */
    char deviceId[32];
    char unit[8];              /* e.g. "m3" */

    int data_count;
    MeterDataPoint data[MAX_DATA_POINTS];
} DeviceReading;

/* Values object */
typedef struct {
    int device_count;
    DeviceReading readings[MAX_DEVICES];
} Values;

/* Root gateway payload */
typedef struct {
    char gatewayId[32];
    char date[11];             /* YYYY-MM-DD */
    char deviceType[16];
    int interval_minutes;
    int total_readings;

    Values values;
} GatewayPayload;

/* Public API */
JsonResult serialize_to_json(
    const GatewayPayload *input,
    char *output,
    size_t output_size
);

#endif /* SERIALIZER_H */
