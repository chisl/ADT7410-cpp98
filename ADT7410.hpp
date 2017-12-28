/*
 * name:        ADT7410
 * description: ±0.5°C Accurate, 16-Bit Digital I2C Temperature Sensor
 * manuf:       Analog Devices
 * version:     0.1
 * url:         http://www.analog.com/media/en/technical-documentation/data-sheets/ADT7410.pdf
 * date:        2017-12-28
 * author       https://chisl.io/
 * file:        ADT7410.hpp
 */

#include <cinttypes>

/* Derive from class ADT7410_Base and implement the read and write functions! */

/* ADT7410: ±0.5°C Accurate, 16-Bit Digital I2C Temperature Sensor */
class ADT7410_Base
{
public:
	/* Pure virtual functions that need to be implemented in derived class: */
	virtual uint8_t read8(uint16_t address, uint16_t n=8) = 0;  // 8 bit read
	virtual void write(uint16_t address, uint8_t value, uint16_t n=8) = 0;  // 8 bit write
	virtual uint16_t read16(uint16_t address, uint16_t n=16) = 0;  // 16 bit read
	virtual void write(uint16_t address, uint16_t value, uint16_t n=16) = 0;  // 16 bit write
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG TEMPERATURE                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/* REG TEMPERATURE:
	 */
	struct TEMPERATURE
	{
		static const uint16_t __address = 0;
		
		/* Bits TLOWFLAG_LSB0: */
		/*
		 * Flags a TLOW event if the configuration register, Register Address 0x03[7] = 0 (13-bit resolution),
		 * and if comparator mode is selected through the configuration register, Register Address
		 * 0x03[4]. When the temperature value is below TLOW, this bit it set to 1.
		 * Contains the Least Significant Bit 0 of the 15-bit temperature value if the configuration
		 * register, Register Address 0x03[7] = 1 (16-bit resolution).
		 */
		struct TLOWFLAG_LSB0
		{
			static const uint16_t dflt = 0b0; // 1'b0
			static const uint16_t mask = 0b0000000000000001; // [0]
		};
		/* Bits THIGHFLAG_LSB1: */
		/*
		 * Flags a THIGH event if the configuration register, Register Address 0x03[7] = 0 (13-bit resolution),
		 * and if comparator mode is selected through the configuration register, Register Address
		 * 0x03[4]. When the temperature value is above THIGH, this bit it set to 1.
		 * Contains the Least Significant Bit 1 of the 15-bit temperature value if the configuration
		 * register, Register Address 0x03[7] = 1 (16-bit resolution).
		 */
		struct THIGHFLAG_LSB1
		{
			static const uint16_t dflt = 0b0; // 1'b0
			static const uint16_t mask = 0b0000000000000010; // [1]
		};
		/* Bits TCRITFLAG_LSB2: */
		/*
		 * Flags a TCRIT event if the configuration register, Register Address 0x03[7] = 0 (13-bit resolution),
		 * and if comparator mode is selected through the configuration register, Register Address
		 * 0x03[4]. When the temperature value exceeds TCRIT, this bit it set to 1.
		 * Contains the Least Significant Bit 2 of the 15-bit temperature value if the configuration
		 * register, Register Address 0x03[7] = 1 (16-bit resolution).
		 */
		struct TCRITFLAG_LSB2
		{
			static const uint16_t dflt = 0b0; // 1'b0
			static const uint16_t mask = 0b0000000000000100; // [2]
		};
		/* Bits TEMPERATURE: */
		/* Temperature value in twos complement format */
		struct TEMPERATURE_
		{
			static const uint16_t dflt = 0b000000000000; // 12'b0
			static const uint16_t mask = 0b0111111111111000; // [3,4,5,6,7,8,9,10,11,12,13,14]
		};
		/* Bits SIGN: */
		/* indicates if the temperature value is negative or positive */
		struct SIGN
		{
			static const uint16_t dflt = 0b0; // 1'b0
			static const uint16_t mask = 0b1000000000000000; // [15]
		};
	};
	
	/* Set register TEMPERATURE */
	void setTEMPERATURE(uint16_t value)
	{
		write(TEMPERATURE::__address, value, 16);
	}
	
