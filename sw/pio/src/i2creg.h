#ifdef __cplusplus
extern "C" {
#endif
/* Author, Copyright: Oleg Borodin <onborodin@gmail.com> 2018 */

uint16_t i2c_read_seq(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t *data, uint16_t len);
uint16_t i2c_write_seq(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t *data, uint16_t len);

void i2c_write_reg(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t data);
uint8_t i2c_read_reg(uint32_t i2c, uint16_t addr, uint8_t reg);

void i2c_set_bit_field(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len, uint8_t data);
void i2c_clean_bit_field(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len);

void i2c_set_one_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base);
void i2c_clean_one_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base);

void i2c_set_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t mask);
void i2c_clean_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t mask);

#ifdef __cplusplus
}
#endif

/* EOF */
