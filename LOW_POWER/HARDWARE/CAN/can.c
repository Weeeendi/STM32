#include "RTE_Components.h"
#include "main.h"


#define CAN_OK 1

#define  CAN_CONTROLLER         1
#define  CAN_LOOPBACK           1       // 0 = no loopback, 1 = external loopback
#define  CAN_BITRATE_NOMINAL    250000  // Nominal bitrate (125 kbit/s)

#define _CAN_Driver_(n)         Driver_CAN##n
#define  CAN_Driver_(n)        _CAN_Driver_(n)
extern   ARM_DRIVER_CAN         CAN_Driver_(CAN_CONTROLLER);
#define  ptrCAN               (&CAN_Driver_(CAN_CONTROLLER))

uint32_t                        rx_obj_idx;
uint8_t                         rx_data[8];
ARM_CAN_MSG_INFO                rx_msg_info;
uint32_t                        tx_obj_idx;
uint8_t                         tx_data[8];
ARM_CAN_MSG_INFO                tx_msg_info;

/*------------------------------------------------------------------------------
 *        CAN Signal Unit Event Callback
 *----------------------------------------------------------------------------*/
void Error_Handler (void) {
    while (1);    //Exception handling function
}

void CAN_SignalUnitEvent (uint32_t event) {
    switch (event) {
    case ARM_CAN_EVENT_UNIT_ACTIVE:
        break;
    case ARM_CAN_EVENT_UNIT_WARNING:
        break;
    case ARM_CAN_EVENT_UNIT_PASSIVE:
        break;
    case ARM_CAN_EVENT_UNIT_BUS_OFF:
        break;
    }
}

/*------------------------------------------------------------------------------
 *        CAN Signal Object Event Callback
 *----------------------------------------------------------------------------*/
void CAN_SignalObjectEvent (uint32_t obj_idx, uint32_t event) {

    if (obj_idx == rx_obj_idx) {                  // If receive object event
        if (event == ARM_CAN_EVENT_RECEIVE) {       // If message was received successfully
            ptrCAN->MessageRead(rx_obj_idx, &rx_msg_info, rx_data, 8U);
            osSignalSet(LCD_ID, 1U);
            // Read received message
            // process received message ...
        }
    }

if (obj_idx == tx_obj_idx) {                  // If transmit object event
    if (event == ARM_CAN_EVENT_SEND_COMPLETE) { // If message was sent successfully
        // acknowledge sent message ...
        osSignalSet(LCD_ID, 1U << 1);       // Send signal to user interface thread
    }
}
}

bool CAN_Initialize(void) {
    ARM_CAN_CAPABILITIES     can_cap;
    ARM_CAN_OBJ_CAPABILITIES can_obj_cap;

    int32_t status;
    u32 i, num_objects;

    can_cap = ptrCAN->GetCapabilities(); //Get CAN driver capabilities
    num_objects = can_cap.num_objects;  //Number of receive/transmit objects

    status = ptrCAN->Initialize(CAN_SignalUnitEvent, CAN_SignalObjectEvent);
    if(status != ARM_DRIVER_OK) Error_Handler();

    status = ptrCAN->PowerControl(ARM_POWER_FULL);
    if(status != ARM_DRIVER_OK) Error_Handler();

    status = ptrCAN->SetMode(ARM_CAN_MODE_INITIALIZATION);
    if(status != ARM_DRIVER_OK) Error_Handler();

    status = ptrCAN->SetBitrate(ARM_CAN_BITRATE_NOMINAL,
                                250000U,
                                ARM_CAN_BIT_PROP_SEG(5U) |
                                ARM_CAN_BIT_PHASE_SEG1(1U) |
                                ARM_CAN_BIT_PHASE_SEG2(1U) |
                                ARM_CAN_BIT_SJW(1U)
                               );
    if(status != ARM_DRIVER_OK) Error_Handler();

    rx_obj_idx = 0xFFFFFFFFU;
    tx_obj_idx = 0xFFFFFFFFU;

    for(i = 0U; i < num_objects ; i++) {
        can_obj_cap = ptrCAN->ObjectGetCapabilities(i);
        if((rx_obj_idx == 0xFFFFFFFFU) && (can_obj_cap.rx == 1U)) {
            rx_obj_idx = i;
        }
        else if((tx_obj_idx == 0xFFFFFFFFU) && (can_obj_cap.tx == 1U)) {
            tx_obj_idx = i;
            break;
        }
    }
    if((rx_obj_idx == 0xFFFFFFFFU) || (tx_obj_idx == 0xFFFFFFFFU)) {
        Error_Handler();
    }

    //setup filter to receive messages with extend ID 0x12345678 to receive msg
    status = ptrCAN->ObjectSetFilter(rx_obj_idx, ARM_CAN_FILTER_ID_EXACT_ADD, ARM_CAN_EXTENDED_ID(0x12345678), 0U);
    if(status != ARM_DRIVER_OK) Error_Handler();

    status = ptrCAN->ObjectConfigure(tx_obj_idx, ARM_CAN_OBJ_TX);
    if(status != ARM_DRIVER_OK) Error_Handler();

    status = ptrCAN->ObjectConfigure(rx_obj_idx, ARM_CAN_OBJ_RX);
    if(status != ARM_DRIVER_OK) Error_Handler();

#if (CAN_LOOPBACK == 1)
    if (can_cap.external_loopback != 1U) {
        return false;
    }
    status = ptrCAN->SetMode (ARM_CAN_MODE_LOOPBACK_EXTERNAL);                    // Activate loopback external mode
    if (status != ARM_DRIVER_OK) {
        return false;
    }
#else
    status = ptrCAN->SetMode (ARM_CAN_MODE_NORMAL);                               // Activate normal operation mode
    if (status != ARM_DRIVER_OK) {
        return false;
    }
#endif
    return CAN_OK;
}

void CAN_Thread(void const *arg) {
    uint32_t i;

    memset(&tx_msg_info, 0U, sizeof(ARM_CAN_MSG_INFO));
    tx_msg_info.id = ARM_CAN_EXTENDED_ID(0x12345678U);
    tx_data[0] = 0xFFU;
    while(1) {
        i = (i + 1U) & 0xFFU;
        memset(tx_data, i, 8U);

        //Send data message
        ptrCAN->MessageSend(tx_obj_idx, &tx_msg_info, tx_data, 8U);
        osDelay(1000U);
    }
}

