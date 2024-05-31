function decodeUplink(input) {
 var data = {};
 data.key ="asaxfryhvuvr3vpd";
 
 // Capteur de température et d'humidité DHT22
 data.t_9 = ((input.bytes[1] << 8) | input.bytes[0])/100; //Humidité intérieur
 data.t_0 = ((input.bytes[3] << 8) | input.bytes[2])/100;
 
 // Capteur de température One Wire 1
 data.t_1 = ((input.bytes[5] << 8) | input.bytes[4])/100;
 
 // Capteur de température One Wire 2
 data.t_2 = ((input.bytes[7] << 8) | input.bytes[6])/100;
 
 // Capteur de luminosité SEN0562
 data.l = ((input.bytes[9] << 8) | input.bytes[8]) / 1.2;
 
 // Capteur de poids HX711
 data.weight_kg = ((input.bytes[11] << 8) | input.bytes[10])/100;
 // Capteur de température et d'humidité extérieur SEN0227
 data.t = (input.bytes[13] << 8 | input.bytes[12])/100;
 data.h = (input.bytes[15] << 8 | input.bytes[14])/100;
 
 //Batterie en pourcentage
 data.b = (input.bytes[17] << 8 | input.bytes[16])/100;
 
 return {
 data: data,
 warnings: [],
 errors: []
 };
}
