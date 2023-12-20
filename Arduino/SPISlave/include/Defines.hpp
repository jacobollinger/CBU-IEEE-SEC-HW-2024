#ifndef DEFINES_HPP
#define DEFINES_HPP

#define DEBUG true

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