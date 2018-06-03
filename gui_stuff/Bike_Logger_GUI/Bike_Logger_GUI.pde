import processing.serial.*;
import signal.library.*;
import controlP5.*;
import grafica.*;
String[] lines;
int index=0;
String[] list;
float time;
float time_previous = 0.0;
float time_step;
float speed;
float incline;
float calories;
float light;
float filteredlight;
float elevation;
float elevation_step = 0.0;

// serial connection
Serial myPort;

ControlP5 cp5;
DropdownList d1;
int cnt = 0;

// smoothArray is a lowpass filter. values:an array of numbers that will be modified in place, smoothing: the strength of the smoothing filter; 1=no change, larger values smoothes more
float[] smoothArray(float[] values, float smoothing ){
  float value = values[0]; // start with the first input
  for (int i=1; i<values.length; i++){
    float currentValue = values[i];
    value = value + ( (currentValue - value) / smoothing);
    values[i] = value;
  }
  return values;
}


void setup() {
  size(1400,800);
  background(215,215,255);
  
  //setup serial port to arduino
  printArray(Serial.list());
  //myPort = new Serial(this, Serial.list()[0],  9600);
  //myPort.write("1");
  
  // load in data in from csv file
  lines = loadStrings("perfectdata.CSV");

  // Prepare the points for the plot
  int numberofPoints = lines.length;
  GPointsArray points = new GPointsArray(numberofPoints);

  // Create a plots and set its position on the screen
  GPlot plot = new GPlot(this,50,50);
  GPlot plot2 = new GPlot(this,600,400);
  GPlot plot3 = new GPlot(this,51,400);
  GPlot plot4 = new GPlot(this,600,50);
  GPlot plot5 = new GPlot(this, 970, 50);
  
  //initialising arrays to be filled with csvread data
  float[] light_array = new float[numberofPoints];
  float[] light_array_filtered = new float[numberofPoints];
  float[] elevation_array = new float[numberofPoints];
  float[] elevation_array_filtered = new float[numberofPoints];
  float[] speed_array = new float[numberofPoints];
  float[] speed_array_filtered = new float[numberofPoints];
  float[] calorie_array = new float[numberofPoints];
  float[] calorie_array_filtered = new float[numberofPoints];
  float[] time_array = new float[numberofPoints];
  
  for (int i = 0; i < numberofPoints; i++) {
    list = split(lines[i], ',');
    time = float(list[0]);
    speed = float(list[1]);
    incline = float(list[2]);
    calories = float(list[3]);
    light = float(list[4]);
    
    //updating elevation once per timestep 
    if (time != time_previous){
      time_step = time - time_previous; // this should always be 1 unless something has gone wrong in the timing
      elevation_step = speed * (1.0/3600.0)* time_step * tan(incline);
    }
    
    //update elevation
    elevation = elevation + elevation_step;
    
    
    //storing data
    light_array[i] = light;
    elevation_array[i] = elevation;
    speed_array[i] = speed;
    calorie_array[i] = calories;
    time_array[i] = time;
    
    ///points.add(x, y);
    plot.addPoint(time,speed);
    plot2.addPoint(time,calories);
    plot3.addPoint(time,light);
    plot4.addPoint(time,elevation);
    
    
    //update time_previous
    time_previous = time;
  }
  
  //trying to filter the arrays of data
  light_array_filtered = smoothArray(light_array, 20);
  elevation_array_filtered = smoothArray(elevation_array, 30);
  speed_array_filtered = smoothArray(speed_array,20);
  calorie_array_filtered = smoothArray(calorie_array, 20);
  
  
  //creating graph from arrays not as the points are read from the csv
  for (int i = 0; i < numberofPoints; i++) {
    plot5.addPoint(time_array[i],calorie_array_filtered[i]);
  }
  
  /*//drop down list stuff
  cp5 = new ControlP5(this);
  
  // create a DropdownList, 
  d1 = cp5.addDropdownList("myList-d1")
          .setPosition(550, 100)
          ;
          
  customize(d1); // customize the first list
  */
  
  // TEST Filter the signal [THIS IS THE IMPORTANT LINE HERE!]
  
  
  
  //testing filtering
  //filtered_light = myFilter.filterUnitFloat( light_array );

  // Set the plot title and the axis labels
  plot.setTitleText("Speed");
  plot.getXAxis().setAxisLabelText("Time /s");
  plot.getYAxis().setAxisLabelText("Speed km/h");
  
  plot2.setTitleText("Calories");
  plot2.getXAxis().setAxisLabelText("Time /s");
  plot2.getYAxis().setAxisLabelText("Calories burnt");
  
  plot3.setTitleText("Light");
  plot3.getXAxis().setAxisLabelText("Time /s");
  plot3.getYAxis().setAxisLabelText("Light Voltage");
  
  plot4.setTitleText("Elevation");
  plot4.getXAxis().setAxisLabelText("Time /s");
  plot4.getYAxis().setAxisLabelText("Elevation /km");
  
  plot5.setTitleText("Filter test graph");
  plot5.getXAxis().setAxisLabelText("Time /s");
  plot5.getYAxis().setAxisLabelText("light");

  
  // Draw the plot  
  plot.beginDraw();
  plot.drawBackground();
  plot.drawBox();
  plot.drawXAxis();
  plot.drawYAxis();
  plot.drawTitle();
  plot.drawGridLines(GPlot.BOTH);
  plot.drawLines();
  plot.endDraw();
  
  plot2.beginDraw();
  plot2.drawBackground();
  plot2.drawBox();
  plot2.drawXAxis();
  plot2.drawYAxis();
  plot2.drawTitle();
  plot2.drawGridLines(GPlot.BOTH);
  plot2.drawLines();
  plot2.endDraw();
  
  plot3.beginDraw();
  plot3.drawBackground();
  plot3.drawBox();
  plot3.drawXAxis();
  plot3.drawYAxis();
  plot3.drawTitle();
  plot3.drawGridLines(GPlot.BOTH);
  plot3.drawLines();
  plot3.endDraw();
  
  plot4.beginDraw();
  plot4.drawBackground();
  plot4.drawBox();
  plot4.drawXAxis();
  plot4.drawYAxis();
  plot4.drawTitle();
  plot4.drawGridLines(GPlot.BOTH);
  plot4.drawLines();
  plot4.endDraw();
  
  plot5.beginDraw();
  plot5.drawBackground();
  plot5.drawBox();
  plot5.drawXAxis();
  plot5.drawYAxis();
  plot5.drawTitle();
  plot5.drawGridLines(GPlot.BOTH);
  plot5.drawLines();
  plot5.endDraw();
}





void customize(DropdownList ddl) {
  // a convenience function to customize a DropdownList
  ddl.setBackgroundColor(color(0));
  ddl.setItemHeight(20);
  ddl.setBarHeight(15);
  ddl.getCaptionLabel().set("Select Graph To View");
  
  ddl.addItem("Speed Graph",0);
  ddl.addItem("Some Other Graph",1);
  
  //ddl.scroll(0);
  ddl.setColorBackground(color(200));
  ddl.setColorActive(color(255, 128));
}

 
 void controlEvent(ControlEvent theEvent) {
  // DropdownList is of type ControlGroup.
  // A controlEvent will be triggered from inside the ControlGroup class.
  // therefore you need to check the originator of the Event with
  // if (theEvent.isGroup())
  // to avoid an error message thrown by controlP5.

  if (theEvent.isGroup()) {
    // check if the Event was triggered from a ControlGroup
    println("event from group : "+theEvent.getGroup().getValue()+" from "+theEvent.getGroup());
  } 
  else if (theEvent.isController()) {
    println("event from controller : "+theEvent.getController().getValue()+" from "+theEvent.getController());
  }
}


void draw() {
}
