#include <imumaths.h>


imu::Quaternion launchPosWorld;     // Referenshöjd. Noll är ?? meter under/över startplattan
imu::Quaternion launchOrientWorld;   // Kompassriktning, pekar uppåt
imu::Quaternion rocketPosWorld;     // Avvikelse från launchPos
imu::Quaternion rocketOrientWorld;  // Raketens riktning i det stora koordinatsystemet
imu::Quaternion sensorAccRocket;      // Sensorernas orientering inuti raketen.
imu::Quaternion sensorGyroRocket;     // Sensorernas orientering inuti raketen.
imu::Quaternion sensorAltitudeWorld; // Sensorernas orientering inuti raketen.
imu::Quaternion sensorCompassRocket;  // Sensorernas orientering inuti raketen.

void setup()
{

}

void loop()
{

/*  

Förenklad modell 1:

* Bara y-ledsförflyttning. Strunta i x och z
* Massan oförändrad
* Bara höjd är av intresse.
* Strunta i rotation och kompass.
* Strunta i allt som händer efter separation
* Inmätning av maxhöjd och flight-tid












  
  1) Stilla på startplattan
      launchPosWorld = höjden y är barometrisk höjd
                       definitionsmässigt är |z| = 0 och |x| = 0
      launchOrientWorld = riktningen ges av kompassen och gravitationsvektorn


  2) Launch (take off)
      Vid launch-ögonblicket sätts:
    
      rocketPosWorld = launchPosWorld
      rocketOrientWorld = launchOrientWorld
    
  3) Flight - Engine BURNING
  
        Sensorvärden läses in och fördelas på 
          sensorAccRocket
          sensorGyroRocket 
          sensorAltitudeWorld
          sensorCompassRocket
          
       
        Gyroskopisk vridning är i koordinatsystemet Rocket och ska mappas till World
        
          sensorGyroWorld
          
        som används för att ge ny orientering av raketen: rocketOrientWorld.
        
        sensorCompassRocket mappas även den och om lutningen på raketen är för stor 
        så kan inte kompassvärdet användas.
        
        korrigera rocketOrientWorld med kompassvärdet          
        

        Accelerationen ska vridas till koordinatsystemet World och hamnar i:
        
          sensorAccWorld
          
        Den anväds sedan för att påverka rocketPosWorld
        
        korrigera höjdvärdet med sensorAltitiudeWorld (Kalman)
        
        
        Fysmodellen:
        
          * Motoracceleration i positiv y-led (Rocket)
          * Luftmotstånd i negativ y-led (Rocket) proportionell mot v2
          * Tyngdkraftsacceleration i negativ y-led (World)
          * Massan reduceras vartefter enligt förbränningsmodellen
        


  4) Flight - Coast
  
      Som tidigare fast med modifierad fysmodell:

        Fysmodellen:
        
          * Luftmotstånd i negativ y-led (Rocket)
          * Tyngdkraftsacceleration i negativ y-led (World)
          * Massan marginellt enligt förbränningsmodellen (delay)
          
          
  5)  Separation

      Tumlar runt och fallskärm vecklas ut.
      Sensorvärden kan vara rätt opålitliga.
      Antag att raketen är i separations-stadiet i c:a en sekund.
      
      Fysmodellen:
          * Vi kan anta att tyngdpunkten fortsätter i samma rikning men med kraftig inbromsning
          * Hela motorns drivdel är borta.
          

  6)  Falling

      Fysmodellen:
          * Fallande. Massa som ovan.
          * Orienteringen av payload borde vara rakt nedåtpekande
          * Luftmotstånd från fallskärmen -> konstant fallhastighet
          * Se upp med kompassvärdena eftersom sensorn är uppochned.
          * Strunta i gyrovärden. Använd bara kompass.
          
  
  
  */
}

