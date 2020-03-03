/**
 * This file is part of piESocket.
 * Copyright (c) 2020 Mateusz Mirosławski.
 *
 * piESocket is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * piESocket is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with piESocket.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEST_SRC_TESTS_PROGRAM_ESOCKET_TESTS_H_
#define TEST_SRC_TESTS_PROGRAM_ESOCKET_TESTS_H_

#include <gtest/gtest.h>
#include <Delay.h>
#include <ESocket.h>

/**
 * Check ESocket class
 */
TEST(ESocketTests, TestDefault1) {

	ESocket s;

	s.run();

	ASSERT_FALSE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_FALSE(s.isLocked());
}

TEST(ESocketTests, TestSwitch1) {

	ESocket s;

	s.setTrigger(true);
	s.run();

	ASSERT_TRUE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_FALSE(s.isLocked());
}

TEST(ESocketTests, TestSwitch2) {

	onh::Delay d(1500);
	ESocket s(1000);

	s.setTrigger(true);
	s.run();

	ASSERT_TRUE(s.getOut());
	ASSERT_FALSE(s.getAlarm());

	d.wait();

	s.setTrigger(false);
	s.run();

	ASSERT_FALSE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_FALSE(s.isLocked());
}

TEST(ESocketTests, TestSwitch3) {

	onh::Delay d(1500);
	ESocket s(1000);

	// Switch on
	s.setTrigger(true);
	s.run();
	ASSERT_TRUE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_FALSE(s.isLocked());

	// Switch triggers alarm - output not changed
	s.setTrigger(false);
	s.run();
	ASSERT_TRUE(s.getOut());
	ASSERT_TRUE(s.getAlarm());
	ASSERT_TRUE(s.isLocked());

	// Ack alarm
	s.setNotAck(true);
	s.run();
	ASSERT_TRUE(s.getOut());
	ASSERT_TRUE(s.getAlarm());
	ASSERT_TRUE(s.isLocked());

	// Wait
	d.wait();
	s.run();
	ASSERT_TRUE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_TRUE(s.isLocked());

	// Take off ack
	s.setNotAck(false);
	s.run();
	ASSERT_FALSE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_FALSE(s.isLocked());
}

TEST(ESocketTests, TestLock1) {

	ESocket s;

	s.setTrigger(true);
	s.setTriggerLock(true);
	s.run();

	ASSERT_FALSE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_TRUE(s.isLocked());
}

TEST(ESocketTests, TestLock2) {

	onh::Delay d(1500);
	ESocket s(1000);

	// Switch on
	s.setTrigger(true);
	s.run();
	ASSERT_TRUE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_FALSE(s.isLocked());

	// Lock
	s.setTriggerLock(true);
	s.setTrigger(false);
	s.run();
	ASSERT_TRUE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_TRUE(s.isLocked());

	d.wait();
	s.setTriggerLock(false);
	s.run();
	ASSERT_FALSE(s.getOut());
	ASSERT_FALSE(s.getAlarm());
	ASSERT_FALSE(s.isLocked());
}

#endif /* TEST_SRC_TESTS_PROGRAM_ESOCKET_TESTS_H_ */
