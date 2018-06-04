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
float distance;
float distance_step = 0.0;
float lux;

float anglefix = 0.0;

// serial connection
Serial myPort;

ControlP5 cp5;
Textlabel myTextlabelA;
Textlabel myTextlabelB;
Textlabel myTextlabelC;
Textlabel myTextlabelD;

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
  
  //initialise cp5 object to allow text labels to be written
  cp5 = new ControlP5(this);
  
  // load in data in from csv file
  lines = loadStrings("DATALOG2.CSV");

  // Prepare the points for the plot
  int numberofPoints = lines.length;
  GPointsArray points = new GPointsArray(numberofPoints);

  // Create a plots and set its position on the screen
  GPlot plot = new GPlot(this,50,100);
  GPlot plot2 = new GPlot(this,600,450);
  GPlot plot3 = new GPlot(this,51,450);
  GPlot plot4 = new GPlot(this,600,100);
  //GPlot plot5 = new GPlot(this, 970, 50);
  
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
    
    //DELETE THIS IF DIYA FIXES IN FIRMWARE - fixing angle issue
   // if (i == 0){
     // anglefix = float(list[2]);
    //};
    
    time = float(list[0]);
    speed = float(list[1]);
    incline = float(list[2]) - anglefix;
    calories = float(list[3]);
    light = float(list[4]);
    
    
    //convert voltage to lux
    float resistance = (light * 1000)/(5.0 - light);
    light = 10000000*pow(resistance, -1.4);
    
    //updating elevation once per timestep 
    if (time != time_previous){
      time_step = time - time_previous; // this should always be 1 unless something has gone wrong in the timing
      elevation_step = speed * (1.0/3600.0)* time_step * tan(incline*(3.141/180));
      elevation_step = elevation_step * 1000.0 ; // convert elevation into metres not kilometres

    }
    
     //updating distance once per timestep 
    if (time != time_previous){
      time_step = time - time_previous; // this should always be 1 unless something has gone wrong in the timing
      distance_step = speed * (1.0/3600.0)* time_step;
    }
    
    
    //update elevation
    elevation = elevation + elevation_step;
    
    
    //update distance
    distance = distance + distance_step;
    
    
    //storing data
    light_array[i] = light;
    elevation_array[i] = elevation;
    speed_array[i] = speed;
    calorie_array[i] = calories;
    time_array[i] = time;
    
    ///unfiltered points.add(x, y) - uncomment this for unfiltered graphing;
    //plot.addPoint(time,speed);
    //plot2.addPoint(time,calories);
    //plot3.addPoint(time,light);
    //plot4.addPoint(time,elevation);
    
    
    //update time_previous
    time_previous = time;
  }
  
  //trying to filter the arrays of data
  light_array_filtered = smoothArray(light_array, 20);
  elevation_array_filtered = smoothArray(elevation_array, 30);
  speed_array_filtered = smoothArray(speed_array,5);
  calorie_array_filtered = smoothArray(calorie_array, 20);
  
  
  //Printing the distance travelled
  
  myTextlabelA = cp5.addTextlabel("label")
                  .setText("The Bike Logger: Data From Your Journey")
                  .setPosition(100,50)
                  .setColorValue(0)
                  .setFont(createFont("Georgia",26));
                  
                  
  
  myTextlabelB = cp5.addTextlabel("label2")
                    .setText("Distance travelled on journey:")
                    .setPosition(1100,200)
                    .setColorValue(0)
                    .setFont(createFont("Georgia",16));
                    
  myTextlabelC = cp5.addTextlabel("label3")
                    .setText(str(distance))
                    .setPosition(1100,230)
                    .setColorValue(0)
                    .setFont(createFont("Georgia",16));
                    
  myTextlabelD = cp5.addTextlabel("label4")
                    .setText("km")
                    .setPosition(1200,230)
                    .setColorValue(0)
                    .setFont(createFont("Georgia",16));
  
  //plotting graphs from filtered data
  for (int i = 0; i < numberofPoints; i++) {
    plot.addPoint(time_array[i],speed_array_filtered[i]);
    plot2.addPoint(time_array[i],calorie_array_filtered[i]);
    plot3.addPoint(time_array[i],light_array_filtered[i]);
    plot4.addPoint(time_array[i],elevation_array_filtered[i]);
  }

  // Set the plot title and the axis labels
  plot.setTitleText("Speed");
  plot.getXAxis().setAxisLabelText("Time /s");
  plot.getYAxis().setAxisLabelText("Speed km/h");
  
  plot2.setTitleText("Calories");
  plot2.getXAxis().setAxisLabelText("Time /s");
  plot2.getYAxis().setAxisLabelText("Calories burnt");
  
  plot3.setTitleText("Light Intensity");
  plot3.getXAxis().setAxisLabelText("Time /s");
  plot3.getYAxis().setAxisLabelText("Light /lux");
  
  plot4.setTitleText("Elevation");
  plot4.getXAxis().setAxisLabelText("Time /s");
  plot4.getYAxis().setAxisLabelText("Elevation /m");
  
  //plot5.setTitleText("Filter test graph");
  //plot5.getXAxis().setAxisLabelText("Time /s");
  //plot5.getYAxis().setAxisLabelText("light");

  
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
  
  /*plot5.beginDraw();
  plot5.drawBackground();
  plot5.drawBox();
  plot5.drawXAxis();
  plot5.drawYAxis();
  plot5.drawTitle();
  plot5.drawGridLines(GPlot.BOTH);
  plot5.drawLines();
  plot5.endDraw();*/
}


void draw() {
}
