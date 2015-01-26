PImage[] inv;

class Entity{
  float x = 0;
  float y = 0;
  void draw(){
   //
  imaga(inv[(frameCount/30) % C2], x, y); 
  }

 void setup (){
  size (800,800);
}

void draw (){
  background(0);
  translate(width/2,height/2);
  
  
}
