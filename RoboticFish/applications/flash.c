/**
 * @file flash.c
 * @author Maja Markusson
 * @brief
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "flash.h"
#include <stdlib.h>
#include "board.h"
#include "stm32f4xx_hal.h"

static void FLASH_Program_Word(uint32_t Address, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* If the previous operation is completed, proceed to program the new data */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_WORD;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint32_t*)Address = Data;
}

//only needed if we are going to read back
static uint32_t rearrange4mem(uint32_t data){
    uint32_t tmp = data;
    tmp &= 0x11000000;
    tmp = tmp >> 6;

    data &= 0x00110000;
    data = data >> 2;

    data |= tmp;

    return data;
}
