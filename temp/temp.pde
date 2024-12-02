import processing.serial.*; // Import serial library for communication

Serial myPort; // Serial port object
float roll = 0, pitch = 0; // Variables to store roll and pitch values

void setup() {
  size(800, 800, P3D); // Set canvas size and enable 3D
  String portName = "COM10"; // Your serial port
  myPort = new Serial(this, portName, 9600); // Initialize serial communication at 9600 baud rate
}

void draw() {
  background(200); // Gray background
  lights(); // Enable lighting

  // Read and process serial data
  while (myPort.available() > 0) {
    String data = myPort.readStringUntil('\n'); // Read until newline character
    if (data != null) {
      data = trim(data); // Remove extra spaces or newline
      String[] angles = split(data, ','); // Split data by comma
      if (angles.length == 2) { // Ensure there are exactly two values
        roll = radians(float(angles[0])); // Convert roll to radians
        pitch = radians(float(angles[1])); // Convert pitch to radians
      }
    }
  }

  // Draw 3D object
  translate(width / 2, height / 2); // Move to canvas center
  rotateX(pitch); // Apply pitch rotation
  rotateY(roll); // Apply roll rotation
  fill(150, 0, 150); // Set object color
  box(200, 50, 100); // Draw a 3D box
}
