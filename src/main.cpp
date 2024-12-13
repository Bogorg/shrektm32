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

constexpr int kTextPosY          = 215;
constexpr int kStartProgressBar  = 8;
constexpr int kEndProgressBar    = 230;
constexpr int kProgressBarHeight = 8;
constexpr int kMaximalNumber     = 99;
constexpr int kPollerPrescaler   = 10000;
constexpr int kPollerFrequency   = 1000;
const char* kWelcomeMessage      = "Encore un effort...";
const char* kChristmasMessage    = "Joyeux No\xebl !";
const XmasTreeDef kTreeDef       = {
          .posX        = 120,
          .posY        = 180,
          .maxWidth    = 200,
          .minWidth    = 30,
          .diskHeight  = 19,
          .height      = 8,
          .discSpacing = 2,
          .pegWidth    = 4,
          .baseWidth   = 80,
};

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
    int brightnessLevel = kBrightnessInitLevel;
    Counter counter;

    display.SetBrightness(kBrightnessMap[brightnessLevel]);
    display.Print(counter.GetCount());

    DiscoLcdGFX gfx(new PwmProxy());
    gfx.SetBackLightLevel(0.5);

    MyRotary rotary(ArduinoShield::kClick2, &counter, &display);

    Joystick* joystick = Joystick::GetInstance();
    // TODID(student): pass a reference of the rotary encoder to the CountButtons
    // and ResetButton. This is required to update the LEDs pattern on the
    // rotary encoder when the counter changes.
    joystick->AddButton(Joystick::kButtonRight,
                        new CountButton(1, &counter, &display, &rotary));
    joystick->AddButton(Joystick::kButtonLeft,
                        new CountButton(-1, &counter, &display, &rotary));
    joystick->AddButton(Joystick::kButtonSelect,
                        new ResetButton(&counter, &display, &rotary));
    joystick->AddButton(Joystick::kButtonUp,
                        new BrightnessButton(1, &brightnessLevel, &display));
    joystick->AddButton(Joystick::kButtonDown,
                        new BrightnessButton(-1, &brightnessLevel, &display));

    gfx.setFont(&IBMPlexSansMedium12pt8b);

    DeletableText t1(&gfx, kWelcomeMessage);
    DeletableText t2(&gfx, kChristmasMessage);

    gfx.setTextColor(kColorCyan);
    t1.DrawCenter(kTextPosY);

    ProgressMeter progress(&gfx,
                           kStartProgressBar,
                           kEndProgressBar,
                           gfx.width() - 2 * kStartProgressBar,
                           kProgressBarHeight,
                           kMaximalNumber);

    XmasTree tree(&gfx, &kTreeDef);

    Poller::InitTimer(kPollerPrescaler, kPollerFrequency);
    int prev = -1;

    while (true) {
        int val = counter.GetCount();
        if (val == prev) continue;

        if (val == kMaximalNumber) {
            gfx.setTextColor(kColorYellow);
            t1.Delete();
            t2.DrawCenter(kTextPosY);
        } else if (prev == kMaximalNumber) {
            gfx.setTextColor(kColorCyan);
            t2.Delete();
            t1.DrawCenter(kTextPosY);
        }

        progress.Draw(val);
        tree.Draw(val * kTreeDef.height / kMaximalNumber);

        prev = val;
    }
}
