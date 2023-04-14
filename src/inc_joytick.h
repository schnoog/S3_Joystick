


void joystick_setup() {
  // Set Range Values
  Joystick.setXAxisRange(0, 65535);
  Joystick.setYAxisRange(0, 65535);
  Joystick.setZAxisRange(0, 65535);
  Joystick.setRxAxisRange(0, 65535);
  Joystick.setRyAxisRange(0, 65535);
  Joystick.setRzAxisRange(0, 65535);
  Joystick.setThrottleRange(0, 65535);
  Joystick.setRudderRange(0, 65535);
  Joystick.setAcceleratorRange(0,65535);
  Joystick.setSteeringRange(0,65535);
  Joystick.setBrakeRange(0,65535);
  Joystick.begin(false); // no auto send
  Serial.println("joystick started");
}



