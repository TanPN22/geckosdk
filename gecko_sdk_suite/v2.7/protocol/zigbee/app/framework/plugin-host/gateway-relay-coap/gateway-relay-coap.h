/***************************************************************************//**
 * @file
 * @brief Definitions for the Gateway Relay COAP plugin.
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

#ifndef SILABS_GATEWAY_RELAY_COAP_H
#define SILABS_GATEWAY_RELAY_COAP_H

/** @brief Parses an incoming dotdot message.
 *
 * This API parses the incoming gateway relay COAP message and, if necessary,
 * sends the resulting ZCL command to the appropriate device.
 *
 * @param length The length of the payload.
 *
 * @param *string A pointer to the payload (after the "zcl" option has been
 * stripped out).
 *
 * @param portCounter The number of the port on which the message was received.
 * This will be used to determine to which device a ZCL command should be sent,
 * if necessary.
 *
 * @param method The COAP method used to send the message. This is checked
 * during parsing because certain methods are only allowed to perform certain
 * functions.
 *
 */
void emberAfGatewayRelayCoapParseDotdotMessage(uint8_t length,
                                               uint8_t *string,
                                               int portCounter,
                                               uint16_t method);

/** @brief Returns the length of the return string.
 *
 * The gateway relay COAP plugin will create a response string. The COAP server
 * needs to know the length of that string for the COAP response methods. This
 * API provides that length.
 *
 */
uint16_t emberAfPluginGatewayRelayCoapReturnStringLength(void);

/** @brief Copies the response string into the data in the pointer.
 *
 * Gateway relay COAP plugin may generate a response string. If so, the COAP
 * server will need to obtain it using this API.
 *
 * @param *ptr A pointer to the response string.
 *
 */
void emberAfPluginGatewayRelayCoapCopyReturnString(char *ptr);

/** @brief Returns the COAP response code from the gateway relay COAP plugin.
 *
 * The COAP server needs to know what response (if any) to send as part of the
 * COAP ACK.  This is generated by parsing the message in the gateway-relay-coap
 * plugin. Use this method to communicate it.
 *
 */
uint16_t emberAfPluginGatewayRelayCoapReturnCode(void);

#endif
