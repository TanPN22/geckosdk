/***************************************************************************//**
 * @file
 * @brief See @ref board for detailed documentation.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
/** @addtogroup board
 *  @brief Functions and definitions specific to the breakout board.
 *
 * The EM35x has the following example GPIO configuration.
 * This board file and the default HAL setup reflects this configuration.
 * - PA0 - SC2MOSI
 * - PA1 - SC2MISO
 * - PA2 - SC2SCLK
 * - PA3 - SC2nSSEL
 * - PA4 - PTI_EN
 * - PA5 - PTI_DATA
 * - PA6 - LED (on RCM), or Radio HoldOff
 * - PA7 - LED (on RCM)
 * - PB0 - Power Amplifier shutdown control / TRACEDATA2
 * - PB1 - SC1TXD
 * - PB2 - SC1RXD
 * - PB3 - SC1nCTS
 * - PB4 - SC1nRTS
 * - PB5 - TEMP_SENSE
 * - PB6 - Button (IRQB fixed to PB6)
 * - PB7 - Buzzer (also used for DataFlash Enable)
 * - PC0 - JTAG (JRST) / TRACEDATA1
 * - PC1 - Power Amplifier antenna select control / TRACEDATA3
 * - PC2 - JTAG (JTDO) / SWO / TRACEDATA0
 * - PC3 - JTAG (JTDI) / TRACECLK
 * - PC4 - JTAG (JTMS) / SWDIO
 * - PC5 - LED (on BoB)
 * - PC6 - Button (IRQC pointed to PC6)
 * - PC7 - TEMP_EN
 * - PD0 - UNUSED
 * - PD1 - n/c
 * - PD2 - n/c
 * - PD3 - n/c
 * - PD4 - n/c
 * - PD5 - UNUSED
 * - PD6 - UNUSED
 * - PD7 - UNUSED
 * - PE0 - n/c
 * - PE1 - n/c
 * - PE2 - n/c
 * - PE3 - n/c
 *
 *@{
 */

#ifndef __BOARD_H__
#define __BOARD_H__

/** @name Custom Baud Rate Definitions
 *
 * The following define is used with defining a custom baud rate for the UART.
 * This define provides a simple hook into the definition of
 * the baud rates used with the UART.  The baudSettings[] array in uart.c
 * links the BAUD_* defines with the actual register values needed for
 * operating the UART.  The array baudSettings[] can be edited directly for a
 * custom baud rate or another entry (the register settings) can be provided
 * here with this define.
 */
//@{

/**
 * @brief This define is the register setting for generating a baud of
 * 921600.  Refer to the EM35x datasheet's discussion on UART baud rates for
 * the equation used to derive this value.
 */
#define EMBER_SERIAL_BAUD_CUSTOM  13
//@} //END OF CUSTOM BAUD DEFINITIONS

/** @name LED Definitions
 *
 * The following are used to aid in the abstraction with the LED
 * connections.  The microcontroller-specific sources use these
 * definitions so they are able to work across a variety of boards
 * which could have different connections.  The names and ports/pins
 * used below are intended to match with a schematic of the system to
 * provide the abstraction.
 *
 * The ::HalBoardLedPins enum values should always be used when manipulating the
 * state of LEDs, as they directly refer to the GPIOs to which the LEDs are
 * connected.
 *
 * \b Note: LEDs 0 and 1 are on the RCM.
 *
 * \b Note: LED 2 is on the breakout board (dev0680).
 *
 * \b Note: LED 3 simply redirects to LED 2.
 *
 * \b Note: LEDs are defined for debugging purposes; can be overridden.
 */
//@{

/**
 * @brief Assign each GPIO with an LED connected to a convenient name.
 * ::BOARD_ACTIVITY_LED and ::BOARD_HEARTBEAT_LED provide a further layer of
 * abstraction on top of the 3 LEDs for verbose coding.
 */
enum HalBoardLedPins {
  BOARDLED0 = PORTA_PIN(6),
  BOARDLED1 = PORTA_PIN(7),
  BOARDLED2 = PORTC_PIN(5),
  BOARDLED3 = BOARDLED2,
  BOARD_ACTIVITY_LED  = BOARDLED0,
  BOARD_HEARTBEAT_LED = BOARDLED1
};

/** @} END OF LED DEFINITIONS  */

/** @name Button Definitions
 *
 * The following are used to aid in the abstraction with the Button
 * connections.  The microcontroller-specific sources use these
 * definitions so they are able to work across a variety of boards
 * which could have different connections.  The names and ports/pins
 * used below are intended to match with a schematic of the system to
 * provide the abstraction.
 *
 * The BUTTONn macros should always be used with manipulating the buttons
 * as they directly refer to the GPIOs to which the buttons are connected.
 *
 * @note The GPIO number must match the IRQ letter
 */
//@{

/**
 * @brief The actual GPIO BUTTON0 is connected to.  This define should
 * be used whenever referencing BUTTON0.
 */
#define BUTTON0             PORTB_PIN(6)

/**
 * @brief The GPIO input register for BUTTON0.
 */
#define BUTTON0_IN          (GPIO->P[1].IN)

/**
 * @brief Point the proper IRQ at the desired pin for BUTTON0.
 * @note IRQB is fixed and as such does not need any selection operation.
 */
#define BUTTON0_SEL()       do {} while (0)

/**
 * @brief The interrupt service routine for BUTTON0.
 */
#define BUTTON0_ISR         halIrqBIsr

/**
 * @brief The interrupt configuration register for BUTTON0.
 */
#define BUTTON0_INTCFG      (EVENT_GPIO->CFGB)

/**
 * @brief The interrupt enable bit for BUTTON0.
 */
//For CMSIS, needs to be compatible with NVIC_EnableIRQ(IRQB_IRQn);
#define BUTTON0_INT_EN_IRQN IRQB_IRQn
//For CMSIS, needs to be compatible with registers of NVIC_Type.
#define BUTTON0_INT_EN_BIT  BIT32(BUTTON0_INT_EN_IRQN)

/**
 * @brief The interrupt flag bit for BUTTON0.
 */
#define BUTTON0_FLAG_BIT    EVENT_GPIO_FLAG_IRQB

/**
 * @brief The missed interrupt bit for BUTTON0.
 */
#define BUTTON0_MISS_BIT    EVENT_MISS_MISS_IRQB

/**
 * @brief The actual GPIO BUTTON1 is connected to.  This define should
 * be used whenever referencing BUTTON1.
 */
#define BUTTON1             PORTC_PIN(6)

/**
 * @brief The GPIO input register for BUTTON1.
 */
#define BUTTON1_IN          (GPIO->P[2].IN)

/**
 * @brief Point the proper IRQ at the desired pin for BUTTON1.
 * @note For this board, IRQC is pointed at PC6
 */
#define BUTTON1_SEL()       do { GPIO->IRQCSEL = PORTC_PIN(6); } while (0)

/**
 * @brief The interrupt service routine for BUTTON1.
 */
#define BUTTON1_ISR         halIrqCIsr

/**
 * @brief The interrupt configuration register for BUTTON1.
 */
#define BUTTON1_INTCFG      (EVENT_GPIO->CFGC)

/**
 * @brief The interrupt enable bit for BUTTON1.
 */
//For CMSIS, needs to be compatible with NVIC_EnableIRQ(IRQC_IRQn);
#define BUTTON1_INT_EN_IRQN IRQC_IRQn
//For CMSIS, needs to be compatible with registers of NVIC_Type.
#define BUTTON1_INT_EN_BIT  BIT32(BUTTON1_INT_EN_IRQN)

/**
 * @brief The interrupt flag bit for BUTTON1.
 */
#define BUTTON1_FLAG_BIT    EVENT_GPIO_FLAG_IRQC

/**
 * @brief The missed interrupt bit for BUTTON1.
 */
#define BUTTON1_MISS_BIT    EVENT_MISS_MISS_IRQC
//@} //END OF BUTTON DEFINITIONS

/** @name USB Power State
 *
 * Define if the USB is self powered or bus powered since the configuration
 * descriptor needs to report to the host the powered state.
 *
 * @note VBUS Monitoring is required for USB to function when the EM358 device
 * is configured as self-powered.
 */
//@{

/**
 * @brief The USB power state.
 *
 * Set the define USB_SELFPWRD_STATE:
 *   0 if the device is bus powered.
 *   1 if the device self powered.
 */
#ifdef USB_BUSPWRD
#define USB_SELFPWRD_STATE (0)
#else
#define USB_SELFPWRD_STATE (1)
#endif
//@}

/** @name USB Remote Wakeup Enable
 *
 * If the USB device needs to awake the host from suspend, then it needs
 * to have remote wakeup enable.
 *
 * @note The host can deny remote wakeup, keeping the device in suspend.
 *
 * If the device has remote wakeup enabled the configuration descriptor
 * needs to report this fact to the host.  Additionally, the USB core
 * in the chip needs to be directly told.  Set the define
 * USB_REMOTEWKUPEN_STATE to 0 if remote wake is disabled or 1 if enabled.
 */
