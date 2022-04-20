/**
 * @file flash.h
 * @author Maja Markusson
 * @brief Functionality for storing to and reading from mcu flash memory. 
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

/**
 * @brief Function reused from flash library of the mcu. 
 * 
 * @param Address start address of the flash operation. 
 * @param Data    dataword to be written to memory. 
 */
void FLASH_Program_Word(uint32_t Address, uint32_t Data);

/**
 * @brief As the edians changes when writing to memory. When read the values need
 *        to be rearranged to appear the same. 
 * 
 * @param Data      dataword as read from memory
 * @return uint32_t the correct value as written to memory
 */
uint32_t rearrangeMemoryVal(uint32_t Data);

#endif /* APPLICATIONS_FLASH_H_ */
