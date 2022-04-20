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

#ifndef APPLICATIONS_FLASH_H_
#define APPLICATIONS_FLASH_H_

#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */

void FLASH_Program_Word(uint32_t Address, uint32_t Data);
static uint32_t rearrange4mem(uint32_t data);

#endif /* APPLICATIONS_FLASH_H_ */