//@{

/**
 * @brief USB Remote Wakeup Enable
 *
 * Set the define USB_REMOTEWKUPEN_STATE:
 *   0 remote wakeup is disabled.
 *   1 remote wakeup is enabled.
 */
#define USB_REMOTEWKUPEN_STATE (0)
//@}

/** @name USB Maximum Power Consumption
 *
 * The USB device must report the maximum power it will draw from the bus.
 * This is done via the bMaxPower parameter in the Configuration Descriptor
 * reported to the host.  The value used is in units of 2mA.
 *
 * Self-powered devices are low power devices and must draw less than 100mA.
 *
 * Systems that have components such as a FEM are likely to consume more than
 * 100mA and are considered high power and therefore must be bus-powered.
 */
//@{

/**
 * @brief USB Max Power parameter (bMaxPower) the driver will report to the
 * host in the Configuration Descriptor.
 */
#define USB_MAX_POWER (50)
//@}

/** @name USB Enumeration Control
 *
 * The following are used to aid in the abstraction of which GPIO is
 * used for controlloing the pull-up resistor for enumeation.
 *
 * The hardware setup connects the D+ signal to a GPIO via a 1.5kOhm
 * pull-up resistor.  Any GPIO can be used since it just needs to be a
 * simple push-pull output configuration.
 */
//@{

/**
 * @brief The actual GPIO ENUMCTRL is connected to.  The GPIO only needs to
 * be a simple push-pull output or input.
 */
#define ENUMCTRL  PORTA_PIN(2)

/**
 * @brief Set the GPIO's configuration to the provided state.  The two
 * states used are GPIO_P_CFGz_Pxy_OUT when the device is enumerated and GPIO_P_CFGz_Pxy_IN
 * when the device is not enumerated.
 */
#define ENUMCTRL_SETCFG(cfg) do { SET_CMSIS_REG_FIELD(GPIO->P[0].CFGL, \
                                                      GPIO_P_CFGL_Px2, \
                                                      cfg);            \
} while (0)

/**
 * @brief When the GPIO used for enumeration is configured as push-pull, this
 * macro makes it easy to set the output state high.
 */
#define ENUMCTRL_SET()       do { GPIO->P[0].SET = GPIO_P_SET_Px2; } while (0)

/**
 * @brief When the GPIO used for enumeration is configured as push-pull, this
 * macro makes it easy to clear the output state low.
 */
#define ENUMCTRL_CLR()       do { GPIO->P[0].CLR = GPIO_P_CLR_Px2; } while (0)
//@} //USB Enumeration Control

/** @name USB VBUS Monitoring Support
 *
 * @note VBUS Monitoring is required for USB to function when the EM358 device
 * is configured as self-powered.
 *
 * The following are used to aid in the abstraction of which
 * GPIO and IRQ is used for VBUS Monitoring.
 *
 * Remember that IRQA and IRQB are fixed to GPIO PB0 and PB6 respectively
 * while IRQC and IRQD can be assigned to any GPIO.  Since USB's D- and D+
 * data pins are fixed to PA0 and PA1 respectively, SC2 can't be used so it
 * makes sense to allocate PA2 for enumeration control and PA3 for VBUS
 * monitoring.  Therefore, using PA3 for VBUS monitoring requires IRQC or IRQD.
 *
 * The driver will only try to use VBUSMON functionality if USB_SELFPWRD_STATE
 * is set to 1.
 */
//@{

/**
 * @brief The actual GPIO VBUSMON is connected to.  Remember that other
 * pieces might want to use PA3.
 *
 * Leaving VBUSMON undefined will keep VBUS Monitoring functionality
 * from being compiled in and not conflict with other pieces that
 * might want to use the GPIO or IRQ that VBUS Monitoring needs.
 */
//#define VBUSMON  GPIO_P_IN_Px3

/**
 * @brief The GPIO input register for VBUSMON.
 */
#define VBUSMON_IN          (GPIO->P[0].IN)

/**
 * @brief The GPIO configuration needed for VBUSMON.  The configuration
 * needs to be a simple input that will monitor for edge tansitions.
 */
#define VBUSMON_SETCFG() do { SET_REG_FIELD(GPIO->P[0].CFGL, PA3_CFG, GPIO_P_CFGz_Pxy_IN); } while (0)

/**
 * @brief Point the proper IRQ at the desired pin for VBUSMON.  Remember that
 * other pieces that might want to use IRQC.
 * @note For this board, IRQC is pointed at PA3.
 */
#define VBUSMON_SEL()       do { GPIO->IRQDSEL = PORTA_PIN(3); } while (0)

/**
 * @brief The interrupt service routine for VBUSMON.  Remember that
 * other pieces that might want to use IRQC.
 */
#define VBUSMON_ISR         halIrqDIsr

/**
 * @brief The interrupt configuration register for VBUSMON.
 */
#define VBUSMON_INTCFG      (EVENT_GPIO->CFGD)

/**
 * @brief The interrupt enable bit for VBUSMON.
 */
//For CMSIS, needs to be compatible with NVIC_EnableIRQ(IRQD_IRQn);
#define VBUSMON_INT_EN_IRQN IRQD_IRQn
//For CMSIS, needs to be compatible with registers of NVIC_Type.
#define VBUSMON_INT_EN_BIT  BIT32(VBUSMON_INT_EN_IRQN)

/**
 * @brief The interrupt flag bit for VBUSMON.
 */
#define VBUSMON_FLAG_BIT    EVENT_GPIO_FLAG_IRQD

/**
 * @brief The missed interrupt bit for VBUSMON.
 */
#define VBUSMON_MISS_BIT    EVENT_MISS_MISS_IRQD
//@} //USB VBUS Monitoring Support

/** @name Radio HoldOff
 *
 * When ::RADIO_HOLDOFF is defined, the GPIO configuration
 * will be initially setup by halInit() to enable Radio HoldOff
 * support on the designated RHO_GPIO as an input, replacing use
 * of that pin's default configuration.
 *
 * @note This define will override other settings for the RHO_GPIO.
 *
 * @note Radio HoldOff can also be enabled/disabled at runtime
 * via halSetRadioHoldOff().
 * The ::RADIO_HOLDOFF definition just controls the default
 * configuration at boot.
 */
//@{

/**
 * @brief This define does not equate to anything.  It is used as a
 * trigger to enable Radio HoldOff support.
 */
//#define RADIO_HOLDOFF  // Configure Radio HoldOff at bootup
//@} //END OF RADIO HOLDOFF

/** @name Radio HoldOff Configuration Definitions
 *
 * The following are used to aid in the abstraction with Radio
 * HoldOff (RHO).  The microcontroller-specific sources use these
 * definitions so they are able to work across a variety of boards
 * which could have different connections.  The names and ports/pins
 * used below are intended to match with a schematic of the system to
 * provide the abstraction.
 *
 * The Radio HoldOff input GPIO is abstracted like BUTTON0/1.
 */
//@{

/**
 * @brief The actual GPIO used to control Radio HoldOff.
 *
 * @note If ::RHO_GPIO is not defined, then Radio HoldOff
 * support will not be built in even for runtime use.
 */
#define RHO_GPIO              PORTA_PIN(6)

/**
 * @brief The GPIO signal level to assert Radio HoldOff (1=high, 0=low).
 */
#define RHO_ASSERTED          1

/**
 * @brief The GPIO configuration register for Radio HoldOff.
 */
#define RHO_CFG               (GPIO->P[0].CFGH)

/**
 * @brief The GPIO input register for Radio HoldOff.
 */
#define RHO_IN                (GPIO->P[0].IN)

/**
 * @brief The GPIO output register for Radio HoldOff.
 */
#define RHO_OUT               (GPIO->P[0].OUT)

/**
 * @brief Point the proper IRQ at the desired pin for Radio HoldOff.
 * Remember there may be other things that might want to use this IRQ.
 */
#define RHO_SEL()             do { GPIO->IRQDSEL = RHO_GPIO; } while (0)

/**
 * @brief The interrupt service routine for Radio HoldOff.
 * Remember there may be other things that might want to use this IRQ.
 */
#define RHO_ISR               halIrqDIsr

/**
 * @brief The interrupt configuration register for Radio HoldOff.
 */
#define RHO_INTCFG            (EVENT_GPIO->CFGD)

/**
 * @brief The interrupt enable bit for Radio HoldOff.
 */
//For CMSIS, needs to be compatible with NVIC_EnableIRQ(IRQD_IRQn);
#define RHO_INT_EN_IRQN IRQD_IRQn
//For CMSIS, needs to be compatible with registers of NVIC_Type.
#define RHO_INT_EN_BIT  BIT32(RHO_INT_EN_IRQN)

