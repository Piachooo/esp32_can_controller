// #include <CAN_config.h>
// #include <ESP32CAN.h>

// CAN_device_t CAN_cfg;
// setup()
// {
// CAN_cfg.speed = CAN_SPEED_1000KBPS;
//   CAN_cfg.tx_pin_id = GPIO_NUM_12; // green wire
//   CAN_cfg.rx_pin_id =  GPIO_NUM_13; // white wire
//   CAN_cfg.rx_queue = xQueueCreate(3, sizeof(CAN_frame_t));
//   //start CAN Module
//   ESP32Can.CANInit();

//  xTaskCreatePinnedToCore ( fSendCAN_Buss, "fSendCAN_Buss", TaskStack15K, NULL, Priority4, NULL, TaskCore0 );
//   sema__Send_CAN_Bus = xSemaphoreCreateMutex();
//   xSemaphoreGive ( sema__Send_CAN_Bus );
// }

// void fSendCAN_Buss( void *pvParameters )
// {
//   stuSERVO_Message pxServo_Message;
//   for ( ;; )
//   {
//     xEventGroupWaitBits (eg, evtSendCAN_Buss, pdTRUE, pdTRUE, portMAX_DELAY);
//     if ( xSemaphoreTake( sema__Send_CAN_Bus, xTicksToWait0 ) == pdTRUE ) // grab semaphore no wait
//     {
//       CAN_frame_t rx_frame;
//       // Serial.println ( " fSendCAN_Buss 2 "  );
//       if ( (CAN_cfg.rx_queue != NULL) && (uxQueueMessagesWaiting(CAN_cfg.rx_queue)) ) // if queue not null and something is waiting in queue
//       {
//         // Serial.println ( uxQueueMessagesWaiting(CAN_cfg.rx_queue) );
//         if (xQueueReceive( CAN_cfg.rx_queue, &rx_frame , xTicksToWait0) == pdTRUE )
//         {
//           if ( rx_frame.MsgID == 2 )
//           {
//             // Serial.println ( rx_frame.data.u8[0] );
//             if ( rx_frame.data.u8[0] == '6' )
//             {
//               EOT = false;
//               // Serial.print ( " frame ID " );
//               // Serial.print ( rx_frame.MsgID );
//               // Serial.println ( "ACK" );
//               //              rx_frame.FIR.B.FF = CAN_frame_std;
//               //              rx_frame.MsgID = xServo_EOT.MsgID;
//               //              rx_frame.FIR.B.DLC = xServo_EOT.DLC;
//               //              rx_frame.data.u8[0] = xServo_EOT.Servo_EOT;
//               //              rx_frame.data.u8[1] = xServo_EOT.p4; // send all '0'
//               //              rx_frame.data.u8[2] = xServo_EOT.p4;
//               //              rx_frame.data.u8[3] = xServo_EOT.p4;
//               //              rx_frame.data.u8[4] = xServo_EOT.p4;
//               //              rx_frame.data.u8[5] = xServo_EOT.p4;
//               //              rx_frame.data.u8[6] = xServo_EOT.p4;
//               //              rx_frame.data.u8[7] = xServo_EOT.p4;
//               //              ESP32Can.CANWriteFrame(&rx_frame);
//               // Serial.println ( " sent Servo controller ack " );
//               //              vTaskDelay( pdMS_TO_TICKS( 6 ) );
//             }
//             //            if (rx_frame.data.u8[0] = '3')
//             //              {
//             //                EOT = false;
//             //              }
//             if ( rx_frame.data.u8[0] == '4' )
//             {
//               //                          rx_frame.FIR.B.FF = CAN_frame_std;
//               //                          rx_frame.MsgID = xServo_EOT.MsgID;
//               //                          rx_frame.FIR.B.DLC = xServo_EOT.DLC;
//               //                          rx_frame.data.u8[0] = '4';
//               //                          rx_frame.data.u8[1] = xServo_EOT.p4;
//               //                          rx_frame.data.u8[2] = xServo_EOT.p4;
//               //                          rx_frame.data.u8[3] = xServo_EOT.p4;
//               //                          rx_frame.data.u8[4] = xServo_EOT.p4;
//               //                          rx_frame.data.u8[5] = xServo_EOT.p4;
//               //                          rx_frame.data.u8[6] = xServo_EOT.p4;
//               //                          rx_frame.data.u8[7] = xServo_EOT.p4;
//               //                          ESP32Can.CANWriteFrame(&rx_frame);
//               // Serial.println ( "InitComplete ack " );
//               EOT = false;
//               xSemaphoreGive ( sema_HexaPodAdjustment ); // begin walking forward task
//             }
//           } // if ( rx_frame.MsgID == 2 )
//         } // if (xQueueReceive( CAN_cfg.rx_queue, &rx_frame , xTicksToWait5) == pdTRUE )
//       } // if ( (CAN_cfg.rx_queue != NULL) && (uxQueueMessagesWaiting(CAN_cfg.rx_queue)) )
//       //      // ack the initialization
//       if ( xQueueReceive ( xQ_SERVO_Message, &pxServo_Message, QueueReceiveDelayTime ) == pdTRUE )
//       {
//         rx_frame.FIR.B.FF = CAN_frame_std;
//         rx_frame.MsgID = pxServo_Message.MsgID;
//         rx_frame.FIR.B.DLC = pxServo_Message.DLC;
//         rx_frame.data.u8[0] = pxServo_Message.Instruction;
//         rx_frame.data.u8[1] = pxServo_Message.p1;
//         rx_frame.data.u8[2] = pxServo_Message.p2;
//         rx_frame.data.u8[3] = pxServo_Message.p3;
//         rx_frame.data.u8[4] = pxServo_Message.p4; // end of torque to position
//         rx_frame.data.u8[5] = pxServo_Message.p5;
//         rx_frame.data.u8[6] = pxServo_Message.p6;
//         rx_frame.data.u8[7] = pxServo_Message.p7;
//         //                Serial.print ( " message in sendCanBus " );
//         //                Serial.print ( ", " );
//         //                Serial.print ( rx_frame.data.u8[0] );
//         //                Serial.print ( ", " );
//         //                Serial.print ( rx_frame.data.u8[1] );
//         //                Serial.print ( ", " );
//         //                Serial.print (rx_frame.data.u8[2] );
//         //                Serial.print ( ", " );
//         //                Serial.print ( rx_frame.data.u8[3] );
//         //                Serial.print ( ", " );
//         //                Serial.print ( rx_frame.data.u8[4] );
//         //                Serial.println ( " message end." );
//         ESP32Can.CANWriteFrame(&rx_frame);
//       }
//       //
//       xSemaphoreGive ( sema__Send_CAN_Bus );
//       ////
//       // Serial.print( "fSendCAN_Buss " );
//       // Serial.print(uxTaskGetStackHighWaterMark( NULL ));
//       // Serial.println();
//       // Serial.flush();
//     }  // if ( xSemaphoreTake( sema__Send_CAN_Bus, xTicksToWait0 ) == pdTRUE ) // grab semaphore no wait
//   } // the for loop
//   vTaskDelete( NULL );
// } // void fSendCAN_Buss( void *pvParameters )
// /////////////////////////////////////////////////////