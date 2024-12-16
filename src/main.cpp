/**
 ******************************************************************************
 * @file        : main.cpp
 * @brief       : main file
 * @authors     : Bulliard Aurélien <aurelien.bulliard@edu.hefr.ch>
 *               & Casimiro Filipe <filipe.casimiro@edu.hefr.ch>    
 * @date        : 13.12.2024
 ******************************************************************************
 * @copyright   : Copyright (c) 2024 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Main file
 ******************************************************************************
 */

#include "DiscoLcd.hpp"
#include "Fonts/IBMPlexSansMedium12pt8b.h"
#include "Fonts/IBMPlexSansMedium18pt8b.h"
#include "arduino_shield.hpp"
#include "color.hpp"
#include "deletable_text.hpp"
#include "f412disco_ado.h"
#include "joystick.hpp"
#include "my_buttons.hpp"
#include "my_counter.hpp"
#include "my_rotary.hpp"
#include "progress.hpp"
#include "tracing.h"
#include "xmas.hpp"
#include "shrek.cpp"

constexpr int kTextPosY          = 215;
constexpr int kStartProgressBar  = 8;
constexpr int kEndProgressBar    = 230;
constexpr int kProgressBarHeight = 8;
constexpr int kMaximalNumber     = 99;
constexpr int kPollerPrescaler   = 10000;
constexpr int kPollerFrequency   = 1000;


class PwmProxy : public DiscoLcdGFX::Pwm {
   public:
    PwmProxy() : DiscoLcdGFX::Pwm() {
        channel_ = new PwmChannel(PwmChannel::kPF5);
    }
    ~PwmProxy() { delete channel_; }

    void SetDutyCycle(float duty_cycle) override {
        channel_->SetDutyCycle(duty_cycle);
    }
    HAL_StatusTypeDef Start() override { return channel_->Start(); }
    HAL_StatusTypeDef Stop() override { return channel_->Stop(); }

   private:
    PwmChannel* channel_;
    PwmProxy(const PwmProxy& t);
    PwmProxy operator=(PwmProxy);
};

int main(void) {
    DiscoAdoInit();

    Seg7 display(ArduinoShield::kClick1);

    DiscoLcdGFX gfx(new PwmProxy());
    gfx.SetBackLightLevel(0.5);
    gfx.drawBitmap(0,0,shrek,240,240,0xFFFF);
}