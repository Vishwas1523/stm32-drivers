/*
 * bitmanipulation.h
 *
 *  Created on: Jun 17, 2026
 *      Author: VICTUS
 */

#ifndef INC_BITMANIPULATION_H_
#define INC_BITMANIPULATION_H_

#define BIT(pos)              (1U << (pos))
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define RESET_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define TOGGLE_BIT(REG, BIT)  ((REG) ^= (BIT))
#define READ_BIT(REG, BIT)    (((REG) & (BIT)) != 0U)

#endif /* INC_BITMANIPULATION_H_ */
