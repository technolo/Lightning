#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <PID_v1.h>
#include <Servo.h>
#include "Defines.h"
#include "Odometr.h"

class Actuators : public Module
{
  private:
    Servo servo_;
    Servo esc_;
    int servoMsec_;;
    int escMsec_;
    Odometr* odometr_ = NULL;
    int escForwardEdge_ = ENG_ZERO_SPEED - 85;  // С данного значения начинаем ехать вперед
    int escBackwardEdge_ = ENG_ZERO_SPEED + 85;  // С данного значения начинаем ехать назад
    int escCenter_ = ENG_ZERO_SPEED;  // С данного значения начинаем ехать назад
    PID* pid_;
    double pidSetpoint_, pidInput_, pidOutput_;

  public:
    Actuators(int period, Odometr* odometr) : Module(period)
    {
      odometr_ = odometr;
      //Specify the links and initial tuning parameters
      double Kp = 5, Ki = 1, Kd = 1;
      pid_ = new PID(&pidInput_, &pidOutput_, &pidSetpoint_, Kp, Ki, Kd, DIRECT);
      pidInput_ = odometr_->getAvgSpeed();
      pidSetpoint_ = 70;
      pid_->SetMode(AUTOMATIC);
    }

    void servoWrite(int msec)
    {
      servoMsec_ = msec;
      servo_.writeMicroseconds(constrain(msec, 550, 950));
    }

    int servoRead()
    {
      return servoMsec_;
    }

    void escWrite(int msec)
    {
      escMsec_ = msec;
      esc_.writeMicroseconds(constrain(msec, 900, 2100));
    }

    int escRead()
    {
      return escMsec_;
    }

    // Калибровка ESC, нахождение нижней и верхней границы с которой авто начинает ехать
    void calibrateEscEdges()
    {
      const int step = 10;  // шаг калибровки
      const int stepCnt = 15;  // количество шагов от центра
      const unsigned int stepPeriod = 100;  // длительность шага калибровки msec
      int i;
      int forwardEdge = ENG_ZERO_SPEED;
      int backwardEdge = ENG_ZERO_SPEED;

      // Forward
      for (i = 0; i < stepCnt; i++)
      {
        forwardEdge -= step;
        int curDistance = odometr_->getDistance();
        escWrite(forwardEdge);
        delay(stepPeriod);
        if (odometr_->getDistance() != curDistance)
          break;
      }
      delay(500);

      // Backward
      for (i = 0; i < stepCnt; i++)
      {
        backwardEdge += step;
        int curDistance = odometr_->getDistance();
        escWrite(backwardEdge);
        delay(stepPeriod);
        if (odometr_->getDistance() != curDistance)
          break;
      }

      escForwardEdge_ = forwardEdge;
      escBackwardEdge_ = backwardEdge;
      escCenter_ = (backwardEdge + forwardEdge) / 2;
      SerialPrint("escForwardEdge = "); SerialPrint(escForwardEdge_);
      SerialPrint("\t escBackwardEdge = "); SerialPrint(escBackwardEdge_);
      SerialPrint("\t escCenter = "); SerialPrint(escCenter_);
      SerialPrintln("\t");
    }

    void init()
    {
      servo_.attach(SERVO_PIN);
      esc_.attach(ESC_PIN);

      servoWrite(SRV_CENTER);
      escWrite(ENG_ZERO_SPEED);

      //calibrateEscEdges();
      //escWrite(escCenter_);
      delay(3000);
    }

    void setAngle(int angle)
    {
      servoWrite(angle);
    }

    void setSpeed(int speed)
    {
      int escSpeed;

      if (speed < 0)
      {
        escSpeed = ENG_ZERO_SPEED - speed * 85;
      }
      else
      {
        /*if (odometr_->getAvgSpeed() < 30)
          {
          escSpeed = ENG_ZERO_SPEED - speed * 95.0 * 1.5;
          }*/
        escSpeed = ENG_ZERO_SPEED - 85 - pidOutput_;
     /* }
      else
      {
        escSpeed = ENG_ZERO_SPEED - speed * 100.0;
      }*/
    }

    /*  if (speed < 0)
      {
        escSpeed = escBackwardEdge_ - speed * 5;
      }
      else
      {
        escSpeed = escForwardEdge_ - speed * 5;
      }*/

    escWrite(escSpeed);
}

int getRealSpeed()
{
  odometr_->getSpeed();
}

void onUpdate()
{
  pidInput_ = odometr_->getAvgSpeed();
  pid_->Compute();
}
};

#endif // ACTUATORS_H
