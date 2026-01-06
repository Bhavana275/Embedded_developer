#include "serializer.h"
#include <stdio.h>
#include <string.h>


#define WRITE_JSON(fmt, ...)                                      \
    do {                                                         \
        int n = snprintf(output + used,                          \
                         output_size - used,                     \
                         fmt, ##__VA_ARGS__);                    \
        if (n < 0 || (size_t)n >= output_size - used) {          \
            return JSON_ERR_BUFFER_TOO_SMALL;                    \
        }                                                        \
        used += (size_t)n;                                       \
    } while (0)

JsonResult serialize_to_json(
    const GatewayPayload *input,
    char *output,
    size_t output_size
) {
    if (!input || !output || output_size == 0) {
        return JSON_ERR_INVALID_INPUT;
    }

    size_t used = 0;

    /* Open outer array */
    WRITE_JSON("[");

    /* Open gateway object */
    WRITE_JSON("{");

    /* Gateway metadata */
    WRITE_JSON(
        "\"gatewayId\":\"%s\","
        "\"date\":\"%s\","
        "\"deviceType\":\"%s\","
        "\"interval_minutes\":%d,"
        "\"total_readings\":%d,",
        input->gatewayId,
        input->date,
        input->deviceType,
        input->interval_minutes,
        input->total_readings
    );

    /* Values */
    WRITE_JSON("\"values\":{");
    WRITE_JSON("\"device_count\":%d,", input->values.device_count);
    WRITE_JSON("\"readings\":[");

    for (int i = 0; i < input->values.device_count; i++) {
    	const DeviceReading *dev = &input->values.readings[i];


        WRITE_JSON(
            "{"
            "\"media\":\"%s\","
            "\"meter\":\"%s\","
            "\"deviceId\":\"%s\","
            "\"unit\":\"%s\","
            "\"data\":[",
            dev->media,
            dev->meter,
            dev->deviceId,
            dev->unit
        );

        for (int j = 0; j < dev->data_count; j++) {
        	const MeterDataPoint *dp = &dev->data[j];


            WRITE_JSON(
                "{"
                "\"timestamp\":\"%s\","
                "\"meter_datetime\":\"%s\","
                "\"total_m3\":%.3f,"
                "\"status\":\"%s\""
                "}",
                dp->timestamp,
                dp->meter_datetime,
                dp->total_m3,
                dp->status
            );

            if (j < dev->data_count - 1) {
                WRITE_JSON(",");
            }
        }

        WRITE_JSON("]}");

        if (i < input->values.device_count - 1) {
            WRITE_JSON(",");
        }
    }

    /* Close all */
    WRITE_JSON("]");
    WRITE_JSON("}");
    WRITE_JSON("}");
    WRITE_JSON("]");

    return JSON_OK;
}
