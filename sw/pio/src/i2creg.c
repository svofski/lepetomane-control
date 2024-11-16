
/* Author, Copyright: Oleg Borodin <onborodin@gmail.com> 2018 */

#include <libopencm3/stm32/i2c.h>
#include <stdlib.h>
#include <i2creg.h>

volatile int acked_addr = 0;

uint16_t i2c_read_seq(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t *data, uint16_t len) {
    I2C_CR1(i2c) = 0;
    I2C_CR1(i2c) = 1;
    
    //i2c_enable_ack(i2c);
    i2c_send_start(i2c);

    /* I2C_EVENT_MASTER_MODE_SELECT EV5: BUSY, MSL and SB */
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, addr, I2C_WRITE);
    /* I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED EV6: BUSY, MSL, ADDR, TXE and TRA */
    while (!(  (I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_ADDR)) & 
               (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)) ))
    {
        if (I2C_SR1(i2c) & I2C_SR1_AF) {
            while(I2C_CR1(i2c) & (I2C_CR1_START|I2C_CR1_STOP|I2C_CR1_PEC));
            I2C_CR1(i2c) |= I2C_CR1_STOP;
            while(I2C_CR1(i2c) & (I2C_CR1_START|I2C_CR1_STOP|I2C_CR1_PEC));
            return -1;
        }
    };
    (void)I2C_SR2(i2c);

    acked_addr = addr;
    *((int *)0) = 0;


    i2c_send_data(i2c, reg);
    /* I2C_EVENT_MASTER_BYTE_TRANSMITTED EV8_2: TRA, BUSY, MSL, TXE and BTF */
    while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));


    i2c_send_start(i2c);
    /* I2C_EVENT_MASTER_MODE_SELECT EV5: BUSY, MSL and SB */
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, addr, I2C_READ);
    /* I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED EV6: BUSY, MSL and ADDR */
    while (!(  (I2C_SR1(i2c) & (I2C_SR1_ADDR)) &
               (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)) ));


    uint16_t i;
    for (i = 0; i < len; i++) {
        if (i == len - 1) {
            i2c_disable_ack(i2c);
            //i2c_nack_current(i2c);
            i2c_send_stop(i2c);
        }
        /* I2C_EVENT_MASTER_BYTE_RECEIVED EV7: BUSY, MSL and RXNE */
        while (!(I2C_SR1(i2c) & I2C_SR1_RxNE));
        data[i] = i2c_get_data(i2c);
    }

    while ((I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)));
    return ++i;
}

uint16_t i2c_write_seq(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t *data, uint16_t len) {

    i2c_enable_ack(i2c);
    i2c_send_start(i2c);

    /* I2C_EVENT_MASTER_MODE_SELECT EV5: BUSY, MSL and SB */
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, addr, I2C_WRITE);
    /* I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED EV6: BUSY, MSL, ADDR, TXE and TRA */
    while (!(  (I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_ADDR)) & 
               (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)) ));
    //(void)I2C_SR2(i2c);

    i2c_send_data(i2c, reg);
    /* I2C_EVENT_MASTER_BYTE_TRANSMITTED EV8_2: TRA, BUSY, MSL, TXE and BTF */
    while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));

    uint16_t i;
    for (i = 0; i < len; i++) {
        i2c_send_data(i2c, data[i]);
        /* I2C_EVENT_MASTER_BYTE_TRANSMITTED EV8_2: TRA, BUSY, MSL, TXE and BTF */
        while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) & 
                (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));
    }

    i2c_send_stop(i2c);

    while ((I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)));
    return ++i;
}

void i2c_write_reg(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t data) {
    i2c_write_seq(i2c, addr, reg, &data, 1);
}

uint8_t i2c_read_reg(uint32_t i2c, uint16_t addr, uint8_t reg) {
    uint8_t data;
    i2c_read_seq(i2c, addr, reg, &data, 1);
    return data;
}