	/* Get register TEMPERATURE */
	uint16_t getTEMPERATURE()
	{
		return read16(TEMPERATURE::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG Status                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Status:
	 * This 8-bit read-only register reflects the status of the overtemperature
	 * and undertemperature interrupts that can cause the CT and
	 * INT pins to go active. It also reflects the status of a temperature
	 * conversion operation. The interrupt flags in this register are
	 * reset by a read operation to the status register and/or when
	 * the temperature value returns within the temperature limits,
	 * including hysteresis. The RDY bit is reset after a read from the
	 * temperature value register. In one-shot and 1 SPS modes, the
	 * RDY bit is reset after a write to the one-shot bits.
	 */
	struct Status
	{
		static const uint16_t __address = 2;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
		/* Bits THIGH: */
		/*
		 * Set this bit to 1 when the temperature goes below the TLOW temperature limit, and if comparator
		 * mode is selected through the configuration register, Register Address 0x03[4]. The bit clears
		 * to 0 when the status register is read and/or when the temperature measured goes back above
		 * the limit set in the setpoint TLOW + THYST registers.
		 */
		struct THIGH
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits TLOW: */
		/*
		 * Set this bit to 1 when the temperature goes above the THIGH temperature limit, and if comparator
		 * mode is selected through the configuration register, Register Address 0x03[4]. The bit clears
		 * to 0 when the status register is read and/or when the temperature measured goes back
		 * below the limit set in the setpoint THIGH − THYST registers.
		 */
		struct TLOW
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits TCRIT: */
		/*
		 * Set this bit to 1 when the temperature goes above the TCRIT temperature limit, and if comparator
		 * mode is selected through the configuration register, Register Address 0x03[4]. This bit clears
		 * to 0 when the status register is read and/or when the temperature measured goes back
		 * below the limit set in the setpoint TCRIT − THYST registers.
		 */
		struct TCRIT
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits nRDY: */
		/*
		 * This bit goes low when the temperature conversion result is written into the temperature
		 * value register. It is reset to 1 when the temperature value register is read. In one-shot and 1
		 * SPS modes, this bit is reset after a write to the one-shot bits.
		 */
		struct nRDY
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b10000000; // [7]
		};
	};
	
	/* Set register Status */
	void setStatus(uint8_t value)
	{
		write(Status::__address, value, 8);
	}
	
	/* Get register Status */
	uint8_t getStatus()
	{
		return read8(Status::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                        REG Configuration                                         *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Configuration:
	 * This 8-bit read/write register stores various configuration modes
	 * for the ADT7410, including shutdown, overtemperature and
	 * undertemperature interrupts, one-shot, continuous conversion,
	 * interrupt pins polarity, and overtemperature fault queues.
	 */
	struct Configuration
	{
		static const uint16_t __address = 3;
		
		/* Bits FAULT_QUEUE: */
		/*
		 * These two bits set the number of undertemperature/overtemperature faults that can
		 * occur before setting the INT and CT pins. This helps to avoid false triggering due
		 * to temperature noise.
		 */
		struct FAULT_QUEUE
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t FAULTS_1 = 0b00; // 1 fault (default)
			static const uint8_t FAULTS_2 = 0b01; // 2 faults.
			static const uint8_t FAULTS_3 = 0b10; // 3 faults.
			static const uint8_t FAULTS_4 = 0b11; // 4 faults
		};
		/* Bits CT_PIN_POLARITY: */
		/* This bit selects the output polarity of the CT pin.  */
		struct CT_PIN_POLARITY
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000100; // [2]
			static const uint8_t ACTIVE_LOW = 0b0; // 
			static const uint8_t ACTIVE_HIGH = 0b1; // 
		};
		/* Bits INT_PIN_POLARITY: */
		/* This bit selects the output polarity of the INT pin.  */
		struct INT_PIN_POLARITY
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
			static const uint8_t ACTIVE_LOW = 0b0; // 
			static const uint8_t ACTIVE_HIGH = 0b1; // 
		};
		/* Bits INT_CT_MODE: */
		/* This bit selects between comparator mode and interrupt mode.  */
		struct INT_CT_MODE
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
			static const uint8_t INTERRUPT_MODE = 0b0; // 
			static const uint8_t COMPARATOR_MODE = 0b1; // 
		};
		/* Bits OPMODE: */
		/* These two bits set the operational mode for the ADT7410.  */
		struct OPMODE
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b01100000; // [5,6]
			static const uint8_t CONTINOUS_CONVERSIO = 0b00; // (default). When one conversion is finished, the ADT7410 starts another.
			static const uint8_t ONE_SHOT = 0b01; // Conversion time is typically 240 ms.
			static const uint8_t ONE_SPS = 0b10; // 1 SPS mode. Conversion time is typically 60 ms. This operational mode reduces the average current consumption.
			static const uint8_t SHUTDOWB = 0b11; // All circuitry except interface circuitry is powered down.
		};
		/* Bits RESOLUTION: */
		/* This bit sets up the resolution of the ADC when converting.  */
		struct RESOLUTION
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
			static const uint8_t RES_13_BIT = 0b0; // 13-bit resolution. Sign bit + 12 bits gives a temperature resolution of 0.0625°C.
			static const uint8_t RES_16_BIT = 0b1; // 16-bit resolution. Sign bit + 15 bits gives a temperature resolution of 0.0078°C.
		};
	};
	
	/* Set register Configuration */
	void setConfiguration(uint8_t value)
	{
		write(Configuration::__address, value, 8);
	}
	
	/* Get register Configuration */
	uint8_t getConfiguration()
	{
		return read8(Configuration::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG THIGH                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG THIGH:
	 * The THIGH setpoint MSB and THIGH setpoint LSB registers store
	 * the overtemperature limit value. An overtemperature event
	 * occurs when the temperature value stored in the temperature
	 * value register exceeds the value stored in this register. The INT pin
	 * is activated if an overtemperature event occurs. The temperature
	 * is stored in twos complement format with the MSB being the
	 * temperature sign bit.
	 * The default setting for the THIGH setpoint is 64°C.
	 */
	struct THIGH
	{
		static const uint16_t __address = 4;
		
		/* Bits THIGH: */
		struct THIGH_
		{
			/* Mode: */
			static const uint16_t dflt = 0b0010000000000000; // 16'h2000
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register THIGH */
	void setTHIGH(uint16_t value)
	{
		write(THIGH::__address, value, 16);
	}
	
	/* Get register THIGH */
	uint16_t getTHIGH()
	{
		return read16(THIGH::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG TLOW                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG TLOW:
	 * The TLOW setpoint MSB and TLOW setpoint LSB registers store
	 * the undertemperature limit value. An undertemperature event
	 * occurs when the temperature value stored in the temperature
	 * value register is less than the value stored in this register. The
	 * INT pin is activated if an undertemperature event occurs. The
	 * temperature is stored in twos complement format with the MSB
	 * being the temperature sign bit.
	 * The default setting for the TLOW setpoint is 10°C.
	 */
	struct TLOW
	{
		static const uint16_t __address = 6;
		
		/* Bits TLOW: */
		struct TLOW_
		{
			/* Mode: */
			static const uint16_t dflt = 0b0000010100000000; // 16'h500
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register TLOW */
	void setTLOW(uint16_t value)
	{
		write(TLOW::__address, value, 16);
	}
	
	/* Get register TLOW */
	uint16_t getTLOW()
	{
		return read16(TLOW::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG TCRIT                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG TCRIT:
	 * The TCRIT setpoint MSB and TCRIT setpoint LSB registers store
	 * the critical overtemperature limit value. A critical overtemperature
	 * event occurs when the temperature value stored in the
	 * temperature value register exceeds the value stored in this
	 * register. The CT pin is activated if a critical overtemperature
	 * event occurs. The temperature is stored in twos complement
	 * format with the MSB being the temperature sign bit.
	 * The default setting for the TCRIT limit is 147°C.
	 */
	struct TCRIT
	{
		static const uint16_t __address = 8;
		
		/* Bits TCRIT: */
		struct TCRIT_
		{
			/* Mode: */
			static const uint16_t dflt = 0b0100100110000000; // 16'h4980
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register TCRIT */
	void setTCRIT(uint16_t value)
	{
		write(TCRIT::__address, value, 16);
	}
	
	/* Get register TCRIT */
	uint16_t getTCRIT()
	{
		return read16(TCRIT::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG THYST                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG THYST:
	 * This 8-bit read/write register stores the temperature hysteresis
	 * value for the THIGH, TLOW, and TCRIT temperature limits. The
	 * temperature hysteresis value is stored in straight binary format
	 * using four LSBs. Increments are possible in steps of 1°C from
	 * 0°C to 15°C. The value in this register is subtracted from the
	 * THIGH and TCRIT values and added to the TLOW value to implement
	 * hysteresis.
	 * Default is 5°C.
	 */
	struct THYST
	{
		static const uint16_t __address = 10;
		
		/* Bits HYSTERESIS: */
		/*
		 * Hysteresis value, from 0°C to 15°C. Stored in straight binary format.
		 * The default setting is 5°C.
		 */
		struct HYSTERESIS
		{
			static const uint8_t dflt = 0b0101; // 4'b101
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0000; // 4'h0
			static const uint8_t mask = 0b11110000; // [4,5,6,7]
		};
	};
	
	/* Set register THYST */
	void setTHYST(uint8_t value)
	{
		write(THYST::__address, value, 8);
	}
	
	/* Get register THYST */
	uint8_t getTHYST()
	{
		return read8(THYST::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                              REG ID                                               *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/* REG ID:
	 */
	struct ID
	{
		static const uint16_t __address = 11;
		
		/* Bits REVISION_ID: */
		/* Revision ID Contains the silicon revision identification number  */
		struct REVISION_ID
		{
			static const uint8_t mask = 0b00000111; // [0,1,2]
		};
		/* Bits MANUFACTURER_ID: */
		/* Manufacture ID Contains the manufacturer identification number  */
		struct MANUFACTURER_ID
		{
			static const uint8_t dflt = 0b11001; // 5'b11001
			static const uint8_t mask = 0b11111000; // [3,4,5,6,7]
		};
	};
	
	/* Set register ID */
	void setID(uint8_t value)
	{
		write(ID::__address, value, 8);
	}
	
	/* Get register ID */
	uint8_t getID()
	{
		return read8(ID::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG RESET                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG RESET:
	 * Software reset: Address pointer word as a command word to reset the part and
	 * upload all default settings. The ADT7410 does not respond to the I2
	 * C bus commands (do not acknowledge) during the default
	 * values upload for approximately 200 µs.
	 */
	struct RESET
	{
		static const uint16_t __address = 47;
		
		/* Bits RESET: */
		struct RESET_
		{
			/* Mode:wt */
			static const uint8_t mask = 0b0; // []
		};
	};
	
	/* Set register RESET */
	void setRESET()
	{
		write(RESET::__address, uint8_t(0), 0);
	}
	
	/* Get register RESET */
	uint8_t getRESET()
	{
		return read8(RESET::__address, 0);
	}
	
};