/**
 * @brief The interrupt flag bit for Radio HoldOff.
 */
#define RHO_FLAG_BIT          EVENT_GPIO_FLAG_IRQD

/**
 * @brief The missed interrupt bit for Radio HoldOff.
 */
#define RHO_MISS_BIT          EVENT_MISS_MISS_IRQD

/** @brief Configuration of GPIO for Radio HoldOff operation
 */
#define PWRUP_CFG_DFL_RHO_FOR_RHO   GPIO_P_CFGz_Pxy_IN_PUD
#define PWRUP_OUT_DFL_RHO_FOR_RHO   GPIO_P_OUT_Pxy_PULLDOWN /* Deassert */
#define PWRDN_CFG_DFL_RHO_FOR_RHO   GPIO_P_CFGz_Pxy_IN_PUD
#define PWRDN_OUT_DFL_RHO_FOR_RHO   GPIO_P_OUT_Pxy_PULLDOWN /* Deassert */

/** @brief Configuration of GPIO for default behavior
 */
#define PWRUP_CFG_DFL_RHO_FOR_DFL   GPIO_P_CFGz_Pxy_OUT
#define PWRUP_OUT_DFL_RHO_FOR_DFL   1 /* LED default off */
#define PWRDN_CFG_DFL_RHO_FOR_DFL   GPIO_P_CFGz_Pxy_OUT
#define PWRDN_OUT_DFL_RHO_FOR_DFL   1 /* LED off */

/** @brief The following definitions are helpers for managing
 *  Radio HoldOff and should not be modified.
 */
#if     (defined(RADIO_HOLDOFF) && defined(RHO_GPIO))
// Initial bootup configuration is for Radio HoldOff
  #define PWRUP_CFG_DFL_RHO           PWRUP_CFG_DFL_RHO_FOR_RHO
  #define PWRUP_OUT_DFL_RHO           PWRUP_OUT_DFL_RHO_FOR_RHO
  #define PWRDN_CFG_DFL_RHO           PWRDN_CFG_DFL_RHO_FOR_RHO
  #define PWRDN_OUT_DFL_RHO           PWRDN_OUT_DFL_RHO_FOR_RHO
  #define halInternalInitRadioHoldOff() halSetRadioHoldOff(true)
#else//!(defined(RADIO_HOLDOFF) && defined(RHO_GPIO))
// Initial bootup configuration is for default
  #define PWRUP_CFG_DFL_RHO           PWRUP_CFG_DFL_RHO_FOR_DFL
  #define PWRUP_OUT_DFL_RHO           PWRUP_OUT_DFL_RHO_FOR_DFL
  #define PWRDN_CFG_DFL_RHO           PWRDN_CFG_DFL_RHO_FOR_DFL
  #define PWRDN_OUT_DFL_RHO           PWRDN_OUT_DFL_RHO_FOR_DFL
  #define halInternalInitRadioHoldOff() /* no-op */
#endif//(defined(RADIO_HOLDOFF) && defined(RHO_GPIO))

#ifdef  RHO_GPIO

  #define ADJUST_GPIO_CONFIG_DFL_RHO(enableRadioHoldOff)  do {                                 \
    DECLARE_INTERRUPT_STATE;  /* Must read-modify-write so to be safe disable interrupts */    \
    DISABLE_INTERRUPTS();                                                                      \
    if (enableRadioHoldOff) {     /* Radio HoldOff */                                          \
      /* Actual register state */                                                              \
      /*halGpioSetConfig(RHO_CFG, PWRUP_CFG_DFL_RHO_FOR_RHO);*/                                \
      RHO_CFG = RHO_CFG                                                                        \
                & ~(0x000F                   << ((RHO_GPIO & 3) * 4))                          \
                | (PWRUP_CFG_DFL_RHO_FOR_RHO << ((RHO_GPIO & 3) * 4));                         \
      RHO_OUT = RHO_OUT                                                                        \
                & ~(0x0001                   << ((RHO_GPIO & 7)))                              \
                | (PWRUP_OUT_DFL_RHO_FOR_RHO << ((RHO_GPIO & 7)));                             \
      /* Shadow register state */                                                              \
      gpioCfgPowerUp[RHO_GPIO >> 2] = gpioCfgPowerUp[RHO_GPIO >> 2]                            \
                                      & ~(0x000F                   << ((RHO_GPIO & 3) * 4))    \
                                      | (PWRUP_CFG_DFL_RHO_FOR_RHO << ((RHO_GPIO & 3) * 4));   \
      gpioOutPowerUp[RHO_GPIO >> 3] = gpioOutPowerUp[RHO_GPIO >> 3]                            \
                                      & ~(0x0001                   << ((RHO_GPIO & 7)))        \
                                      | (PWRUP_OUT_DFL_RHO_FOR_RHO << ((RHO_GPIO & 7)));       \
      gpioCfgPowerDown[RHO_GPIO >> 2] = gpioCfgPowerDown[RHO_GPIO >> 2]                        \
                                        & ~(0x000F                   << ((RHO_GPIO & 3) * 4))  \
                                        | (PWRDN_CFG_DFL_RHO_FOR_RHO << ((RHO_GPIO & 3) * 4)); \
      gpioOutPowerDown[RHO_GPIO >> 3] = gpioOutPowerDown[RHO_GPIO >> 3]                        \
                                        & ~(0x0001                   << ((RHO_GPIO & 7)))      \
                                        | (PWRDN_OUT_DFL_RHO_FOR_RHO << ((RHO_GPIO & 7)));     \
      RHO_INTCFG  = (0 << _EVENT_GPIO_CFGD_FILT_SHIFT)         /* 0 = no filter  */            \
                    | (3 << _EVENT_GPIO_CFGD_MOD_SHIFT);       /* 3 = both edges */            \
    } else {         /* default */                                                             \
      /* Actual register state */                                                              \
      /*halGpioSetConfig(RHO_CFG, PWRUP_CFG_DFL_RHO_FOR_DFL);*/                                \
      RHO_CFG = RHO_CFG                                                                        \
                & ~(0x000F                   << ((RHO_GPIO & 3) * 4))                          \
                | (PWRUP_CFG_DFL_RHO_FOR_DFL << ((RHO_GPIO & 3) * 4));                         \
      RHO_OUT = RHO_OUT                                                                        \
                & ~(0x0001                   << ((RHO_GPIO & 7)))                              \
                | (PWRUP_OUT_DFL_RHO_FOR_DFL << ((RHO_GPIO & 7)));                             \
      /* Shadow register state */                                                              \
      gpioCfgPowerUp[RHO_GPIO >> 2] = gpioCfgPowerUp[RHO_GPIO >> 2]                            \
                                      & ~(0x000F                   << ((RHO_GPIO & 3) * 4))    \
                                      | (PWRUP_CFG_DFL_RHO_FOR_DFL << ((RHO_GPIO & 3) * 4));   \
      gpioOutPowerUp[RHO_GPIO >> 3] = gpioOutPowerUp[RHO_GPIO >> 3]                            \
                                      & ~(0x0001                   << ((RHO_GPIO & 7)))        \
                                      | (PWRUP_OUT_DFL_RHO_FOR_DFL << ((RHO_GPIO & 7)));       \
      gpioCfgPowerDown[RHO_GPIO >> 2] = gpioCfgPowerDown[RHO_GPIO >> 2]                        \
                                        & ~(0x000F                   << ((RHO_GPIO & 3) * 4))  \
                                        | (PWRDN_CFG_DFL_RHO_FOR_DFL << ((RHO_GPIO & 3) * 4)); \
      gpioOutPowerDown[RHO_GPIO >> 3] = gpioOutPowerDown[RHO_GPIO >> 3]                        \
                                        & ~(0x0001                   << ((RHO_GPIO & 7)))      \
                                        | (PWRDN_OUT_DFL_RHO_FOR_DFL << ((RHO_GPIO & 7)));     \
      RHO_INTCFG  = 0;         /* disabled */                                                  \
    }                                                                                          \
    RHO_SEL();         /* Point IRQ at the desired pin */                                      \
    RESTORE_INTERRUPTS();                                                                      \
} while (0)

#endif//RHO_GPIO
//@} //END OF RADIO HOLDOFF CONFIGURATION DEFINITIONS

/** @name Temperature sensor ADC channel
 *
 * Define the analog input channel connected to the LM-20 temperature sensor.
 * The scale factor compensates for different platform input ranges.
 * PB5/ADC0 must be an analog input.
 * PC7 must be an output and set to a high level to power the sensor.
 *
 *@{
 */

/**
 * @brief The analog input channel to use for the temperature sensor.
 */
#define TEMP_SENSOR_ADC_CHANNEL ADC_SOURCE_ADC0_VREF2

/**
 * @brief The scale factor to compensate for different input ranges.
 */