void i2c_set_bit_field(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len, uint8_t data) {
    uint8_t rdata = 0;
    rdata = i2c_read_reg(i2c, addr, reg);
    uint8_t mask = 0xFF & ((0xFF << (base + len)) | 0xFF >> (8 - base));
    rdata &= mask;
    data <<= base;
    data &= ~mask;
    rdata |= data;
    i2c_write_reg(i2c, addr, reg, rdata);
}

void i2c_clean_bit_field(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len) {
    uint8_t rdata = 0;
    rdata = i2c_read_reg(i2c, addr, reg);
    uint8_t mask = 0xFF & ((0xFF << (base + len)) | 0xFF >> (8 - base));
    rdata &= mask;
    i2c_write_reg(i2c, addr, reg, rdata);
}


void i2c_set_one_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base) {
    uint8_t rdata = i2c_read_reg(i2c, addr, reg);
    rdata |= (1 << base);
    i2c_write_reg(i2c, addr, reg, rdata);
}

void i2c_clean_one_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base) {
    uint8_t rdata = i2c_read_reg(i2c, addr, reg);
    rdata &= ~(1 << base);
    i2c_write_reg(i2c, addr, reg, rdata);
}


void i2c_set_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t mask) {
    uint8_t rdata = i2c_read_reg(i2c, addr, reg);
    rdata |= mask;
    i2c_write_reg(i2c, addr, reg, rdata);
}

void i2c_clean_bit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t mask) {
    uint8_t rdata = i2c_read_reg(i2c, addr, reg);
    rdata &= ~(mask);
    i2c_write_reg(i2c, addr, reg, rdata);
}



#if 0

void _i2c_write_reg(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t data) {

    i2c_enable_ack(i2c);
    i2c_send_start(i2c);

    /* I2C_EVENT_MASTER_MODE_SELECT EV5: BUSY, MSL and SB */
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, addr, I2C_WRITE);
    /* I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED EV6: BUSY, MSL, ADDR, TXE and TRA */
    while (!(  (I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_ADDR)) & 
               (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)) ));
    //(void)I2C_SR2(i2c);

    i2c_send_data(i2c, reg);
    /* I2C_EVENT_MASTER_BYTE_TRANSMITTED EV8_2: TRA, BUSY, MSL, TXE and BTF */
    while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));

    i2c_send_data(i2c, data);
    /* I2C_EVENT_MASTER_BYTE_TRANSMITTED EV8_2: TRA, BUSY, MSL, TXE and BTF */
    while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));

    i2c_send_stop(i2c);

    while ((I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)));
}


uint8_t _i2c_read_reg(uint32_t i2c, uint16_t addr, uint8_t reg) {
    uint8_t data = 0;

    i2c_enable_ack(i2c);
    i2c_send_start(i2c);

    /* I2C_EVENT_MASTER_MODE_SELECT EV5: BUSY, MSL and SB */
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, addr, I2C_WRITE);
    /* I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED EV6: BUSY, MSL, ADDR, TXE and TRA */
    while (!(  (I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_ADDR)) & 
               (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)) ));
    (void)I2C_SR2(i2c);

    i2c_send_data(i2c, reg);
    /* I2C_EVENT_MASTER_BYTE_TRANSMITTED EV8_2: TRA, BUSY, MSL, TXE and BTF */
    while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));

    i2c_send_start(i2c);
    /* I2C_EVENT_MASTER_MODE_SELECT EV5: BUSY, MSL and SB */
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & 
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, addr, I2C_READ);
    /* I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED EV6: BUSY, MSL and ADDR */
    while (!(  (I2C_SR1(i2c) & (I2C_SR1_ADDR)) &
               (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)) ));

    i2c_disable_ack(i2c);
    i2c_send_stop(i2c);
    /* I2C_EVENT_MASTER_BYTE_RECEIVED EV7: BUSY, MSL and RXNE */
    while (!( (I2C_SR1(i2c) & I2C_SR1_RxNE )));
    data = i2c_get_data(i2c);

    while ((I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)));

    return data;
}
#endif

/* EOF */
