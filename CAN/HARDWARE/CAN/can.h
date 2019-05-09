#ifndef CAN_H
#define CAN_H

#define CAN_TX_Pin GPIO_Pin_12
#define CAN_RX_Pin GPIO_Pin_11
#define CAN_TX_Port GPIOA
#define CAN_RX_Port GPIOA

void CAN1_Init(void);
void CAN1_MODE_Config(void);

#endif
