//
// Multicopter mission test.
//
// Author: Julian Oes <julian@oes.ch>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <iostream>
#include <string>
#include "autopilot_tester.h"


TEST_CASE("Takeoff and Land (Multicopter offboard)", "[multicopter_offboard]")
{
    AutopilotTester tester;
    Offboard::PositionNEDYaw home {0.0f, 0.0f, 0.0f, 0.0f};
    Offboard::PositionNEDYaw takeoff_position {0.0f, 0.0f, -2.0f, 0.0f};
    tester.connect(connection_url);
    tester.wait_until_ready_local_position_only();
    tester.arm();
    tester.offboard_goto(takeoff_position, 0.5f);
    tester.offboard_land();
    tester.wait_until_disarmed();
    REQUIRE(tester.estimated_horizontal_position_close_to(home, 0.5f));
}


TEST_CASE("Mission (Multicopter offboard )", "[multicopter_offboard]")
{
    AutopilotTester tester;
    Offboard::PositionNEDYaw home {0.0f, 0.0f, 0.0f, 0.0f};
    Offboard::PositionNEDYaw takeoff_position {0.0f, 0.0f, -2.0f, 0.0f};
    Offboard::PositionNEDYaw waypoint_1 {0.0f, 5.0f, -2.0f, 180.0f};
    Offboard::PositionNEDYaw waypoint_2 {5.0f, 5.0f, -4.0f, 180.0f};
    Offboard::PositionNEDYaw waypoint_3 {5.0f, 0.0f, -4.0f, 90.0f};
    tester.connect(connection_url);
    tester.wait_until_ready_local_position_only();
    tester.arm();
    tester.offboard_goto(takeoff_position, 0.5f);
    tester.offboard_goto(waypoint_1, 1.0f);
    tester.offboard_goto(waypoint_2, 1.0f);
    tester.offboard_goto(waypoint_3, 1.0f);
    tester.offboard_goto(takeoff_position, 0.2f);
    tester.offboard_land();
    tester.wait_until_disarmed();
    REQUIRE(tester.estimated_horizontal_position_close_to(home, 1.0f));
}