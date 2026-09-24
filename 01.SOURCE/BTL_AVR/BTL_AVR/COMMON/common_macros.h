#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

/* Set a bit in any register */
#define SET_BIT(REG, BIT) (REG |= (1 << BIT))

/* Clear a bit in any register */
#define CLEAR_BIT(REG, BIT) (REG &= (~(1 << BIT)))  

/* Toggle a bit in any register */
#define TOGGLE_BIT(REG, BIT) (REG ^= (1 << BIT))

/* Check if a bit is set in any register */
#define BIT_IS_SET(REG, BIT) (REG & (1 << BIT))

/* Check if a bit is clear in any register */
#define BIT_IS_CLEAR(REG, BIT) (!(REG & (1 << BIT)))

/* Get the value of a bit in any register */
#define GET_BIT(REG, BIT) ((REG & (1 << BIT)) >> BIT)

#endif // COMMON_MACROS_H