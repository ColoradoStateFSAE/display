/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This file was generated by cantools version 38.0.2 Thu Apr  4 11:59:44 2024.
 */

#ifndef R3_H
#define R3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef EINVAL
#    define EINVAL 22
#endif

/* Frame ids. */
#define R3_GROUP20_FRAME_ID (0x3e0u)
#define R3_GROUP24_FRAME_ID (0x3e4u)
#define R3_GROUP15_FRAME_ID (0x372u)
#define R3_GROUP39_FRAME_ID (0x470u)
#define R3_GROUP13_FRAME_ID (0x370u)
#define R3_GROUP5_FRAME_ID (0x368u)
#define R3_GROUP1_FRAME_ID (0x361u)
#define R3_GROUP0_FRAME_ID (0x360u)

/* Frame lengths in bytes. */
#define R3_GROUP20_LENGTH (8u)
#define R3_GROUP24_LENGTH (8u)
#define R3_GROUP15_LENGTH (8u)
#define R3_GROUP39_LENGTH (8u)
#define R3_GROUP13_LENGTH (8u)
#define R3_GROUP5_LENGTH (8u)
#define R3_GROUP1_LENGTH (8u)
#define R3_GROUP0_LENGTH (8u)

/* Extended or standard frame types. */
#define R3_GROUP20_IS_EXTENDED (0)
#define R3_GROUP24_IS_EXTENDED (0)
#define R3_GROUP15_IS_EXTENDED (0)
#define R3_GROUP39_IS_EXTENDED (0)
#define R3_GROUP13_IS_EXTENDED (0)
#define R3_GROUP5_IS_EXTENDED (0)
#define R3_GROUP1_IS_EXTENDED (0)
#define R3_GROUP0_IS_EXTENDED (0)

/* Frame cycle times in milliseconds. */


/* Signal choices. */


/**
 * Signals in message group20.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group20_t {
    /**
     * 20-01
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t coolant_temperature;

    /**
     * 20-02
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t air_temperature;

    /**
     * 20-03
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t fuel_temperature;

    /**
     * 20-04
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t oil_temperature;
};

/**
 * Signals in message group24.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group24_t {
    /**
     * 24-01
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t neutral_switch;

    /**
     * 24-03
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t gear_switch;

    /**
     * 24-07
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t clutch_switch;

    /**
     * 24-08
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t oil_pressure_light;

    /**
     * 24-12
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t flat_shift_switch;

    /**
     * 24-25
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t check_engine_light;
};

/**
 * Signals in message group15.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group15_t {
    /**
     * 15-01
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t battery_voltage;

    /**
     * 15-02
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t target_boost_level;

    /**
     * 15-03
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t barometric_pressure;
};

/**
 * Signals in message group39.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group39_t {
    /**
     * 39-01
     *
     * Range: -
     * Scale: 0.001
     * Offset: 0
     */
    uint16_t wideband_overall;

    /**
     * 39-02
     *
     * Range: -
     * Scale: 0.001
     * Offset: 0
     */
    uint16_t wideband_bank_1;

    /**
     * 39-03
     *
     * Range: -
     * Scale: 0.001
     * Offset: 0
     */
    uint16_t wideband_bank_2;

    /**
     * 39-04
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int8_t gear_selector_position;

    /**
     * 39-05
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int8_t gear;
};

/**
 * Signals in message group13.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group13_t {
    /**
     * 13-01
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t vehicle_speed;

    /**
     * 13-02
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    int16_t intake_cam_angle_1;

    /**
     * 13-03
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    int16_t intake_cam_angle_2;
};

/**
 * Signals in message group5.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group5_t {
    /**
     * 05-01
     *
     * Range: -
     * Scale: 0.001
     * Offset: 0
     */
    uint16_t wideband_sensor_1;

    /**
     * 05-02
     *
     * Range: -
     * Scale: 0.001
     * Offset: 0
     */
    uint16_t wideband_sensor_2;

    /**
     * 05-03
     *
     * Range: -
     * Scale: 0.001
     * Offset: 0
     */
    uint16_t wideband_sensor_3;

    /**
     * 05-04
     *
     * Range: -
     * Scale: 0.001
     * Offset: 0
     */
    uint16_t wideband_sensor_4;
};

/**
 * Signals in message group1.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group1_t {
    /**
     * 01-01
     *
     * Range: -
     * Scale: 0.1
     * Offset: -101.3
     */
    uint16_t fuel_pressure;

    /**
     * 01-02
     *
     * Range: -
     * Scale: 0.1
     * Offset: -101.3
     */
    uint16_t oil_pressure;

    /**
     * 01-03
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t engine_demand;

    /**
     * 01-04
     *
     * Range: -
     * Scale: 0.1
     * Offset: -101.3
     */
    uint16_t wastegate_pressure;
};

/**
 * Signals in message group0.
 *
 * All signal values are as on the CAN bus.
 */
struct r3_group0_t {
    /**
     * 00-01
     *
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t rpm;

    /**
     * 00-02
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t manifold_pressure;

    /**
     * 00-03
     *
     * Range: -
     * Scale: 0.1
     * Offset: 0
     */
    uint16_t throttle_position;

    /**
     * 00-04
     *
     * Range: -
     * Scale: 0.1
     * Offset: -101.3
     */
    uint16_t coolant_pressure;
};

