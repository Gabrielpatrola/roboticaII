// Thiago Sodre - sodrecvel@yahoo.com.br
// Robo Bluetooth
// Cascavel - PR

// Inclui Biblioteca serial
 #include <SoftwareSerial.h> 

// Lembra que: um Tx(Transmite) liga no outro Rx(Recebe)
// * RX no pin 2 (connectado ao TX do Bluetooth)
// * TX no pin 3 (connectado ao RX do bluetooth)
// Criando a nova porta de comunicaçao serial Bluetooth pelos pinos Rx=2 e Tx=3 evitando conflitos com a comunicao USb do Arduino...
  SoftwareSerial Bluetooth(2, 3); // 2-RX, 3-TX

//Definicoes para Pinos Arduino referentes os motores e ligados a Ponte H com controle PWM
int M_Dir_A = 4;          // Pino A do Motor Direito
int M_Dir_B = 5;          // Pino B do Motor Direito
int M_Dir_V = 6;          // Controle por PWM para Velocidade do Motor Direito
int M_Esq_A = 7;          // Pino A do Motor Esquerdo
int M_Esq_B = 8;          // Pino B do Motor Esquerdo
int M_Esq_V = 9;          // Controle por PWM para Velocidade do Motor Esquerdo
const int Farol = 13;     // Pino Led Frente
const int Lanterna = 12;  // Pino Led Traseira
const int Alerta = 11;    // Pino Led Alerta
const int Buzzer = 10;    // Pino Buzina

//Declaraço de Variaveis a serem utilizadas 
char Comando;             // Comando recebe a leitura de via Serial.read do Bluetooth
int Pisca;                // Ativar e Contador para Pisca Alerta
int Bip;                  // Ativar Bip de Re
int BipC;                 // Contador de tempo Bip de Re
int Velox;                // Definiçao de Velocidade

// Criando SubRotinas Movimento
void PARE();
void OFF();
void FRENTE();
void RE();
void DIREITA();
void ESQUERDA();
void EIXODIREITA();
void EIXOESQUERDA();
void REDIREITA();
void REESQUERDA();


// VOID SETUP ==>> Executado 1x na inicializaço do Arduino
void setup()                   
{
 Bluetooth.begin(9600);    // Estabelece Velocidade da comunicação
//Define os pinos como saida
 pinMode(M_Dir_A, OUTPUT);
 pinMode(M_Dir_B, OUTPUT);
 pinMode(M_Dir_V, OUTPUT);
 pinMode(M_Esq_A, OUTPUT);
 pinMode(M_Esq_B, OUTPUT);
 pinMode(M_Esq_V, OUTPUT);
 pinMode(Farol, OUTPUT); 
 pinMode(Lanterna, OUTPUT);
 pinMode(Alerta, OUTPUT);
 pinMode(Buzzer, OUTPUT); 

// Zerando Variaveis
 Pisca=0; Bip=0; BipC=0; Velox=0;
 
PARE();                        // Sub-Rotina para PARAR tudo... 
}


