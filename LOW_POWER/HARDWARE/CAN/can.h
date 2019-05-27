#ifndef CAN_H
#define CAN_H


/* CAN functions declaration */
bool CAN_init(ARM_DRIVER_CAN *ptrCAN);
void CAN_SignalUnitEvent (uint32_t event);
void CAN_SignalObjectEvent (uint32_t obj_idx, uint32_t event);
void Error_Handler (void);
#endif