#define TEMP_SENSOR_SCALE_FACTOR 1

/** @} END OF TEMPERATURE SENSOR ADC CHANNEL DEFINITIONS */

/** @name Packet Trace
 *
 * When ::PACKET_TRACE is defined, ::GPIO->P[0].CFGH will automatically be setup by
 * halInit() to enable Packet Trace support on PA4 and PA5,
 * in addition to the configuration specified below.
 *
 * @note This define will override any settings for PA4 and PA5.
 */
//@{

/**
 * @brief This define does not equate to anything.  It is used as a
 * trigger to enable Packet Trace support.
 */
#define PACKET_TRACE  // We do have PACKET_TRACE support
//@} //END OF PACKET TRACE DEFINITIONS

/** @name ENABLE_OSC32K
 *
 * When ENABLE_OSC32K is defined, halInit() will configure system
 * timekeeping to utilize the external 32.768 kHz crystal oscillator
 * rather than the internal 1 kHz RC oscillator.
 *
 * @note ENABLE_OSC32K is mutually exclusive with
 * ENABLE_ALT_FUNCTION_NTX_ACTIVE since they define conflicting
 * usage of GPIO PC6.
 *
 * On initial powerup the 32.768 kHz crystal oscillator will take a little
 * while to start stable oscillation. This only happens on initial powerup,
 * not on wake-from-sleep, since the crystal usually stays running in deep
 * sleep mode.
 *
 * When ENABLE_OSC32K is defined the crystal oscillator is started as part of
 * halInit(). After the crystal is started we delay for
 * OSC32K_STARTUP_DELAY_MS (time in milliseconds).  This delay allows the
 * crystal oscillator to stabilize before we start using it for system timing.
 *
 * If you set OSC32K_STARTUP_DELAY_MS to less than the crystal's startup time:
 *   - The system timer won't produce a reliable one millisecond tick before
 *     the crystal is stable.
 *   - You may see some number of ticks of unknown period occur before the
 *     crystal is stable.
 *   - halInit() will complete and application code will begin running, but
 *     any events based on the system timer will not be accurate until the
 *     crystal is stable.
 *   - An unstable system timer will only affect the APIs in system-timer.h.
 *
 * Typical 32.768 kHz crystals measured by Ember take about 400 milliseconds
 * to stabilize. Be sure to characterize your particular crystal's stabilization
 * time since crystal behavior can vary.
 */
//@{
#define OSC32K_STARTUP_DELAY_MS (0)

#if OSC32K_STARTUP_DELAY_MS > MAX_INT16U_VALUE
#error "OSC32K_STARTUP_DELAY_MS must fit in 16 bits."
#endif

/**
 * @brief This define does not equate to anything.  It is used as a
 * trigger to enable 32.768 kHz XTAL oscillator on the RCM plugged
 * into the Breakout board (dev0680).
 * Default is to disable 32.768 kHz XTAL and use 1 kHz RC oscillator instead.
 */
//#define ENABLE_OSC32K  // Enable 32.768 kHz osc instead of 1 kHz RC osc
//@} //END OF ENABLE OSC32K DEFINITIONS

/** @name ENABLE_ALT_FUNCTION_REG_EN
 *
 * When ENABLE_ALT_FUNCTION_REG_EN is defined, halInit() will enable the REG_EN
 * alternate functionality on PA7.  REG_EN is the special signal provided
 * by the EM35x's internal power controller which can be used to tell an
 * external power regulator when the EM35x is in deep sleep or not and as such
 * signal the external regulator to cut power.  This signal will override all
 * GPIO configuration and use of PA7.  When the alternate functionality is
 * not enabled, PA7 can be operated as a standard GPIO.
 */
//@{

/**
 * @brief This define does not equate to anything.  It is used as a
 * trigger to enable the REG_EN alternate function on PA7.
 * Default is to not enable REG_EN functionality on PA7.
 */
//#define ENABLE_ALT_FUNCTION_REG_EN
//@} //END OF ENABLE_ALT_FUNCTION_REG_EN DEFINITIONS

/** @name ENABLE_ALT_FUNCTION_TX_ACTIVE
 *
 * When ENABLE_ALT_FUNCTION_TX_ACTIVE is defined, halInit() and halPowerUp()
 * will enable the TX_ACTIVE alternate functionality of PC5.  halPowerDown()
 * will configure PC5 to be a low output.  TX_ACTIVE can be used for
 * external PA power management and RF switching logic.  In transmit mode
 * the Tx baseband drives TX_ACTIVE high.  In receive mode the TX_ACTIVE
 * signal is low.  This define will override any settings for PC5.
 */
//@{

/**
 * @brief This define does not equate to anything.  It is used as a
 * trigger to enable the TX_ACTIVE alternate function on PC5.
 * Default enable TX_ACTIVE functionality on PC5 when using
 * the EM35x as an NCP for EZSP-UART.
 */
#define ENABLE_ALT_FUNCTION_TX_ACTIVE
//@} //END OF ENABLE_ALT_FUNCTION_TX_ACTIVE DEFINITIONS

/** @name ENABLE_ALT_FUNCTION_NTX_ACTIVE
 *
 * When ENABLE_ALT_FUNCTION_NTX_ACTIVE is defined, halInit() and halPowerUp()
 * will enable the nTX_ACTIVE alternate functionality of PC6.  halPowerDown()
 * will configure PC6 to be a low output.  nTX_ACTIVE can be used for
 * external PA power management and RF switching logic.  In transmit mode
 * the Tx baseband drives nTX_ACTIVE low.  In receive mode the nTX_ACTIVE
 * signal is high.  This define will override any settings for PC6.
 *
 * @note ENABLE_ALT_FUNCTION_NTX_ACTIVE is mutually exclusive with
 * ENABLE_OSC32K since they define conflicting usage of GPIO PC6.
 */
//@{

/**
 * @brief This define does not equate to anything.  It is used as a
 * trigger to enable the nTX_ACTIVE alternate function on PC6.
 * Default enable nTX_ACTIVE functionality on PC6 when using
 * the EM35x as an NCP for EZSP-UART.
 */
#define ENABLE_ALT_FUNCTION_NTX_ACTIVE
//@} //END OF ENABLE_ALT_FUNCTION_NTX_ACTIVE DEFINITIONS

/** @name GPIO Configuration Definitions
 *
 * The following are used to specify the GPIO configuration to establish
 * when Powered (POWERUP_), and when Deep Sleeping (POWERDOWN_).  The reason
 * for separate Deep Sleep settings is to allow for a slightly different
 * configuration that minimizes power consumption during Deep Sleep.  For
 * example, inputs that might float could be pulled up or down, and output
 * states chosen with care, e.g. to turn off LEDs or other devices that might
 * consume power or be unnecessary when Deep Sleeping.
 */
//@{

/** @name Packet Trace Configuration Defines
 *
 * Provide the proper set of pin configuration for when the Packet
 * Trace is enabled (look above for the define which enables it).  When Packet
 * Trace is not enabled, leave the two PTI pins in their default configuration.
 * If Packet Trace is not being used, feel free to set the pin configurations
 * as desired.  The config shown here is simply the Power On Reset defaults.
 *@{
 */

/**
 * @brief Give the packet trace configuration a friendly name.
 */
#ifdef  PACKET_TRACE
  #define PWRUP_CFG_PTI_EN    GPIO_P_CFGz_Pxy_OUT_ALT
  #define PWRUP_OUT_PTI_EN    0
  #define PWRDN_CFG_PTI_EN    GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_PTI_EN    GPIO_P_OUT_Pxy_PULLDOWN
  #define PWRUP_CFG_PTI_DATA  GPIO_P_CFGz_Pxy_OUT_ALT
  #define PWRUP_OUT_PTI_DATA  1
  #define PWRDN_CFG_PTI_DATA  GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_PTI_DATA  GPIO_P_OUT_Pxy_PULLUP
#else//!PACKET_TRACE
  #define PWRUP_CFG_PTI_EN    GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRUP_OUT_PTI_EN    GPIO_P_OUT_Pxy_PULLDOWN
  #define PWRDN_CFG_PTI_EN    GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_PTI_EN    GPIO_P_OUT_Pxy_PULLDOWN
  #define PWRUP_CFG_PTI_DATA  GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRUP_OUT_PTI_DATA  GPIO_P_OUT_Pxy_PULLUP
  #define PWRDN_CFG_PTI_DATA  GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_PTI_DATA  GPIO_P_OUT_Pxy_PULLUP
#endif//PACKET_TRACE
//@} END OF Packet Trace Configuration Defines