void loop()
{
 char Comando = Bluetooth.read(); // Leitura de dados do Bluetooth
 Serial.println(Comando);

//  Inicio dos testes sobre a Variavel Comando
/*  Comandos recebidos via APP Bluetooth RC Controler
 Forward          Frente            => F                Back             Re                => B
 Left             Esquerda          => L                Right            Direita           => R
 Forward Left     Frente Esquerda   => G                Forward Right    Frente Direita    => I
 Back Left        Re Esquerda       => H                Back Right       Re Direita        => J
 Stop             Pare              => S                Stop All         Para Tudo         => D
 Front Lights On  Ligar Farol       => W (Maiusculo)    Front Lights Off Desligar Farol    => w (Minusculo)
 Back Lights On   Ligar Lanterna    => U (Maiusculo)    Back Lights Off  Desligar Lanterna => u (Minusculo)
 Horn On          Ligar Buzzer      => V (Maiusculo)    Horn Off         Desligar Buzzer   => v (Minusculo)
 Extra On         Ligar Alerta      => X (Maiusculo)    Extra Off        Desliga Alerta    => x (Minusculo)
 Speed 0          Velocidade 0%     => 0 (Zero)         Speed 10         Velocidade 10%    => 1 
 Speed 20         Velocidade 20%    => 2                Speed 30         Velocidade 30%    => 3 
 Speed 40         Velocidade 40%    => 4                Speed 50         Velocidade 50%    => 5 
 Speed 60         Velocidade 60%    => 6                Speed 70         Velocidade 70%    => 7 
 Speed 80         Velocidade 80%    => 8                Speed 90         Velocidade 90%    => 9 
 Speed 100        Velocidade 100%   => q (Minusculo)
*/
//  Testes Direção Recebida 
switch(Comando)
   {
    // COMANDOS DE VELOCIDADE  O da onda PWM vai de 0 a 255
      case '0':  {  Velox=0;                   }  break;
      case '1':  {  Velox=120;                 }  break;
      case '2':  {  Velox=130;                 }  break;
      case '3':  {  Velox=140;                 }  break;
      case '4':  {  Velox=150;                 }  break;
      case '5':  {  Velox=160;                 }  break;
      case '6':  {  Velox=170;                 }  break;
      case '7':  {  Velox=180;                 }  break;
      case '8':  {  Velox=190;                 }  break;
      case '9':  {  Velox=200;                 }  break;
      case 'q':  {  Velox=255;                 }  break;
    // COMANDOS DE DIREÇAO
      case 'F':  {  FRENTE();                  }  break;
      case 'B':  {  RE();                      }  break;
      case 'L':  {  EIXOESQUERDA();            }  break;
      case 'R':  {  EIXODIREITA();             }  break;
      case 'G':  {  ESQUERDA();                }  break;
      case 'I':  {  DIREITA();                 }  break;
      case 'H':  {  REESQUERDA();              }  break;
      case 'J':  {  REDIREITA();               }  break;
      case 'S':  {  PARE();                    }  break;
      case 'D':  {  OFF();                     }  break;
    // COMANDOS DE AUXILIARES
      case 'U':  {  digitalWrite(Lanterna, HIGH); }  break;
      case 'u':  {  digitalWrite(Lanterna, LOW);  }  break;
      case 'X':  {  digitalWrite(Alerta, HIGH); }  break;
      case 'x':  {  digitalWrite(Alerta, LOW);  }  break;
      case 'W':  {  digitalWrite(Farol, HIGH); }  break;
      case 'w':  {  digitalWrite(Farol, LOW);  }  break;
      case 'V':  {  tone(Buzzer,2500);         }  break;
      case 'v':  {  noTone(Buzzer);            }  break;



   } // Fim Switch

  
}   // Fim void loop

void PARE()
  {
   //Parada
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_A, LOW);
   digitalWrite(M_Dir_B, LOW);
   digitalWrite(M_Esq_A, LOW);
   digitalWrite(M_Esq_B, LOW);
  }
  
void OFF()
  {
   //Desliga tudo
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_A, LOW);
   digitalWrite(M_Dir_B, LOW);
   digitalWrite(M_Esq_A, LOW);
   digitalWrite(M_Esq_B, LOW);
   digitalWrite(Lanterna, LOW);
   digitalWrite(Alerta, LOW);
   digitalWrite(Farol, LOW);
   noTone(Buzzer);
  }
  
void FRENTE()
  {
   analogWrite(M_Dir_V, Velox);    
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Esq_B, LOW);
   digitalWrite(M_Dir_B, LOW);
   digitalWrite(M_Dir_A, HIGH);
   digitalWrite(M_Esq_A, HIGH);
  }

void RE()
  {
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_A, LOW);
   digitalWrite(M_Esq_A, LOW);
   digitalWrite(M_Dir_B, HIGH);
   digitalWrite(M_Esq_B, HIGH);
  }

void DIREITA()
  {
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_A, LOW);
   digitalWrite(M_Dir_B, LOW);
   digitalWrite(M_Esq_B, LOW);
   digitalWrite(M_Esq_A, HIGH);
  }

void ESQUERDA()
  {
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_B, LOW);
   digitalWrite(M_Esq_A, LOW);
   digitalWrite(M_Esq_B, LOW);
   digitalWrite(M_Dir_A, HIGH);
  }

void EIXODIREITA() // Roda no proprio eixo
  {
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_A, LOW);
   digitalWrite(M_Esq_B, LOW);
   digitalWrite(M_Dir_B, HIGH);
   digitalWrite(M_Esq_A, HIGH);
  }

void EIXOESQUERDA() // Roda no proprio eixo
  {
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_B, LOW);
   digitalWrite(M_Esq_A, LOW);
   digitalWrite(M_Dir_A, HIGH);
   digitalWrite(M_Esq_B, HIGH);
  }

void REDIREITA()
  {
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_A, LOW);
   digitalWrite(M_Dir_B, LOW);
   digitalWrite(M_Esq_A, LOW);
   digitalWrite(M_Esq_B, HIGH);
  }

void REESQUERDA()
  {
   analogWrite(M_Dir_V, Velox);
   analogWrite(M_Esq_V, Velox);
   digitalWrite(M_Dir_B, HIGH);
   digitalWrite(M_Dir_A, LOW);
   digitalWrite(M_Esq_A, LOW);
   digitalWrite(M_Esq_B, LOW);
  }

