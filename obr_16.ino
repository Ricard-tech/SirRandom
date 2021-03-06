#include <Servo.h>

Servo levantador;
Servo agarrador;

int STBY = 26; //standby

//Motor A
int PWMA = 4;  //Speed control
int AIN1 = 28; //Direction
int AIN2 = 30; //Direction

//Motor B
int PWMB = 3;  //Speed control
int BIN1 = 24; //Direction
int BIN2 = 22; //Direction

// SENSOR DE COR - INICIO
//ESQUERDO
const int s0e = 41;
const int s1e = 39;
const int s2e = 45;
const int s3e = 43;
const int oute = 47;
//DIREITO
const int s0d = 40;
const int s1d = 38;
const int s2d = 44;
const int s3d = 42;
const int outd = 46;
// Variables
int redD = 0;
int greenD = 0;
int blueD = 0;
int redE = 0;
int greenE = 0;
int blueE = 0;

// SENSOR DE COR - FIM

void mostrarCor()
{
  corDireito();
  corEsquerdo();
  Serial.print("RR:");
  Serial.print(redD);
  Serial.print("GR:");
  Serial.print(greenD);
  Serial.print("BR:");
  Serial.print(blueD);
  Serial.print("  RL:");
  Serial.print(redE);
  Serial.print("GL:");
  Serial.print(greenE);
  Serial.print("BL:");
  Serial.print(blueE);
  Serial.println();
}

void TestIR()
{
  //menor que 500 branco maior preto
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.print(analogRead(A2));
  Serial.print(" ");
  Serial.print(analogRead(A3));
  Serial.print(" ");
  Serial.print(analogRead(A4));
  Serial.print(" ");
  Serial.println(analogRead(A5));
  Serial.print(" ");
  Serial.println(analogRead(A6));
  Serial.print(" ");
  Serial.println(analogRead(A7));
  Serial.println("-----------------");
  delay(200);
}

void move(int m1, int m2, int m1Vel, int m2Vel)
{

  //frente move(1,1,110,110);
  //tras move(0,0,110,110);
  //direita move(0,1,110,110);
  //esquerda move(1,0,110,110);

  digitalWrite(STBY, HIGH); //disable standby

  if (m1 == 1)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  else
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  analogWrite(PWMA, m1Vel);

  if (m2 == 1)
  {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  else
  {

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  analogWrite(PWMB, m2Vel);
}

void stop()
{
  //enable standby
  digitalWrite(STBY, LOW);
}

void setupMotor()
{
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

//------------ SENSOR DE COR -------------
void corDireito()
{

  digitalWrite(s2d, LOW);
  digitalWrite(s3d, LOW);
  //count OUT, pRed, RED
  redD = pulseIn(outd, digitalRead(outd) == HIGH ? LOW : HIGH);
  digitalWrite(s3d, HIGH);
  //count OUT, pBLUE, BLUE
  blueD = pulseIn(outd, digitalRead(outd) == HIGH ? LOW : HIGH);
  digitalWrite(s2d, HIGH);
  //count OUT, pGreen, GREEN
  greenD = pulseIn(outd, digitalRead(outd) == HIGH ? LOW : HIGH);
}

void corEsquerdo()
{

  digitalWrite(s2e, LOW);
  digitalWrite(s3e, LOW);
  //count OUT, pRed, RED
  redE = pulseIn(oute, digitalRead(oute) == HIGH ? LOW : HIGH);
  digitalWrite(s3e, HIGH);
  //count OUT, pBLUE, BLUE
  blueE = pulseIn(oute, digitalRead(oute) == HIGH ? LOW : HIGH);
  digitalWrite(s2e, HIGH);
  //count OUT, pGreen, GREEN
  greenE = pulseIn(oute, digitalRead(oute) == HIGH ? LOW : HIGH);
}

void setupSensorCorEsquerdo()
{

  pinMode(s0e, OUTPUT);
  pinMode(s1e, OUTPUT);
  pinMode(s2e, OUTPUT);
  pinMode(s3e, OUTPUT);
  pinMode(oute, INPUT);
  digitalWrite(s0e, HIGH);
  digitalWrite(s1e, HIGH);
}

void setupSensorCorDireito()
{

  pinMode(s0d, OUTPUT);
  pinMode(s1d, OUTPUT);
  pinMode(s2d, OUTPUT);
  pinMode(s3d, OUTPUT);
  pinMode(outd, INPUT);
  digitalWrite(s0d, HIGH);
  digitalWrite(s1d, HIGH);
}

void sLinha()
{

  //move(1,0,80,80); DIREITA
  //move(0,1,80,80); Esquerda
  if (analogRead(A2) > 600)
  {
    if (analogRead(A1) > 600)
    {
      if (verde())
        return;
      move(1, 1, 65, 65);
      delay(200);
      stop();
    }
    move(0, 1, 75, 75);
    delay(150);
  }
  if (analogRead(A5) > 600)
  {
    if (analogRead(A6) > 600)
    {
      if (verde())
        return;
      move(1, 1, 65, 65);
      delay(200);
      stop();
    }
    move(1, 1, 75, 75);
    delay(10);
    move(1, 0, 75, 75);
    delay(150);
  }
  move(1, 1, 60, 60);
}
bool verde()
{

  move(1, 1, 70, 70);
  delay(200);
  stop();
  delay(1000);
  corDireito();
  corEsquerdo();

  if (redD && greenD && blueD > 40)
  {

    /* for(int i = 0; i < 5; i++){
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
        }
      */
    move(1, 1, 65, 65);
    delay(100);

    move(1, 0, 75, 75);
    delay(1000);
    while (analogRead(A4) > 600 && analogRead(A3) > 600)
    {
    }

    move(1, 0, 75, 75);
    while (analogRead(A4) < 900)
      ;
    return true;
  }

  if (redE && greenE && blueE > 40)
  {
    /* for(int i = 0; i < 3; i++){
        digitalWr ite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
        }
      */
    move(1, 1, 65, 65);
    delay(100);

    move(0, 1, 75, 75);
    delay(1000);
    while (analogRead(A4) > 600 && analogRead(A3) > 600)
    {
    }

    move(0, 1, 75, 75);
    while (analogRead(A3) < 900)
      ;
    return true;
  }

  move(0, 0, 65, 65);
  delay(200);
  //stop();
  //delay(1000);
  return false;
}

void setup()
{
  setupSensorCorEsquerdo();
  setupSensorCorDireito();
  setupMotor();
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
  levantador.attach(9);
  agarrador.attach(8);
  levantador.write(5);
  agarrador.write(130);
}

void loop()
{
  sLinha();
  delay(5);
}