/** @name 32kHz Oscillator and nTX_ACTIVE Configuration Defines
 *
 * Since the 32kHz Oscillator and nTX_ACTIVE both share PC6, their
 * configuration defines are linked and instantiated together.  Look above
 * for the defines that enable the 32kHz Oscillator and nTX_ACTIVE.
 *
 * @note ENABLE_OSC32K is mutually exclusive with
 * ENABLE_ALT_FUNCTION_NTX_ACTIVE since they define conflicting
 * usage of GPIO PC6.
 *
 * When using the 32kHz, configure PC6 and PC7 for analog for the XTAL.
 *
 * When using nTX_ACTIVE, configure PC6 for alternate output while awake
 * and a low output when deepsleeping.  Also, configure PC7 for TEMP_EN.
 *
 * When not using the 32kHz or nTX_ACTIVE, configure PC6 and PC7 for
 * Button1 and TEMP_EN.
 *@{
 */

/**
 * @brief Give GPIO PC6 configuration a friendly name.
 */
#if defined(ENABLE_OSC32K) && defined(ENABLE_ALT_FUNCTION_NTX_ACTIVE)
//Oops!  Only one of these can be used at a time!
  #error ENABLE_OSC32K and ENABLE_ALT_FUNCTION_NTX_ACTIVE are mutually \
  exclusive.  They define conflicting usage for GPIO PC6.

#elif defined(ENABLE_OSC32K) && !defined(ENABLE_ALT_FUNCTION_NTX_ACTIVE)
//Use OCS32K configuration
  #define PWRUP_CFG_BUTTON1  GPIO_P_CFGz_Pxy_ANALOG
  #define PWRUP_OUT_BUTTON1  0
  #define PWRDN_CFG_BUTTON1  GPIO_P_CFGz_Pxy_ANALOG
  #define PWRDN_OUT_BUTTON1  0

#elif !defined(ENABLE_OSC32K) && defined(ENABLE_ALT_FUNCTION_NTX_ACTIVE)
//Use nTX_ACTIVE configuration
  #define PWRUP_CFG_BUTTON1  GPIO_P_CFGz_Pxy_OUT_ALT
  #define PWRUP_OUT_BUTTON1  0
  #define PWRDN_CFG_BUTTON1  GPIO_P_CFGz_Pxy_OUT
  #define PWRDN_OUT_BUTTON1  0

#else
//Use Button1 configuration
  #define PWRUP_CFG_BUTTON1  GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRUP_OUT_BUTTON1  GPIO_P_OUT_Pxy_PULLUP /* Button needs a pullup */
  #define PWRDN_CFG_BUTTON1  GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_BUTTON1  GPIO_P_OUT_Pxy_PULLUP /* Button needs a pullup */

#endif

/**
 * @brief Give GPIO PC7 configuration a friendly name.
 */
#ifdef  ENABLE_OSC32K
  #define CFG_OSC32K         GPIO_P_CFGz_Pxy_ANALOG
#else//!ENABLE_OSC32K
  #define CFG_OSC32K         GPIO_P_CFGz_Pxy_IN_PUD
#endif//ENABLE_OSC32K
//@} END OF 32kHz Oscillator and nTX_ACTIVE Configuration Defines

/** @name TX_ACTIVE Configuration Defines
 *
 * Provide the proper set of pin (PC5) configurations for when TX_ACTIVE is
 * enabled (look above for the define which enables it).  When TX_ACTIVE is
 * not enabled, configure the pin for LED2.
 *@{
 */

/**
 * @brief Give the TX_ACTIVE configuration a friendly name.
 */
#ifdef  ENABLE_ALT_FUNCTION_TX_ACTIVE
  #define PWRUP_CFG_LED2  GPIO_P_CFGz_Pxy_OUT_ALT
  #define PWRUP_OUT_LED2  0
  #define PWRDN_CFG_LED2  GPIO_P_CFGz_Pxy_OUT
  #define PWRDN_OUT_LED2  0
#else //!ENABLE_ALT_FUNCTION_TX_ACTIVE
  #define PWRUP_CFG_LED2  GPIO_P_CFGz_Pxy_OUT
  #define PWRUP_OUT_LED2  1  /* LED default off */
  #define PWRDN_CFG_LED2  GPIO_P_CFGz_Pxy_OUT
  #define PWRDN_OUT_LED2  1  /* LED default off */
#endif//ENABLE_ALT_FUNCTION_TX_ACTIVE
//@} END OF TX_ACTIVE Configuration Defines

/** @name USB Configuration Defines
 *
 * Provide the proper set of pin configuration for when USB is not enumerated.
 * Not enumerated primarily refers to the driver not being configured or deep
 * sleep.  The configuration used here is only for keeping the USB off the bus.
 * The GPIO configuration used when active is controlled by the USB driver
 * since the driver needs to control the enumeration process (which affects
 * GPIO state.)
 *
 * @note: Using USB requires Serial port 3 to be defined and is only possible
 * on EM3582/EM3586/EM3588/EM359 chips.
 *@{
 */

/**
 * @brief Give the USB configuration a friendly name.
 */
#if (!defined(EM_SERIAL3_DISABLED)) && (defined(CORTEXM3_EM35X_USB))
  #define PWRUP_CFG_USBDM      GPIO_P_CFGz_Pxy_IN
  #define PWRUP_OUT_USBDM      0
  #define PWRUP_CFG_USBDP      GPIO_P_CFGz_Pxy_IN
  #define PWRUP_OUT_USBDP      0
  #define PWRUP_CFG_ENUMCTRL   GPIO_P_CFGz_Pxy_OUT
  #define PWRUP_OUT_ENUMCTRL   0
  #define PWRUP_CFG_VBUSMON    GPIO_P_CFGz_Pxy_IN
  #define PWRUP_OUT_VBUSMON    0
  #define PWRDN_CFG_USBDM      GPIO_P_CFGz_Pxy_IN
  #define PWRDN_OUT_USBDM      0
  #define PWRDN_CFG_USBDP      GPIO_P_CFGz_Pxy_IN
  #define PWRDN_OUT_USBDP      0
  #define PWRDN_CFG_ENUMCTRL   GPIO_P_CFGz_Pxy_OUT
  #define PWRDN_OUT_ENUMCTRL   0
  #define PWRDN_CFG_VBUSMON    GPIO_P_CFGz_Pxy_IN
  #define PWRDN_OUT_VBUSMON    0
#else
  #define PWRUP_CFG_USBDM      GPIO_P_CFGz_Pxy_OUT_ALT
  #define PWRUP_OUT_USBDM      0
  #define PWRUP_CFG_USBDP      GPIO_P_CFGz_Pxy_IN
  #define PWRUP_OUT_USBDP      0
  #define PWRUP_CFG_ENUMCTRL   GPIO_P_CFGz_Pxy_OUT_ALT
  #define PWRUP_OUT_ENUMCTRL   0
  #define PWRUP_CFG_VBUSMON    GPIO_P_CFGz_Pxy_OUT
  #define PWRUP_OUT_VBUSMON    1
  #define PWRDN_CFG_USBDM      GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_USBDM      GPIO_P_OUT_Pxy_PULLUP
  #define PWRDN_CFG_USBDP      GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_USBDP      GPIO_P_OUT_Pxy_PULLUP
  #define PWRDN_CFG_ENUMCTRL   GPIO_P_CFGz_Pxy_IN_PUD
  #define PWRDN_OUT_ENUMCTRL   GPIO_P_OUT_Pxy_PULLUP
  #define PWRDN_CFG_VBUSMON    GPIO_P_CFGz_Pxy_OUT
  #define PWRDN_OUT_VBUSMON    1
#endif//
//@} END OF USB Configuration Defines

/** @name GPIO Configuration Macros
 *
 * These macros define the GPIO configuration and initial state of the output
 * registers for all the GPIO in the powerup and powerdown modes.
 *@{
 */

//Each pin has 4 cfg bits.  There are 4.5 ports with 2 cfg registers per
//port since the cfg register only holds 4 pins (16bits).  Therefore,
//the cfg arrays need to be 9 entries of 16bits.
extern uint16_t gpioCfgPowerUp[9];
extern uint16_t gpioCfgPowerDown[9];
//Each pin has 1 out bit.  There are 5 ports with 1 out register per
//port (8bits).  Therefore, the out arrays need to be 5 entries of 8bits.
extern uint8_t gpioOutPowerUp[5];
extern uint8_t gpioOutPowerDown[5];
//A single mask variable covers all GPIO.
extern GpioMaskType gpioRadioPowerBoardMask;

/**
 * @brief Define the pins crucial to host-NCP communications over UART.  This
 * mask is used to prevent the host from changing pin configurations
 * necessary to maintain host-NCP communications (otherwise changes would
 * break the link!).
 */
#define EZSP_PIN_BLACKOUT_MASK  ((((GpioMaskType)1) << PORTB_PIN(1))   /*SC1TXD*/  \
                                 | (((GpioMaskType)1) << PORTB_PIN(2)) /*SC1RXD*/  \
                                 | (((GpioMaskType)1) << PORTB_PIN(3)) /*SC1nCTS*/ \
                                 | (((GpioMaskType)1) << PORTB_PIN(4))) /*SC1nRTS*/

