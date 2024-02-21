#ifndef DEFINES_HPP
#define DEFINES_HPP

#define DEBUG true
#define BAUDRATE 115200

#pragma region Wheel Definitions
#define WHEELS_M1_FLT 33
#define WHEELS_M1_PWM 8
#define WHEELS_M1_SLP 30
#define WHEELS_M1_DIR 25
#define WHEELS_M1_CS A15
#define WHEELS_M2_FLT 31
#define WHEELS_M2_PWM 7
#define WHEELS_M2_SLP 32
#define WHEELS_M2_DIR 23
#define WHEELS_M2_CS A14

#define WHEEL_MAX_SPEED 255

#pragma endregion

// TODO: Add arm definitions
#pragma region ADC Definitions
#define ARM_BASE_PIN
#define ARM_SHOULDER_PIN
#define ARM_WRIST_PIN
#define ARM_GRIPPER_PIN

#define ARM_SHOULDER_FEEDBACK_PIN
#define ARM_WRIST_FEEDBACK_PIN
#define ARM_GRIPPER_FEEDBACK_PIN

#define ARM_GRIPPER_OPEN
#define ARM_GRIPPER_GRIP_FUEL_TANK
#define ARM_GRIPPER_GRIP_SMALL_PACKAGE
#define ARM_GRIPPER_GRIP_LARGE_PACKAGE

#pragma endregion

#define SPI_EOT 0x04
#define SPI_BUFFER_SIZE 1UL << 8

#pragma region SPI Control Register Values
#define SPI_DATA_ORDER_MSB_FIRST 0
#define SPI_DATA_ORDER_LSB_FIRST 1

#define SPI_MASTER 1
#define SPI_SLAVE 0

#define SPI_CLOCK_POLARITY_IDLE_LOW 0
#define SPI_CLOCK_POLARITY_IDLE_HIGH 1

#define SPI_CLOCK_PHASE_SAMPLE_ON_LEADING 0
#define SPI_CLOCK_PHASE_SAMPLE_ON_TRAILING 1
#pragma endregion

#pragma region SPI Control Register Bits
#ifndef SPIE
#define SPIE 7
#endif

#ifndef SPE
#define SPE 6
#endif

#ifndef DORD
#define DORD 5
#endif

#ifndef MSTR
#define MSTR 4
#endif

#ifndef CPOL
#define CPOL 3
#endif

#ifndef CPHA
#define CPHA 2
#endif
#pragma endregion

#endif // DEFINES_HPP
