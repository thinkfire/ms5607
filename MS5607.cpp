/*
  Author : Amit Ate
  email  : amitate007@gmail.com
*/

#include <MS5607.h>
#include <Wire.h>

MS5607::MS5607()
{
  //do nothing
}

/*
  Initialise library coefficient for measurements
*/

char MS5607::begin()
{
  Wire.begin();
  return(readCalibration());
}

char MS5607::readCalibration()
{

  if(resetDevice() &&
    readUInt(PROM_READ+2, C1) &&
    readUInt(PROM_READ+2*2, C2) &&
    readUInt(PROM_READ+2*3, C3) &&
    readUInt(PROM_READ+2*4, C4) &&
    readUInt(PROM_READ+2*5, C5) &&
    readUInt(PROM_READ+2*6, C6)
  ){
    Serial.println(C1,2);
    Serial.println(C2,2);
    Serial.println(C3,2);
    Serial.println(C4,2);
    Serial.println(C5,2);
    Serial.println(C6,2);
    return (1);
  }else{return(0);}
}

char MS5607::readUInt(char address, double &value)
{
  unsigned char data[2];	//4bit
	data[0] = address;
	if (readBytes(data,2))
	{
		value = (double)(unsigned int)(((unsigned int)data[1]<<8)|(unsigned int)data[0]);
		return(1);
	}
	value = 0;
	return(0);

}

char MS5607::readBytes(unsigned char *values, char length)
{
	char x;

	Wire.beginTransmission(MS5607_ADDR);
	Wire.write(values[0]);
	char error = Wire.endTransmission();
	if (error == 0)
	{
		Wire.requestFrom(MS5607_ADDR,length);
		while(Wire.available() != length) ; // wait until bytes are ready
		for(x=0;x<length;x++)
		{
			values[x] = Wire.read();
		}
		return(1);
	}
	return(0);
}

char MS5607::resetDevice(void){
  Wire.beginTransmission(MS5607_ADDR);
  Wire.write(RESET);
  char error = Wire.endTransmission();
  if(error == 0){
    delay(4);
    return(1);
  }else{return(0);}
}
