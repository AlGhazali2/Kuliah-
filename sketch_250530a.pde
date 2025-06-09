import processing.event.MouseEvent;

float rotX = 0;
float rotY = 0;
float rotZ = 0;
float zoomLevel = 1.0;
float offsetY = 0;

PImage tex;
boolean useTexture = false;

float lightX = -1, lightY = 0.5, lightZ = -1;

void setup() {
  size(800, 600, P3D);
  tex = loadImage("texture.jpg"); // Letakkan texture.jpg dalam folder sketch
  println("Kontrol: Mouse (rotasi), Q/E (roll), W/S (naik/turun), +/- (zoom), T (toggle texture), panah (ubah cahaya)");
}

void draw() {
  background(240);
  fill(0);
  textSize(16);
  text("Zoom: " + nf(zoomLevel, 1, 1) + "x", 20, 30);
  text("Texture: " + (useTexture ? "On" : "Off"), 20, 50);
  text("Cahaya: [" + nf(lightX,1,1) + "," + nf(lightY,1,1) + "," + nf(lightZ,1,1) + "]", 20, 70);

  translate(width/2, height/2 + offsetY);
  scale(zoomLevel);
  perspective(PI/3.0, float(width)/float(height), 0.1, 1000);

  rotateX(rotX);
  rotateY(rotY);
  rotateZ(rotZ);

  ambientLight(60, 60, 60);
  directionalLight(200, 200, 200, lightX, lightY, lightZ);

  float hurufWidth = 100;
  float hurufHeight = 180;
  float depth = 30;

  pushMatrix(); translate(-hurufWidth * 1.5, 0, 0); drawSolidA(hurufWidth, hurufHeight, depth); popMatrix();
  pushMatrix(); translate(0, 0, 0); drawSolidA(hurufWidth, hurufHeight, depth); popMatrix();
  pushMatrix(); translate(hurufWidth * 1.5, 0, 0); drawSolidG(hurufWidth, hurufHeight, depth); popMatrix();
}

void drawSolidA(float w, float h, float d) {
  float legWidth = w * 0.2;
  float barHeight = w * 0.15;

  if (useTexture) textureMode(NORMAL);

  // Kaki kiri (miring)
  pushMatrix();
  translate(-w / 4, 0, 0);
  rotateZ(radians(15));
  drawBoxWithTexture(legWidth, h, d);
  popMatrix();

  // Kaki kanan (miring)
  pushMatrix();
  translate(w / 4, 0, 0);
  rotateZ(radians(-15));
  drawBoxWithTexture(legWidth, h, d);
  popMatrix();

  // Batang tengah
  pushMatrix();
  translate(0, -h * 0.1, 0);
  drawBoxWithTexture(w - legWidth * 1.2, barHeight, d);
  popMatrix();
}

void drawSolidG(float w, float h, float d) {
  float t = w * 0.15;

  // Horizontal atas
  pushMatrix(); translate(0, -h/2 + t/2, 0); drawBoxWithTexture(w, t, d); popMatrix();
  // Horizontal bawah
  pushMatrix(); translate(0, h/2 - t/2, 0); drawBoxWithTexture(w, t, d); popMatrix();
  // Vertikal kiri
  pushMatrix(); translate(-w/2 + t/2, 0, 0); drawBoxWithTexture(t, h, d); popMatrix();
  // Vertikal kanan bawah
  pushMatrix(); translate(w/2 - t/2, h/4, 0); drawBoxWithTexture(t, h/2, d); popMatrix();
  // Horizontal tengah
  pushMatrix(); translate(0, 0, 0); drawBoxWithTexture(w/2, t, d); popMatrix();
}

void drawBoxWithTexture(float w, float h, float d) {
  if (useTexture && tex != null) {
    beginShape(QUADS);
    texture(tex);

    // Z+ face
    vertex(-w/2, -h/2,  d/2, 0, 0);
    vertex( w/2, -h/2,  d/2, 1, 0);
    vertex( w/2,  h/2,  d/2, 1, 1);
    vertex(-w/2,  h/2,  d/2, 0, 1);
    endShape(CLOSE);
  } else {
    fill(255, 100, 100);
    noStroke();
    box(w, h, d);
  }
}

void mouseMoved() {
  rotX = map(mouseY, 0, height, -PI / 2, PI / 2);
  rotY = map(mouseX, 0, width, -PI, PI);
}

void mouseWheel(MouseEvent event) {
  zoomLevel += event.getCount() * -0.1;
  zoomLevel = constrain(zoomLevel, 0.3, 3.0);
}

void keyPressed() {
  if (key == '+' || key == '=') zoomLevel += 0.2;
  else if (key == '-') zoomLevel -= 0.2;
  else if (key == ' ') {
    rotX = 0; rotY = 0; rotZ = 0;
    zoomLevel = 1.0;
    offsetY = 0;
    lightX = -1; lightY = 0.5; lightZ = -1;
  } else if (key == 'q' || key == 'Q') rotZ -= 0.1;
  else if (key == 'e' || key == 'E') rotZ += 0.1;
  else if (key == 'w' || key == 'W') offsetY -= 10;
  else if (key == 's' || key == 'S') offsetY += 10;
  else if (key == 't' || key == 'T') useTexture = !useTexture;
  else if (keyCode == LEFT)  lightX -= 0.2;
  else if (keyCode == RIGHT) lightX += 0.2;
  else if (keyCode == UP)    lightY -= 0.2;
  else if (keyCode == DOWN)  lightY += 0.2;

  zoomLevel = constrain(zoomLevel, 0.3, 3.0);
}