/**
 * Pack message group20.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group20_pack(
    uint8_t *dst_p,
    const struct r3_group20_t *src_p,
    size_t size);

/**
 * Unpack message group20.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group20_unpack(
    struct r3_group20_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group20_coolant_temperature_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group20_coolant_temperature_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group20_coolant_temperature_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group20_air_temperature_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group20_air_temperature_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group20_air_temperature_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group20_fuel_temperature_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group20_fuel_temperature_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group20_fuel_temperature_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group20_oil_temperature_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group20_oil_temperature_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group20_oil_temperature_is_in_range(uint16_t value);

/**
 * Pack message group24.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group24_pack(
    uint8_t *dst_p,
    const struct r3_group24_t *src_p,
    size_t size);

/**
 * Unpack message group24.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group24_unpack(
    struct r3_group24_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t r3_group24_neutral_switch_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group24_neutral_switch_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group24_neutral_switch_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t r3_group24_gear_switch_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group24_gear_switch_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group24_gear_switch_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t r3_group24_clutch_switch_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group24_clutch_switch_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group24_clutch_switch_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t r3_group24_oil_pressure_light_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group24_oil_pressure_light_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group24_oil_pressure_light_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t r3_group24_flat_shift_switch_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group24_flat_shift_switch_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group24_flat_shift_switch_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t r3_group24_check_engine_light_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group24_check_engine_light_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group24_check_engine_light_is_in_range(uint8_t value);

/**
 * Pack message group15.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group15_pack(
    uint8_t *dst_p,
    const struct r3_group15_t *src_p,
    size_t size);

/**
 * Unpack message group15.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group15_unpack(
    struct r3_group15_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group15_battery_voltage_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group15_battery_voltage_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group15_battery_voltage_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group15_target_boost_level_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group15_target_boost_level_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group15_target_boost_level_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group15_barometric_pressure_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group15_barometric_pressure_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group15_barometric_pressure_is_in_range(uint16_t value);

/**
 * Pack message group39.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group39_pack(
    uint8_t *dst_p,
    const struct r3_group39_t *src_p,
    size_t size);

/**
 * Unpack message group39.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group39_unpack(
    struct r3_group39_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group39_wideband_overall_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group39_wideband_overall_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group39_wideband_overall_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group39_wideband_bank_1_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group39_wideband_bank_1_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group39_wideband_bank_1_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group39_wideband_bank_2_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group39_wideband_bank_2_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group39_wideband_bank_2_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int8_t r3_group39_gear_selector_position_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group39_gear_selector_position_decode(int8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group39_gear_selector_position_is_in_range(int8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int8_t r3_group39_gear_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group39_gear_decode(int8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group39_gear_is_in_range(int8_t value);

/**
 * Pack message group13.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group13_pack(
    uint8_t *dst_p,
    const struct r3_group13_t *src_p,
    size_t size);

/**
 * Unpack message group13.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group13_unpack(
    struct r3_group13_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group13_vehicle_speed_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group13_vehicle_speed_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group13_vehicle_speed_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t r3_group13_intake_cam_angle_1_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group13_intake_cam_angle_1_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group13_intake_cam_angle_1_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t r3_group13_intake_cam_angle_2_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group13_intake_cam_angle_2_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group13_intake_cam_angle_2_is_in_range(int16_t value);

/**
 * Pack message group5.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group5_pack(
    uint8_t *dst_p,
    const struct r3_group5_t *src_p,
    size_t size);

/**
 * Unpack message group5.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group5_unpack(
    struct r3_group5_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group5_wideband_sensor_1_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group5_wideband_sensor_1_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group5_wideband_sensor_1_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group5_wideband_sensor_2_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group5_wideband_sensor_2_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group5_wideband_sensor_2_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group5_wideband_sensor_3_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group5_wideband_sensor_3_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group5_wideband_sensor_3_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group5_wideband_sensor_4_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group5_wideband_sensor_4_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group5_wideband_sensor_4_is_in_range(uint16_t value);

/**
 * Pack message group1.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group1_pack(
    uint8_t *dst_p,
    const struct r3_group1_t *src_p,
    size_t size);

/**
 * Unpack message group1.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group1_unpack(
    struct r3_group1_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group1_fuel_pressure_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group1_fuel_pressure_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group1_fuel_pressure_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group1_oil_pressure_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group1_oil_pressure_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group1_oil_pressure_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group1_engine_demand_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group1_engine_demand_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group1_engine_demand_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group1_wastegate_pressure_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group1_wastegate_pressure_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group1_wastegate_pressure_is_in_range(uint16_t value);

/**
 * Pack message group0.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int r3_group0_pack(
    uint8_t *dst_p,
    const struct r3_group0_t *src_p,
    size_t size);

/**
 * Unpack message group0.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int r3_group0_unpack(
    struct r3_group0_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group0_rpm_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group0_rpm_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group0_rpm_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group0_manifold_pressure_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group0_manifold_pressure_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group0_manifold_pressure_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group0_throttle_position_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group0_throttle_position_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group0_throttle_position_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t r3_group0_coolant_pressure_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double r3_group0_coolant_pressure_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool r3_group0_coolant_pressure_is_in_range(uint16_t value);


#ifdef __cplusplus
}
#endif

#endif