// Set up FEM control signals based on ENABLE_ALT_FUNCTION_xxx defines above
// in preparation for GPIO Radio Power Board Mask below:
// -PA control line (Tx_Active)
#ifdef ENABLE_ALT_FUNCTION_TX_ACTIVE
  #define FEM_CTX_BIT (BIT32(PORTC_PIN(5)))
#else
  #define FEM_CTX_BIT (0)
#endif
// -LNA control line (!Tx_Active)
#ifdef ENABLE_ALT_FUNCTION_NTX_ACTIVE
  #define FEM_CRX_BIT (BIT32(PORTC_PIN(6)))
#else
  #define FEM_CRX_BIT (0)
#endif

/**
 * @brief Define the mask for GPIO relevant to the radio in the context
 * of power state.  Each bit in the mask indicates the corresponding GPIO
 * which should be affected when invoking halStackRadioPowerUpBoard() or
 * halStackRadioPowerDownBoard().
 */
#define DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE()                           \
  GpioMaskType gpioRadioPowerBoardMask = { (BIT32(PORTB_PIN(0)) /* FEM_CSD */   \
                                            | BIT32(PORTB_PIN(5)) /* FEM_CPS */ \
                                            | FEM_CTX_BIT                       \
                                            | FEM_CRX_BIT                       \
                                            ) }

#define GPIOCFG_UNUSED      GPIO_P_CFGz_Pxy_OUT
#define GPIOOUT_UNUSED      0

/**
 * @brief Initialize GPIO powerup configuration variables.
 */
#define DEFINE_POWERUP_GPIO_CFG_VARIABLES()                                                       \
  uint16_t gpioCfgPowerUp[9] = {                                                                  \
    ((PWRUP_CFG_USBDM    << _GPIO_P_CFGL_Px0_SHIFT)                                               \
     | (PWRUP_CFG_USBDP    << _GPIO_P_CFGL_Px1_SHIFT)                                             \
     | (PWRUP_CFG_ENUMCTRL << _GPIO_P_CFGL_Px2_SHIFT)                                             \
     | (PWRUP_CFG_VBUSMON  << _GPIO_P_CFGL_Px3_SHIFT)),                                           \
    ((PWRUP_CFG_PTI_EN   << _GPIO_P_CFGH_Px4_SHIFT)                                               \
     | (PWRUP_CFG_PTI_DATA << _GPIO_P_CFGH_Px5_SHIFT)                                             \
     | (PWRUP_CFG_DFL_RHO  << _GPIO_P_CFGH_Px6_SHIFT)                                             \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGH_Px7_SHIFT)),                                   \
    ((GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px0_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_OUT_ALT    << _GPIO_P_CFGL_Px1_SHIFT)                       /* SC1TXD  */ \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGL_Px2_SHIFT)                       /* SC1RXD  */ \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGL_Px3_SHIFT)),                     /* SC1nCTS */ \
    ((GPIO_P_CFGz_Pxy_OUT_ALT    << _GPIO_P_CFGH_Px4_SHIFT)                         /* SC1nRTS */ \
     | (GPIO_P_CFGz_Pxy_ANALOG     << _GPIO_P_CFGH_Px5_SHIFT)                                     \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGH_Px6_SHIFT)                                     \
     | (GPIO_P_CFGz_Pxy_OUT_ALT    << _GPIO_P_CFGH_Px7_SHIFT)),                                   \
    ((GPIO_P_CFGz_Pxy_OUT_ALT    << _GPIO_P_CFGL_Px0_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px1_SHIFT)                                     \
     | (GPIO_P_CFGz_Pxy_OUT_ALT    << _GPIO_P_CFGL_Px2_SHIFT)                                     \
     | (GPIO_P_CFGz_Pxy_IN         << _GPIO_P_CFGL_Px3_SHIFT)),                                   \
    ((GPIO_P_CFGz_Pxy_IN         << _GPIO_P_CFGH_Px4_SHIFT)                                       \
     | (PWRUP_CFG_LED2     << _GPIO_P_CFGH_Px5_SHIFT)                                             \
     | (PWRUP_CFG_BUTTON1  << _GPIO_P_CFGH_Px6_SHIFT)                                             \
     | (CFG_OSC32K         << _GPIO_P_CFGH_Px7_SHIFT)),                                           \
    ((GPIOCFG_UNUSED     << _GPIO_P_CFGL_Px0_SHIFT)                                               \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px1_SHIFT)                       /* SC3TXD  */ \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px2_SHIFT)                       /* SC3RXD  */ \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px3_SHIFT)),                     /* SC3nCTS */ \
    ((GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGH_Px4_SHIFT)                         /* SC3nRTS */ \
     | (GPIOCFG_UNUSED     << _GPIO_P_CFGH_Px5_SHIFT)                                             \
     | (GPIOCFG_UNUSED     << _GPIO_P_CFGH_Px6_SHIFT)                                             \
     | (GPIOCFG_UNUSED     << _GPIO_P_CFGH_Px7_SHIFT)),                                           \
    ((GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px0_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px1_SHIFT)                                     \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px2_SHIFT)                                     \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px3_SHIFT))                                    \
  }

/**
 * @brief Initialize GPIO powerup output variables.
 */
#define DEFINE_POWERUP_GPIO_OUTPUT_DATA_VARIABLES()                                      \
  uint8_t gpioOutPowerUp[5] = {                                                          \
    ((PWRUP_OUT_USBDM    << _GPIO_P_OUT_Px0_SHIFT)                                       \
     | (PWRUP_OUT_USBDP    << _GPIO_P_OUT_Px1_SHIFT)                                     \
     | (PWRUP_OUT_ENUMCTRL << _GPIO_P_OUT_Px2_SHIFT)                                     \
     | (PWRUP_OUT_VBUSMON  << _GPIO_P_OUT_Px3_SHIFT)                                     \
     | (PWRUP_OUT_PTI_EN   << _GPIO_P_OUT_Px4_SHIFT)                                     \
     | (PWRUP_OUT_PTI_DATA << _GPIO_P_OUT_Px5_SHIFT)                                     \
     | (PWRUP_OUT_DFL_RHO  << _GPIO_P_OUT_Px6_SHIFT)                                     \
     | (1                  << _GPIO_P_OUT_Px7_SHIFT)),                                   \
    ((1                  << _GPIO_P_OUT_Px0_SHIFT)                                       \
     | (1                  << _GPIO_P_OUT_Px1_SHIFT)                       /* SC1TXD  */ \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)                       /* SC1RXD  */ \
     | (1                  << _GPIO_P_OUT_Px3_SHIFT)                       /* SC1nCTS */ \
     | (0                  << _GPIO_P_OUT_Px4_SHIFT)                       /* SC1nRTS */ \
     | (0                  << _GPIO_P_OUT_Px5_SHIFT)                                     \
     |                      /* PB6 has button needing a pullup */                        \
     (GPIO_P_OUT_Pxy_PULLUP     << _GPIO_P_OUT_Px6_SHIFT)                                \
     | (GPIO_P_OUT_Pxy_PULLDOWN   << _GPIO_P_OUT_Px7_SHIFT)),                            \
    ((1                  << _GPIO_P_OUT_Px0_SHIFT)                                       \
     | (0                  << _GPIO_P_OUT_Px1_SHIFT)                                     \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)                                     \
     | (0                  << _GPIO_P_OUT_Px3_SHIFT)                                     \
     | (0                  << _GPIO_P_OUT_Px4_SHIFT)                                     \
     | (PWRUP_OUT_LED2     << _GPIO_P_OUT_Px5_SHIFT)                                     \
     | (PWRUP_OUT_BUTTON1  << _GPIO_P_OUT_Px6_SHIFT)                                     \
     | (1                  << _GPIO_P_OUT_Px7_SHIFT)),                                   \
    ((GPIOOUT_UNUSED     << _GPIO_P_OUT_Px0_SHIFT)                                       \
     | (1                  << _GPIO_P_OUT_Px1_SHIFT)                       /* SC3TXD  */ \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)                       /* SC3RXD  */ \
     | (1                  << _GPIO_P_OUT_Px3_SHIFT)                       /* SC3nCTS */ \
     | (1                  << _GPIO_P_OUT_Px4_SHIFT)                       /* SC3nRTS */ \
     | (GPIOOUT_UNUSED     << _GPIO_P_OUT_Px5_SHIFT)                                     \
     | (GPIOOUT_UNUSED     << _GPIO_P_OUT_Px6_SHIFT)                                     \
     | (GPIOOUT_UNUSED     << _GPIO_P_OUT_Px7_SHIFT)),                                   \
    ((1                  << _GPIO_P_OUT_Px0_SHIFT)                                       \
     | (1                  << _GPIO_P_OUT_Px1_SHIFT)                                     \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)                                     \
     | (1                  << _GPIO_P_OUT_Px3_SHIFT))                                    \
  }

