/**
 ******************************************************************************
 * @file        : my_counter.hpp
 * @brief       : My Counter
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 25. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * My Counter
 ******************************************************************************
 */

#ifndef SRC_MY_COUNTER_HPP_
#define SRC_MY_COUNTER_HPP_

class Counter {
   public:
    Counter();
    void Reset();
    void Decrement();
    void Increment();
    int GetCount();

   private:
    int count_;
};

#endif /* SRC_MY_COUNTER_HPP_ */
