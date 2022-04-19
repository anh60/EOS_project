/**
 * @file flash.h
 * @author Maja Markusson
 * @brief
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <rtdef.h>

#ifndef APPLICATIONS_SERVO_H_
#define APPLICATIONS_SERVO_H_

#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */

static void FLASH_Program_Word(uint32_t Address, uint32_t Data);
