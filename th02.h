// @File		TH02.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		02/05/23
//
//
// Copyright (C) 2023  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef TH02_H
#define TH02_H

#define TH02_SLA_W  0x80
#define TH02_SLA_R  0x81

void TH02_Write(unsigned char reg, unsigned char byte)
{
    Wire_Start();
    Wire_Write( TH02_SLA_W );
    Wire_Write( reg );
    Wire_Write( byte );
    Wire_Stop();
}

unsigned char TH02_Read_ID(void)
{
    unsigned char data = 0x00;
    
    Wire_Start();
    Wire_Write( TH02_SLA_W );
    Wire_Write( 0x11 );
    Wire_Start();
    Wire_Write( TH02_SLA_R );
    data = Wire_Nack();
    Wire_Stop();
    
    return ( data );
}

unsigned char TH02_Read_RDY(void)
{
    unsigned char data = 0x00;
    
    Wire_Start();
    Wire_Write( TH02_SLA_W );
    Wire_Write( 0x00 );
    Wire_Start();
    Wire_Write( TH02_SLA_R );
    data = Wire_Nack();
    Wire_Stop();
    
    return ( data );
}

unsigned int TH02_Read_temp(void)
{
    TH02_Write(0x03, 0x11);
    
    while(TH02_Read_RDY());
    
    unsigned char msb = 0;
    unsigned char lsb = 0;
    
    Wire_Start();
    Wire_Write( TH02_SLA_W );
    Wire_Write( 0x01 );
    Wire_Start();
    Wire_Write( TH02_SLA_R );
    msb = Wire_Ack();
    lsb = Wire_Nack();
    Wire_Stop();
    
    unsigned int data = (unsigned int) ( ( msb << 8) | lsb );
    
    data >>= 2;
    
    data = (unsigned int) ( (data / 32) - 50);
    
    return ( (unsigned int) data );
}

unsigned int TH02_Read_Humi(void)
{
    TH02_Write(0x03, 0x01);
    
    while(TH02_Read_RDY());
    
    unsigned char msb = 0;
    unsigned char lsb = 0;
    
    Wire_Start();
    Wire_Write( TH02_SLA_W );
    Wire_Write( 0x01 );
    Wire_Start();
    Wire_Write( TH02_SLA_R );
    msb = Wire_Ack();
    lsb = Wire_Nack();
    Wire_Stop();
    
    unsigned int data = (unsigned int) ( ( msb << 8) | lsb );
    
    data >>= 4;
    
    data = (unsigned int) ( (data / 16) - 24);
    
    return ( (unsigned int) data );
}

#endif