/**
 * @brief Initialize powerdown GPIO configuration variables.
 */
#define DEFINE_POWERDOWN_GPIO_CFG_VARIABLES()                                                       \
  uint16_t gpioCfgPowerDown[9] = {                                                                  \
    ((PWRDN_CFG_USBDM    << _GPIO_P_CFGL_Px0_SHIFT)                                                 \
     | (PWRDN_CFG_USBDP    << _GPIO_P_CFGL_Px1_SHIFT)                                               \
     | (PWRDN_CFG_ENUMCTRL << _GPIO_P_CFGL_Px2_SHIFT)                                               \
     | (PWRDN_CFG_VBUSMON  << _GPIO_P_CFGL_Px3_SHIFT)),                                             \
    ((PWRDN_CFG_PTI_EN   << _GPIO_P_CFGH_Px4_SHIFT)                                                 \
     | (PWRDN_CFG_PTI_DATA << _GPIO_P_CFGH_Px5_SHIFT)                                               \
     | (PWRDN_CFG_DFL_RHO  << _GPIO_P_CFGH_Px6_SHIFT)                                               \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGH_Px7_SHIFT)),                                     \
    ((GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px0_SHIFT)                                         \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px1_SHIFT)                         /* SC1TXD  */ \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGL_Px2_SHIFT)                         /* SC1RXD  */ \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGL_Px3_SHIFT)),                       /* SC1nCTS */ \
    ((GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGH_Px4_SHIFT)                           /* SC1nRTS */ \
     |                         /* disable analog for sleep */                                       \
     (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGH_Px5_SHIFT)                                         \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGH_Px6_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGH_Px7_SHIFT)),                                     \
    ((GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGL_Px0_SHIFT)                                         \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px1_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px2_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGL_Px3_SHIFT)),                                     \
    ((GPIO_P_CFGz_Pxy_IN_PUD     << _GPIO_P_CFGH_Px4_SHIFT)                                         \
     | (PWRDN_CFG_LED2     << _GPIO_P_CFGH_Px5_SHIFT)                                               \
     | (PWRDN_CFG_BUTTON1  << _GPIO_P_CFGH_Px6_SHIFT)                                               \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGH_Px7_SHIFT)),                                     \
    ((GPIOCFG_UNUSED     << _GPIO_P_CFGL_Px0_SHIFT)                                                 \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px1_SHIFT)                         /* SC3TXD  */ \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px2_SHIFT)                         /* SC3RXD  */ \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px3_SHIFT)),                       /* SC3nCTS */ \
    ((GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGH_Px4_SHIFT)                           /* SC3nRTS */ \
     | (GPIOCFG_UNUSED     << _GPIO_P_CFGH_Px5_SHIFT)                                               \
     | (GPIOCFG_UNUSED     << _GPIO_P_CFGH_Px6_SHIFT)                                               \
     | (GPIOCFG_UNUSED     << _GPIO_P_CFGH_Px7_SHIFT)),                                             \
    ((GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px0_SHIFT)                                         \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px1_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px2_SHIFT)                                       \
     | (GPIO_P_CFGz_Pxy_OUT        << _GPIO_P_CFGL_Px3_SHIFT))                                      \
  }

/**
 * @brief Initialize powerdown GPIO output variables.
 */
#define DEFINE_POWERDOWN_GPIO_OUTPUT_DATA_VARIABLES()                                             \
  uint8_t gpioOutPowerDown[5] = {                                                                 \
    ((PWRDN_OUT_USBDM    << _GPIO_P_OUT_Px0_SHIFT)                                                \
     | (PWRDN_OUT_USBDP    << _GPIO_P_OUT_Px1_SHIFT)                                              \
     | (PWRDN_OUT_ENUMCTRL << _GPIO_P_OUT_Px2_SHIFT)                                              \
     | (PWRDN_OUT_VBUSMON  << _GPIO_P_OUT_Px3_SHIFT)                                              \
     | (PWRDN_OUT_PTI_EN   << _GPIO_P_OUT_Px4_SHIFT)                                              \
     | (PWRDN_OUT_PTI_DATA << _GPIO_P_OUT_Px5_SHIFT)                                              \
     | (PWRDN_OUT_DFL_RHO  << _GPIO_P_OUT_Px6_SHIFT)                                              \
     | (1                  << _GPIO_P_OUT_Px7_SHIFT)),                                            \
    ((0                  << _GPIO_P_OUT_Px0_SHIFT)                                                \
     | (GPIO_P_OUT_Pxy_PULLUP     << _GPIO_P_OUT_Px1_SHIFT)                         /* SC1TXD  */ \
     | (GPIO_P_OUT_Pxy_PULLUP     << _GPIO_P_OUT_Px2_SHIFT)                         /* SC1RXD  */ \
     | (GPIO_P_OUT_Pxy_PULLDOWN   << _GPIO_P_OUT_Px3_SHIFT)                         /* SC1nCTS */ \
     | (GPIO_P_OUT_Pxy_PULLUP     << _GPIO_P_OUT_Px4_SHIFT)                         /* SC1nRTS */ \
     |                        /* tempsense needs pulldown */                                      \
     (GPIO_P_OUT_Pxy_PULLDOWN   << _GPIO_P_OUT_Px5_SHIFT)                                         \
     |                        /* PB6 has button needing a pullup */                               \
     (GPIO_P_OUT_Pxy_PULLUP     << _GPIO_P_OUT_Px6_SHIFT)                                         \
     | (GPIO_P_OUT_Pxy_PULLDOWN   << _GPIO_P_OUT_Px7_SHIFT)),                                     \
    ((GPIO_P_OUT_Pxy_PULLUP     << _GPIO_P_OUT_Px0_SHIFT)                                         \
     | (0                  << _GPIO_P_OUT_Px1_SHIFT)                                              \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)                                              \
     | (GPIO_P_OUT_Pxy_PULLDOWN   << _GPIO_P_OUT_Px3_SHIFT)                                       \
     | (GPIO_P_OUT_Pxy_PULLDOWN   << _GPIO_P_OUT_Px4_SHIFT)                                       \
     | (PWRDN_OUT_LED2     << _GPIO_P_OUT_Px5_SHIFT)                                              \
     | (PWRDN_OUT_BUTTON1  << _GPIO_P_OUT_Px6_SHIFT)                                              \
     | (1                  << _GPIO_P_OUT_Px7_SHIFT)),                                            \
    ((GPIOOUT_UNUSED     << _GPIO_P_OUT_Px0_SHIFT)                                                \
     | (1                  << _GPIO_P_OUT_Px1_SHIFT)                         /* SC3TXD  */        \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)                         /* SC3RXD  */        \
     | (1                  << _GPIO_P_OUT_Px3_SHIFT)                         /* SC3nCTS */        \
     | (1                  << _GPIO_P_OUT_Px4_SHIFT)                         /* SC3nRTS */        \
     | (GPIOOUT_UNUSED     << _GPIO_P_OUT_Px5_SHIFT)                                              \
     | (GPIOOUT_UNUSED     << _GPIO_P_OUT_Px6_SHIFT)                                              \
     | (GPIOOUT_UNUSED     << _GPIO_P_OUT_Px7_SHIFT)),                                            \
    ((1                  << _GPIO_P_OUT_Px0_SHIFT)                                                \
     | (1                  << _GPIO_P_OUT_Px1_SHIFT)                                              \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)                                              \
     | (1                  << _GPIO_P_OUT_Px3_SHIFT))                                             \
  }

/**
 * @brief Set powerup GPIO configuration registers.
 */
#define SET_POWERUP_GPIO_CFG_REGISTERS() \
  GPIO->P[0].CFGL = gpioCfgPowerUp[0];   \
  GPIO->P[0].CFGH = gpioCfgPowerUp[1];   \
  GPIO->P[1].CFGL = gpioCfgPowerUp[2];   \
  GPIO->P[1].CFGH = gpioCfgPowerUp[3];   \
  GPIO->P[2].CFGL = gpioCfgPowerUp[4];   \
  GPIO->P[2].CFGH = gpioCfgPowerUp[5];   \
  GPIO_PDCFGL = gpioCfgPowerUp[6];       \
  GPIO_PDCFGH = gpioCfgPowerUp[7];       \
  GPIO_PECFGL = gpioCfgPowerUp[8];

/**
 * @brief Set powerup GPIO output registers.
 */
#define SET_POWERUP_GPIO_OUTPUT_DATA_REGISTERS() \
  GPIO->P[0].OUT = gpioOutPowerUp[0];            \
  GPIO->P[1].OUT = gpioOutPowerUp[1];            \
  GPIO->P[2].OUT = gpioOutPowerUp[2];            \
  GPIO->P[3].OUT = gpioOutPowerUp[3];            \
  GPIO->P[4].OUT = gpioOutPowerUp[4];

