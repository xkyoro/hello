float x, y;
float x_size, y_size;
boolean R_hit;
int e_num = 10;

void setup(){
 size (400,400,P2D); 
 
 x = 20.0;
 y = 0.0;
 x_size = 20.0;
 y_size = 20.0;
 R_hit = false;
 
}

void draw(){
  background(0);
  for(int i = 0; i < e_num; i++){
  rect(x + (i * x_size), y, x_size, y_size);
  }
  fill(255);
    
  if(x + (e_num* x_size) >= width){
    R_hit = true;
    y += y_size;
  }
  if(x <= 0){
   R_hit = false;
   y += y_size;
  }
  
  if(y > y_size * 15){
   y = 0.0; 
  }
  
  if(!R_hit)x++;
  else x--;
}