/**
 * @brief Set powerdown GPIO configuration registers.
 */
#define SET_POWERDOWN_GPIO_CFG_REGISTERS() \
  GPIO->P[0].CFGL = gpioCfgPowerDown[0];   \
  GPIO->P[0].CFGH = gpioCfgPowerDown[1];   \
  GPIO->P[1].CFGL = gpioCfgPowerDown[2];   \
  GPIO->P[1].CFGH = gpioCfgPowerDown[3];   \
  GPIO->P[2].CFGL = gpioCfgPowerDown[4];   \
  GPIO->P[2].CFGH = gpioCfgPowerDown[5];   \
  GPIO_PDCFGL = gpioCfgPowerDown[6];       \
  GPIO_PDCFGH = gpioCfgPowerDown[7];       \
  GPIO_PECFGL = gpioCfgPowerDown[8];

/**
 * @brief Set powerdown GPIO output registers.
 */
#define SET_POWERDOWN_GPIO_OUTPUT_DATA_REGISTERS() \
  GPIO->P[0].OUT = gpioOutPowerDown[0];            \
  GPIO->P[1].OUT = gpioOutPowerDown[1];            \
  GPIO->P[2].OUT = gpioOutPowerDown[2];            \
  GPIO->P[3].OUT = gpioOutPowerDown[3];            \
  GPIO->P[4].OUT = gpioOutPowerDown[4];

/**
 * @brief Set resume GPIO configuration registers. Identical to SET_POWERUP
 */
#define SET_RESUME_GPIO_CFG_REGISTERS() \
  SET_POWERUP_GPIO_CFG_REGISTERS()

/**
 * @brief Set resume GPIO output registers. Identical to SET_POWERUP
 */
#define SET_RESUME_GPIO_OUTPUT_DATA_REGISTERS() \
  SET_POWERUP_GPIO_OUTPUT_DATA_REGISTERS()

/**
 * @brief Set suspend GPIO configuration registers. SET_POWERDOWN minus USB regs
 */
#define SET_SUSPEND_GPIO_CFG_REGISTERS() \
  /* GPIO->P[0].CFGL USB untouched! */   \
  GPIO->P[0].CFGH = gpioCfgPowerDown[1]; \
  GPIO->P[1].CFGL = gpioCfgPowerDown[2]; \
  GPIO->P[1].CFGH = gpioCfgPowerDown[3]; \
  GPIO->P[2].CFGL = gpioCfgPowerDown[4]; \
  GPIO->P[2].CFGH = gpioCfgPowerDown[5]; \
  GPIO_PDCFGL = gpioCfgPowerDown[6];     \
  GPIO_PDCFGH = gpioCfgPowerDown[7];     \
  GPIO_PECFGL = gpioCfgPowerDown[8];

/**
 * @brief Set suspend GPIO output registers. SET_POWERDOWN minus USB regs
 */
#define SET_SUSPEND_GPIO_OUTPUT_DATA_REGISTERS()             \
  GPIO->P[0].OUT = (GPIO->P[0].OUT & 0x0F) /*USB untouched*/ \
                   | (gpioOutPowerDown[0] & 0xF0);           \
  GPIO->P[1].OUT = gpioOutPowerDown[1];                      \
  GPIO->P[2].OUT = gpioOutPowerDown[2];                      \
  GPIO->P[3].OUT = gpioOutPowerDown[3];                      \
  GPIO->P[4].OUT = gpioOutPowerDown[4];

/**
 * @brief External regulator enable/disable macro.
 */
#ifdef ENABLE_ALT_FUNCTION_REG_EN
  #define CONFIGURE_EXTERNAL_REGULATOR_ENABLE()  GPIO->DBGCFG |= GPIO_DBGCFG_EXTREGEN;
#else
  #define CONFIGURE_EXTERNAL_REGULATOR_ENABLE()  GPIO->DBGCFG &= ~GPIO_DBGCFG_EXTREGEN;
#endif
//@} END OF GPIO Configuration Macros

/** @name GPIO Wake Source Definitions
 *
 * A convenient define that chooses if this external signal can
 * be used as source to wake from deep sleep.  Any change in the state of the
 * signal will wake up the CPU.
 */
//@{

/**
 * @brief true if this GPIO can wake the chip from deep sleep, false if not.
 */
#define WAKE_ON_PA0   false
#define WAKE_ON_PA1   false
#define WAKE_ON_PA2   false
#define WAKE_ON_PA3   false
#define WAKE_ON_PA4   false
#define WAKE_ON_PA5   false
#define WAKE_ON_PA6   false
#define WAKE_ON_PA7   false
#define WAKE_ON_PB0   false
#define WAKE_ON_PB1   false
#ifdef SLEEPY_EZSP_UART  // SC1RXD
  #define WAKE_ON_PB2   true
#else
  #define WAKE_ON_PB2   false
#endif
#define WAKE_ON_PB3   false
#define WAKE_ON_PB4   false
#define WAKE_ON_PB5   false
#define WAKE_ON_PB6   true   //BUTTON0
#define WAKE_ON_PB7   false
#define WAKE_ON_PC0   false
#define WAKE_ON_PC1   false
#define WAKE_ON_PC2   false
#define WAKE_ON_PC3   false
#define WAKE_ON_PC4   false
#define WAKE_ON_PC5   false
#define WAKE_ON_PC6   true   //BUTTON1
#define WAKE_ON_PC7   false
#define WAKE_ON_PD1   false
#define WAKE_ON_PD2   false
#define WAKE_ON_PD3   false
#define WAKE_ON_PD4   false
#define WAKE_ON_PE0   false
#define WAKE_ON_PE1   false
#define WAKE_ON_PE2   false
#define WAKE_ON_PE3   false
//@} //END OF GPIO Wake Source Definitions

//@} //END OF GPIO Configuration Definitions

/** @name Board Specific Functions
 *
 * The following macros exist to aid in the initialization, power up from sleep,
 * and power down to sleep operations.  These macros are responsible for
 * either initializing directly, or calling initialization functions for any
 * peripherals that are specific to this board implementation.  These
 * macros are called from halInit, halPowerDown, and halPowerUp respectively.
 */
//@{

/**
 * @brief Initialize the board.  This function is called from ::halInit().
 */
#define halInternalInitBoard()     \
  do {                             \
    halInternalPowerUpBoard();     \
    halInternalInitRadioHoldOff(); \
  } while (0)

/**
 * @brief Power down the board.  This function is called from
 * ::halPowerDown().
 */
#define halInternalPowerDownBoard()            \
  do {                                         \
    /* Board peripheral deactivation */        \
    /* halInternalSleepAdc(); */               \
    SET_POWERDOWN_GPIO_OUTPUT_DATA_REGISTERS() \
    SET_POWERDOWN_GPIO_CFG_REGISTERS()         \
  } while (0)

/**
 * @brief Power up the board.  This function is called from
 * ::halPowerUp().
 */
#define halInternalPowerUpBoard()                            \
  do {                                                       \
    SET_POWERUP_GPIO_OUTPUT_DATA_REGISTERS()                 \
    SET_POWERUP_GPIO_CFG_REGISTERS()                         \
    /*The radio GPIO should remain in the powerdown state */ \
    /*until the stack specifically powers them up. */        \
    halStackRadioPowerDownBoard();                           \
    CONFIGURE_EXTERNAL_REGULATOR_ENABLE()                    \
    /* Board peripheral reactivation */                      \
    halInternalInitAdc();                                    \
  } while (0)

/**
 * @brief Suspend the board.  This function is called from
 * ::halSuspend().
 */
#define halInternalSuspendBoard()            \
  do {                                       \
    /* Board peripheral deactivation */      \
    /* halInternalSleepAdc(); */             \
    SET_SUSPEND_GPIO_OUTPUT_DATA_REGISTERS() \
    SET_SUSPEND_GPIO_CFG_REGISTERS()         \
  } while (0)

/**
 * @brief Resume the board.  This function is called from
 * ::halResume().
 */
#define halInternalResumeBoard()                             \
  do {                                                       \
    SET_RESUME_GPIO_OUTPUT_DATA_REGISTERS()                  \
    SET_RESUME_GPIO_CFG_REGISTERS()                          \
    /*The radio GPIO should remain in the powerdown state */ \
    /*until the stack specifically powers them up. */        \
    halStackRadioPowerDownBoard();                           \
    CONFIGURE_EXTERNAL_REGULATOR_ENABLE()                    \
    /* Board peripheral reactivation */                      \
    halInternalInitAdc();                                    \
  } while (0)
//@} //END OF BOARD SPECIFIC FUNCTIONS

#endif //__BOARD_H__

/** @} END Board Specific Functions */

/** @} END addtogroup */
